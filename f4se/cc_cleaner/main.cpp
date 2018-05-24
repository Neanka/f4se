#include "Shared.h"
#include "main.h"

#include "f4se\GameMenus.h"

std::string mName = "cc_cleaner";
UInt32 mVer = 1;

F4SEScaleformInterface		*g_scaleform = NULL;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;


std::string CCGetConfigOption(const char * section, const char * key)
{
	std::string	result;

	const std::string & configPath = "./Data/MCM/Settings/cc_cleaner.ini";
	if(!configPath.empty())
	{
		char	resultBuf[256];
		resultBuf[0] = 0;

		UInt32	resultLen = GetPrivateProfileString(section, key, NULL, resultBuf, sizeof(resultBuf), configPath.c_str());

		result = resultBuf;
	}

	return result;
}

class Scaleform_getSetting : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args){
		std::string settingId = args->args[0].GetString();
		bool result = true;
		if (settingId == "bMOTDEnabled")
		{
			result = to_bool(CCGetConfigOption("Main","bMOTDEnabled"));
		}
		else if (settingId == "bCCEntryEnabled")
		{
			result = to_bool(CCGetConfigOption("Main","bCCEntryEnabled"));
		}
		else if (settingId == "bModsEntryEnabled")
		{
			result = to_bool(CCGetConfigOption("Main", "bModsEntryEnabled"));
		}
		args->result->SetBool(result);
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	RegisterFunction<Scaleform_getSetting>(f4se_root, view->movieRoot, "getSetting");

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
	} else {
		_MESSAGE("WARNING: Scaleform registration failed.");
	}
	if (currentSWFPathString.find("MainMenu.swf") != std::string::npos) {
		_MESSAGE("Hooking MainMenu menu.");
		//auto root = view->movieRoot;
		//if(!root)
		//	return false;
		GFxValue loader, urlRequest, root;

		movieRoot->GetVariable(&root, "root");

		movieRoot->CreateObject(&loader, "flash.display.Loader");
		movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("cc_cleaner.swf"), 1);

		
		root.SetMember("cc_cleaner_loader", &loader);
		bool injectionSuccess = movieRoot->Invoke("root.cc_cleaner_loader.load", nullptr, &urlRequest, 1);

		movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &loader, 1);

		if (injectionSuccess) {

		} else {
			_MESSAGE("WARNING: cc_cleaner injection failed.");
		}
	} //else {_MESSAGE("Hooking %s menu.",currentSWFPathString.c_str());}

	return true;
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\" + mName + ".log").c_str());

		logMessage("query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name = mName.c_str();
		info->version = mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();


		// Check game version
		if (f4se->runtimeVersion != CURRENT_RUNTIME_VERSION) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.89 only.", f4se->runtimeVersion);
			MessageBox(NULL, "Unsupported runtime version (expected v1.10.89). \ncc_cleaner will be disabled.", "cc_cleaner", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if(!g_scaleform)
		{
			errorMessage("couldn't get scaleform interface");
			return false;
		} else {
			logMessage("got scaleform interface");
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (g_scaleform)
		{
			g_scaleform->Register("cc_cleaner", RegisterScaleform);
			logMessage("Scaleform Register Succeeded");
		}
		return true;
	}

};
