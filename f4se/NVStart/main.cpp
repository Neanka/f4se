
#include "Shared.h"

#include "main.h"
#include "f4se/GameMenus.h"

std::string mName = "NVStart";
UInt32 mVer = 1;
IDebugLog	gLog;

F4SEScaleformInterface		*g_scaleform = NULL;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

std::string NVStartGetConfigOption(const char * section, const char * key)
{
	std::string	result;

	const std::string & configPath = "./Data/MCM/Settings/NVStart.ini";
	if (!configPath.empty())
	{
		char	resultBuf[256];
		resultBuf[0] = 0;

		UInt32	resultLen = GetPrivateProfileString(section, key, NULL, resultBuf, sizeof(resultBuf), configPath.c_str());

		result = resultBuf;
	}

	return result;
}

class Scaleform_getStartLoc : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		std::string StartLoc = NVStartGetConfigOption("Main", "sStartLoc");
		args->movie->movieRoot->CreateString(args->result, StartLoc.c_str());
	}
};

class Scaleform_getAutoStart : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		std::string AutoStart = NVStartGetConfigOption("Main", "bAutoStart");
		bool result = to_bool(AutoStart);

		args->result->SetBool(result);
	}
};

class Scaleform_exe : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		std::string command = args->args[0].GetString();
		ExecuteCommand(command.c_str());
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	RegisterFunction<Scaleform_getStartLoc>(f4se_root, view->movieRoot, "getStartLoc");
	RegisterFunction<Scaleform_getAutoStart>(f4se_root, view->movieRoot, "getAutoStart");
	RegisterFunction<Scaleform_exe>(f4se_root, view->movieRoot, "exe");

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

		GFxValue loader, urlRequest, root;

		movieRoot->GetVariable(&root, "root");

		movieRoot->CreateObject(&loader, "flash.display.Loader");
		movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("NVStart.swf"), 1);


		root.SetMember("NVStart_loader", &loader);
		bool injectionSuccess = movieRoot->Invoke("root.NVStart_loader.load", nullptr, &urlRequest, 1);

		movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &loader, 1);

		if (injectionSuccess) {

		}
		else {
			errorMessage("WARNING: NVStart injection failed.");
		}
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
		//if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_26) {
		//	_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.26 only.", f4se->runtimeVersion);
		//	MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.26). \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
		//	//	return false;
		//}

		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			errorMessage("couldn't get scaleform interface");
			return false;
		}
		else {
			logMessage("got scaleform interface");
		}
		// Get the messaging interface

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("NVStart load");
		if (g_scaleform)
		{
			g_scaleform->Register("NVStart", RegisterScaleform);
			logMessage("Scaleform Register Succeeded");
		}
		InitExeAddress();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		return true;
	}

};
