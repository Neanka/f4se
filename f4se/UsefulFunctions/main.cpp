#include "main.h"

std::string mName = "UsefulFunctions";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;
F4SEPapyrusInterface		*g_papyrus = NULL;

#include "f4se/GameCamera.h"
typedef void(*_ThirdPersonCameraState_UpdateMode)(TESCameraState* state, bool weaponDrawn);
RelocAddr <_ThirdPersonCameraState_UpdateMode> ThirdPersonCameraState_UpdateMode(0x1251CC0);

bool IsWeaponDrawn()
{
	return (((*g_player)->actorState.flags >> 1) & 7) >= 3;
}

SInt32 GetCameraState(StaticFunctionTag * base)
{
	PlayerCamera * playerCamera = *g_playerCamera;
	if (playerCamera) {
		for (int i = 0; i < PlayerCamera::kNumCameraStates; i++) {
			if (playerCamera->cameraState == playerCamera->cameraStates[i])
				return i;
		}
	}
	return -1;
}

void UpdateThirdPerson(StaticFunctionTag * base)
{
	ThirdPersonCameraState_UpdateMode((*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_ThirdPerson2], IsWeaponDrawn());
}


#include "f4se/PapyrusNativeFunctions.h"

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, SInt32>("GetCameraState", "UsefulFunctions", GetCameraState, vm));
	vm->SetFunctionFlags("UsefulFunctions", "GetCameraState", IFunction::kFunctionFlag_NoWait);
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, void>("UpdateThirdPerson", "UsefulFunctions", UpdateThirdPerson, vm));
	return true;
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\"+ mName +".log").c_str());

		logMessage("query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		mName.c_str();
		info->version =		mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		// Check game version
		if (f4se->runtimeVersion != CURRENT_RUNTIME_VERSION) {
			char str[512];
			sprintf_s(str, sizeof(str), "Your game version: v%d.%d.%d.%d\nExpected version: v%d.%d.%d.%d\n%s will be disabled.",
				GET_EXE_VERSION_MAJOR(f4se->runtimeVersion),
				GET_EXE_VERSION_MINOR(f4se->runtimeVersion),
				GET_EXE_VERSION_BUILD(f4se->runtimeVersion),
				GET_EXE_VERSION_SUB(f4se->runtimeVersion),
				GET_EXE_VERSION_MAJOR(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_MINOR(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_BUILD(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_SUB(CURRENT_RUNTIME_VERSION),
				mName.c_str()
			);

			MessageBox(NULL, str, mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		// get the papyrus interface and query its version
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus)
		{
			_MESSAGE("couldn't get papyrus interface");
			return false;
		}
		else {
			_MESSAGE("got papyrus interface");
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		return true;
	}

};
