#include "main.h"
#include "Shared.h"

#include "f4se/GameMenus.h"
#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

std::string mName = "TIM";
UInt32 mVer = 1;

UInt32 iMode;
std::string sHeaderText;
std::string sBodyText;
UInt32 iInputType;
UInt32 iNumChars;


PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEScaleformInterface		*g_scaleform = NULL;

F4SEPapyrusInterface		*g_papyrus = NULL;

void ResetVariables()
{
	iMode = 0;
	sHeaderText = "Header text";
	sBodyText = "Body text";
	iInputType = 2;
	iNumChars = 26;
}

class Scaleform_SetPlayerName : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		std::string playerName = args->args[0].GetString();
		SetPlayerName_int(nullptr, playerName.c_str());
		
	}
};

class Scaleform_MenuOpenClose : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		std::string menuName = args->args[0].GetString();
		bool state = args->args[1].GetBool();
		MenuOpenClose_int(BSFixedString(menuName.c_str()),state);
	}
};

void TIMOpen(StaticFunctionTag *base, UInt32 type, BSFixedString headerText, BSFixedString bodyText, UInt32 inputType, UInt32 numChars) {
	logMessage("TIMOpen");
	iMode = type;
	sBodyText = bodyText;
	sHeaderText = headerText;
	iInputType = inputType;
	iNumChars = numChars;
	MenuOpenClose_int("SPECIALMenu", true);
}

void SetPlayerName(StaticFunctionTag *base,  BSFixedString playerName) {
	logMessage("SetPlayerName_int");
	SetPlayerName_int(nullptr, playerName.c_str());
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction5 <StaticFunctionTag, void, UInt32, BSFixedString, BSFixedString, UInt32, UInt32>("Open", "TIM:TIM", TIMOpen, vm));
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, BSFixedString>("SetPlayerName", "TIM:TIM", SetPlayerName, vm));
	return true;
}

bool InjectTIM(GFxMovieRoot * movieRoot)
{
	GFxValue loader, urlRequest, root;

	movieRoot->GetVariable(&root, "root");

	movieRoot->CreateObject(&loader, "flash.display.Loader");
	movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("TIM.swf"), 1);


	root.SetMember("TIM_loader", &loader);
	bool injectionSuccess = movieRoot->Invoke("root.TIM_loader.load", nullptr, &urlRequest, 1);

	movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &loader, 1);

	if (injectionSuccess) {
		logMessage("TIM injection successed.");
	}
	else {
		errorMessage("WARNING: TIM injection failed.");
	}
	return injectionSuccess;
}

bool InjectVT(GFxMovieRoot * movieRoot)
{
	GFxValue loader, urlRequest, root;

	movieRoot->GetVariable(&root, "root");

	movieRoot->CreateObject(&loader, "flash.display.Loader");
	movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("VigorTestor.swf"), 1);


	root.SetMember("VigorTestor_loader", &loader);
	bool injectionSuccess = movieRoot->Invoke("root.VigorTestor_loader.load", nullptr, &urlRequest, 1);

	movieRoot->Invoke("root.addChild", nullptr, &loader, 1);

	if (injectionSuccess) {

	}
	else {
		errorMessage("WARNING: VigorTestor injection failed.");
	}
	return injectionSuccess;
}

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	RegisterFunction<Scaleform_MenuOpenClose>(f4se_root, view->movieRoot, "MenuOpenClose");
	RegisterFunction<Scaleform_SetPlayerName>(f4se_root, view->movieRoot, "SetPlayerName");

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;

	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
	}
	else {
		errorMessage("WARNING: Scaleform registration failed.");
	}
	if (currentSWFPathString.find("SPECIALMenu.swf") != std::string::npos) {
		logMessage("Hooking SPECIAL menu.");
		auto root = view->movieRoot;
		if (!root)
			return false;
		if (iMode==42)
		{
			InjectVT(root);
		}
		else if (iMode>0)
		{
			GFxValue rootObj; movieRoot->GetVariable(&rootObj, "root");
			GFxValue tim; movieRoot->CreateObject(&tim);
			rootObj.SetMember("tim", &tim);
			GFxValue gMode, gHeaderText, gBodyText, gInputType, gNumChars;
			gMode.SetInt(iMode);
			movieRoot->CreateString(&gHeaderText, sHeaderText.c_str());
			movieRoot->CreateString(&gBodyText, sBodyText.c_str());
			gInputType.SetInt(iInputType);
			gNumChars.SetInt(iNumChars);
			tim.SetMember("Mode", &gMode);
			tim.SetMember("HeaderText", &gHeaderText);
			tim.SetMember("BodyText", &gBodyText);
			tim.SetMember("InputType", &gInputType);
			tim.SetMember("NumChars", &gNumChars);

			InjectTIM(root);
			GFxValue value;
			value.SetInt(720);
			root->SetVariable("root.Menu_mc.y", &value);
		
			value.SetInt(-435);
			root->SetVariable("root.Menu_mc.Background_mc.y", &value);
			value.SetInt(365);
			root->SetVariable("root.Menu_mc.Background_mc.x", &value);
			value.SetInt(550);
			root->SetVariable("root.Menu_mc.Background_mc.width", &value);
			value.SetInt(150);
			root->SetVariable("root.Menu_mc.Background_mc.height", &value);
		}
		

		ResetVariables();
	}
	return true;
}
//args->movie->movieRoot->CreateString(args->result, sHeaderText.c_str());
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
			errorMessage("couldn't get papyrus interface");
			return false;
		}
		else {
			logMessage("got papyrus interface");
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
		logMessage("load");
		InitExeAddress();
		InitTIMAddress();
		InitUIManager();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			logMessage("Papyrus Register Succeeded");
		}
		if (g_scaleform)
		{
			g_scaleform->Register(mName.c_str(), RegisterScaleform);
			logMessage("Scaleform Register Succeeded");
		}
		ResetVariables();
		return true;
	}

};
