
#include "Shared.h"

#include "main.h"
#include "f4se/GameMenus.h"

std::string mName = "removesurvival";
UInt32 mVer = 1;
IDebugLog	gLog;

F4SEScaleformInterface		*g_scaleform = NULL;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;



bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;

	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
	}
	else {
		errorMessage("WARNING: Scaleform registration failed.");
	}
	if (currentSWFPathString.find("MainMenu.swf") != std::string::npos) {
		logMessage("Hooking MainMenu menu.");
		auto root = view->movieRoot;
		if (!root)
			return false;
		GFxValue value;
		value.SetBool(false);
		root->SetVariable("root.Menu_mc.isSurvivalAvailable", &value);
	}
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
			return false;
		}

		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			errorMessage("couldn't get scaleform interface");
			return false;
		}
		else {
			logMessage("got scaleform interface");
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("removesurvival load");
		if (g_scaleform)
		{
			g_scaleform->Register("removesurvival", RegisterScaleform);
			logMessage("Scaleform Register Succeeded");
		}
		return true;
	}

};
