#include "main.h"

std::string mName = "TestPlugin";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEPapyrusInterface			* g_papyrus = NULL;

void GetTranslatedCoordinates(StaticFunctionTag* base, TESObjectREFR * thisObjectReference, float fDist, VMArray<float> fArray)
{
	if (!thisObjectReference || fArray.Length() != 3) {
		//Consider this as your fprintf(), it writes to your plugin's log file...
		_DMESSAGE("NULL TESOBJECTREFR POINTER OR INVALID ARRAY LENGTH!!!");
		return;
	}
	float fSetValue;
	//Using pointers because VMArray's set value method need variables 
	//to be passed by reference...
	float *fSetValuePtr = &fSetValue;
	float fRotZ = thisObjectReference->rot.z;
	float fTemp = (abs(fDist))*sin(fRotZ);
	*fSetValuePtr = thisObjectReference->pos.x + fTemp;
	fArray.Set(fSetValuePtr, 0);
	*fSetValuePtr = thisObjectReference->pos.y + fTemp / tan(fRotZ);
	fArray.Set(fSetValuePtr, 1);
	*fSetValuePtr = thisObjectReference->pos.z + fTemp * tan(thisObjectReference->rot.y);
	fArray.Set(fSetValuePtr, 2);
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction3 <StaticFunctionTag, void, TESObjectREFR*, float, VMArray<float>> ("GetTranslatedCoordinates", "MyPluginScript", GetTranslatedCoordinates, vm));
	vm->SetFunctionFlags("MyPluginScript", "GetTranslatedCoordinates", IFunction::kFunctionFlag_NoWait);
	return true;
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\"+ mName +".log").c_str());

		_MESSAGE("query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		mName.c_str();
		info->version =		mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		// Check game version
		if (f4se->runtimeVersion != CURRENT_RELEASE_RUNTIME) {
			char str[512];
			sprintf_s(str, sizeof(str), "Your game version: v%d.%d.%d.%d\nExpected version: v%d.%d.%d.%d\n%s will be disabled.",
				GET_EXE_VERSION_MAJOR(f4se->runtimeVersion),
				GET_EXE_VERSION_MINOR(f4se->runtimeVersion),
				GET_EXE_VERSION_BUILD(f4se->runtimeVersion),
				GET_EXE_VERSION_SUB(f4se->runtimeVersion),
				GET_EXE_VERSION_MAJOR(CURRENT_RELEASE_RUNTIME),
				GET_EXE_VERSION_MINOR(CURRENT_RELEASE_RUNTIME),
				GET_EXE_VERSION_BUILD(CURRENT_RELEASE_RUNTIME),
				GET_EXE_VERSION_SUB(CURRENT_RELEASE_RUNTIME),
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
		_MESSAGE("load");

		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}

		return true;
	}

};
