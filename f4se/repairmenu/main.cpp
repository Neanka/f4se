#include "main.h"

std::string mName = "repairmenu";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

#include "SharedClasses_Pipboy.h"

F4SEPapyrusInterface		*g_papyrus = NULL;

typedef void(*_sub_140C0F860)(void* manager, void* param2);
RelocAddr <_sub_140C0F860> sub_140C0F860_original(0xC15BB0);
RelocAddr <_sub_140C0F860> sub_140C0F860_hooktarget(0xC0BD8F);
#include "PapyrusNativeFunctions.h"

void sub_140C0F860_hook(void* manager, void* param2)
{
	//tracePipboyObjectLight((*g_PipboyDataManager)->inventoryData.inventoryObject);
	_MESSAGE("sub_140C0F860_hook");
	sub_140C0F860_original(manager, param2);
	tracePipboyObject((*g_PipboyDataManager)->inventoryData.inventoryObject);
}

EventResult DC_Function(PlayerDifficultySettingChanged::Event * evn)
{
	_DMESSAGE("PlayerDifficultySettingChanged::Event recieved");
	return kEvent_Continue;
};

bool RMtestfunk(StaticFunctionTag *base) {
	_MESSAGE("repairmenu testfunk");
	//DumpClass(*g_PipboyDataManager, 800);
	//tracePipboyObject((PipboyObject*)&(*g_PipboyDataManager)->mainObject);

	//REGISTER_EVENT_SIMPLE(PlayerDifficultySettingChanged::Event, DC_Function);
	/*
	PipboyObject* xPO = CreatePipboyObject(nullptr);

	PipboyArray* xPA = CreatePipboyArray(xPO);
	CALL_MEMBER_FN(xPO, SetMember)(&BSFixedString("some array"), xPA);

	PipboyObject* xPO1 = CreatePipboyObject(xPA);
	CALL_MEMBER_FN(xPO1, SetMember_BSFixedStringCS)(&BSFixedString("some string var"), &BSFixedString("text"));
	xPA->Insert(xPO1, 0);
	PipboyObject* xPO2 = CreatePipboyObject(xPA);
	xPA->Insert(xPO2, 0);
	tracePipboyObject(xPO);
	*/
	
	return true;
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("RMtestfunk", "MyDebug:debugS", RMtestfunk, vm));
	return true;
}

#include "f4se_common/SafeWrite.h"
#include "f4se_common//BranchTrampoline.h"

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
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (!g_branchTrampoline.Create(1024 * 64))
		{
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr))
		{
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		sig_scan_timer tmr; tmr.start();
		plugin_info.plugin_name = "def_shared";
		SharedClasses_PipboyInit();
		Shared2_Init();
		Shared2_InitEvents();
		//InitReloc(mName.c_str());
		_MESSAGE("Sigscan elapsed: %llu ms.", tmr.stop());
		g_branchTrampoline.Write5Call(sub_140C0F860_hooktarget.GetUIntPtr(), (uintptr_t)sub_140C0F860_hook);
		return true;
	}

};
