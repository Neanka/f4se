#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"
#include "f4se/GameData.h"
#include <shlobj.h>
#include <string>


#include "main.h"
#include "Shared.h"

#include "f4se_common/f4se_version.h"

F4SEPapyrusInterface		*g_papyrus = NULL;

std::string mName = "IsMenuOpenFix";
UInt32 mVer = 1;
IDebugLog	gLog;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se/GameMenus.h"

#include "Globals.h"

bool IsMenuOpen(StaticFunctionTag *, BSFixedString menuName)
{
	return (*G::ui)->IsMenuOpen(&menuName);
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction1<StaticFunctionTag, bool, BSFixedString>("IsMenuOpen", "UI", IsMenuOpen, vm));
	return true;
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\" + mName + ".log").c_str());
		logMessage("query");

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = mName.c_str();
		info->version = mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		// Check game version
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_50) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.50 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.50). \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			//	return false;
		}

		// get the papyrus interface and query its version
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus)
		{
			logMessage("couldn't get papyrus interface");
			return false;
		}
		else {
			logMessage("got papyrus interface");
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			logMessage("Papyrus Register Succeeded");
		}
		G::Init();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		return true;
	}

};
