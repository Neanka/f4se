#include "main.h"
#include "Shared.h"

#include "f4se/GameMenus.h"

std::string mName = "XDI_Demo";
UInt32 mVer = 1;
IDebugLog	gLog;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEMessagingInterface		*g_messaging = NULL;

F4SEScaleformInterface		*g_scaleform = NULL;

#include "papfunctions.h"

void GameDataReady()
{
	logMessage("GameDataReady");
}

void GameLoaded()
{
	logMessage("GameLoaded");
	papMessageBox("<b>Welcome to XDI_Demo.</b>\n\nTalk to Marley.\nShe will have a quest and items to barter with you, but not before you progress sufficiently in her dialogue scenes. Talk with her to unlock these additional dialogue options. Enjoy!\n\n\n\n\nAnd don't forget to check out MCM options!");
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {

	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		GameDataReady();
		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:
		GameLoaded();
		break;
	}
}

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
		movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("XDI_Demo.swf"), 1);


		root.SetMember("XDI_Demo_loader", &loader);
		bool injectionSuccess = movieRoot->Invoke("root.XDI_Demo_loader.load", nullptr, &urlRequest, 1);

		movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &loader, 1);

		if (injectionSuccess) {

		}
		else {
			errorMessage("WARNING: XDI_Demo injection failed.");
		}
	}
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
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_26) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.26 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.26). \n"+mName+" will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			errorMessage("couldn't get messaging interface");
			return false;
		}
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}
		else {
			_MESSAGE("got scaleform interface");
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		if (g_scaleform)
		{
			g_scaleform->Register(mName.c_str(), RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		InitExeAddress();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		return true;
	}

};
