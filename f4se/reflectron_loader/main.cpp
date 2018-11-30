#include "main.h"

std::string mName = "reflectron_loader";
UInt32 mVer = 1;

F4SEScaleformInterface		*g_scaleform = NULL;
F4SEMessagingInterface			* g_messaging = nullptr;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;


#include "f4se/ScaleformLoader.h"

bool bgtextureMounted = false;
NiTexture * bgtexture = nullptr;

typedef UInt32(*_unkshdrfnc)(BSGFxShaderFXTarget * & component, GFxValue & stage, const char* name);
RelocAddr <_unkshdrfnc> unkshdrfnc(0x0000B3AFA0);
RelocAddr <uintptr_t> unkshdrfnc_HookTarget(0x000B3C423);
_unkshdrfnc unkshdrfnc_Original = nullptr;

UInt32 unkshdrfnc_Hook(BSGFxShaderFXTarget * & component, GFxValue & stage, const char* name)
{
	DumpClass(&component, 20);
	DumpClass(&stage, 20);
	_MESSAGE("%s", name);
	return unkshdrfnc_Original(component, stage, name);
}

class reflectron_loader : public GameMenuBase
{
public:

	BSGFxShaderFXTarget * xst;
	BSGFxShaderFXTarget * xst2;

	enum
	{
		kMessage_UpdateModSettings = 0x10,
		kMessage_UpdateColorSettings
	};

	reflectron_loader() : GameMenuBase()
	{
		flags = 0x0018480;//0x4018480;//  kFlag_DoNotPreventGameSave | kFlag_DisableInteractive | kFlag_Unk800000 | kFlag_ApplyDropDownFilter;//
		depth = 0x9;
		context = 0x22;

		if (CALL_MEMBER_FN((*g_scaleformManager), LoadMovie)(this, this->movie, "reflectron_loader", "root1.Menu_mc", 2))
		{

			_DMESSAGE("LoadMovie done");

			CreateBaseShaderTarget(this->shaderTarget, this->stage);

			//this->shaderTarget->SetFilterColor(false);
			//(*g_colorUpdateDispatcher)->eventDispatcher.AddEventSink(this->shaderTarget);

			this->subcomponents.Push(this->shaderTarget);

			GFxValue xstmc, xstmc2;
			this->movie->movieRoot->GetVariable(&xstmc, "root1.Menu_mc.actualBG_mc");
			xst = new BSGFxShaderFXTarget(&xstmc);
			this->subcomponents.Push(xst);
			//unkshdrfnc(xst2, this->stage, "root1.Menu_mc.tex_bg");
			this->movie->movieRoot->GetVariable(&xstmc2, "root1.Menu_mc.tex_bg");
			xst2 = new BSGFxShaderFXTarget(&xstmc2);
			this->subcomponents.Push(xst2);
			xst2->SetFilterColor(false);

			const char * menuName = "reflectron_loader";
			const char * filePath = "Textures\\F4NV\\Interface\\Reflectron4096x4096.dds";
			const char * imageName = "reflectron";


			LoadTextureByPath(filePath, true, bgtexture, 0, 0, 0);
			if (bgtexture)
			{
				_MESSAGE("texture loaded");
				if (bgtextureMounted)
				{
					_MESSAGE("Already mounted");
				}
				else
				{
					auto imageLoader = (*g_scaleformManager)->imageLoader;
					if (imageLoader)
					{
						bgtexture->name = imageName;
						bgtexture->IncRef();
						imageLoader->MountImage(&bgtexture);
						bgtextureMounted = true;
					}
				}
				// LoadTextureByPath increases refcount
				bgtexture->DecRef();
			}
			this->movie->movieRoot->Invoke("root.Menu_mc.LoadBG", nullptr, nullptr, 0);
		}

	}

	virtual void	Invoke(Args * args) final
	{
		switch (args->optionID)
		{
		case 0:
		{

		}
		break;
		case 1:
		{

		}
		break;
		default:
			break;
		}
	}

	virtual void	RegisterFunctions() final
	{
		_DMESSAGE("RegisterFunctions");
		//this->RegisterNativeFunction("ExitCommandMode", 0);
		//this->RegisterNativeFunction("OpenInventory", 1);
	}

	virtual UInt32	ProcessMessage(UIMessage * msg) final
	{
		GFxMovieRoot * root = movie->movieRoot;
		switch (msg->type)
		{
		case kMessage_UpdateModSettings:
		{
			break;
		}
		default:
			break;
		}
		return this->GameMenuBase::ProcessMessage(msg);
	};

	virtual void	DrawNextFrame(float unk0, void * unk1) final
	{
		//_DMESSAGE("DrawNextFrame");
		return this->GameMenuBase::DrawNextFrame(unk0, unk1);
	};

	static IMenu * Createreflectron_loader()
	{
		return new reflectron_loader();
	}

	static void UpdateModSettings()
	{
		static BSFixedString menuName("reflectron_loader");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_UpdateModSettings);
	}

	static void OpenMenu()
	{
		static BSFixedString menuName("reflectron_loader");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Open);
	}

	static void CloseMenu()
	{
		static BSFixedString menuName("reflectron_loader");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Close);
	}

	static void RegisterMenu()
	{
		static BSFixedString menuName("reflectron_loader");
		if ((*g_ui) != nullptr && !(*g_ui)->IsMenuRegistered(menuName))
		{
			(*g_ui)->Register("reflectron_loader", Createreflectron_loader);
		}
		_DMESSAGE("RegisterMenu %s", (*g_ui)->IsMenuRegistered(menuName) ? "registered" : "not registered");
	}
};

void MessageCallback(F4SEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case F4SEMessagingInterface::kMessage_GameLoaded:
		reflectron_loader::RegisterMenu();
		break;
	case F4SEMessagingInterface::kMessage_GameDataReady:
		break;
	default:
		break;
	}
}

typedef UInt32(*_LooksMenuProcessMessage)(GameMenuBase* menu, UIMessage * message);
//RelocAddr <_LooksMenuProcessMessage> LooksMenuProcessMessage(0x000B3D680);
RelocAddr <_LooksMenuProcessMessage> LooksMenuProcessMessage_HookTarget(0x0002D482E0);

_LooksMenuProcessMessage LooksMenuProcessMessage_Original;



UInt32 LooksMenuProcessMessage_Hook(GameMenuBase* menu, UIMessage * message) {
	UInt32 result = LooksMenuProcessMessage_Original(menu, message);	
	if (message->type == 1)
	{
		//reflectron_loader::OpenMenu();
		// unset kFlag_ApplyDropDownFilter flag because this flag broke semitransparent parts of menus
			//menu->flags &= ~0x8000;
		menu->flags = 0x80C800;
		menu->depth = 5;
	}
	else if (message->type == 3)
	{
		// unmount image when menu closed
		reflectron_loader::CloseMenu();
		auto imageLoader = (*g_scaleformManager)->imageLoader;
		if (imageLoader && bgtexture && bgtextureMounted)
		{
			imageLoader->UnmountImage(&bgtexture);
			bgtexture->DecRef();
			bgtexture = nullptr;
			bgtextureMounted = false;
		}
	}

	return result;
}

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();

		if (currentSWFPathString.find("reflectron_loader.swf") != std::string::npos) {
			
			_MESSAGE("Hooking reflectron_loader menu.");
			return true;
			const char * menuName = "reflectron_loader";
			const char * filePath = "Textures\\F4NV\\Interface\\Reflectron4096x4096.dds";
			const char * imageName = "reflectron";

			
			LoadTextureByPath(filePath, true, bgtexture, 0, 0, 0);
			if (bgtexture)
			{
				_MESSAGE("texture loaded");
				if (bgtextureMounted)
				{
					_MESSAGE("Already mounted");
				}
				else
				{
					auto imageLoader = (*g_scaleformManager)->imageLoader;
					if (imageLoader)
					{
						bgtexture->name = imageName;
						bgtexture->IncRef();
						imageLoader->MountImage(&bgtexture);
						bgtextureMounted = true;
					}
				}
				// LoadTextureByPath increases refcount
				bgtexture->DecRef();
			}
			return true;
			GFxValue arrArgs[2];
			GFxValue urlRequest, root;
			arrArgs[1].SetInt(0);

			movieRoot->GetVariable(&root, "root");

			movieRoot->CreateObject(&arrArgs[0], "flash.display.Loader");
			movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("img://reflectron"), 1);


			root.SetMember("reflectron_loader", &arrArgs[0]);
			bool injectionSuccess = movieRoot->Invoke("root.reflectron_loader.load", nullptr, &urlRequest, 1);

			//GFxValue content;
			//movieRoot->GetVariable(&content, "root.reflectron_loader.content");

			//movieRoot->Invoke("root.Menu_mc.tex_bg.addChildAt", nullptr, arrArgs, 2);
			movieRoot->Invoke("root.Menu_mc.addChild", nullptr, &arrArgs[0], 1);

			// shrink texture to actual display size (hardcoded values for 16x9)
			GFxValue scaleX, scaleY;
			scaleX.SetNumber((double)1280 / 4098);
			scaleY.SetNumber((double)720 / 4098);
			movieRoot->SetVariable("root.reflectron_loader.scaleX", &scaleX);
			movieRoot->SetVariable("root.reflectron_loader.scaleY", &scaleY);
			
			// code to move weight triangle

			//GFxValue triangleX, triangleY;
			//triangleX.SetNumber(1053.25);
			//triangleY.SetNumber(427.35);
			//movieRoot->SetVariable("root.LooksMenu_mc.WeightTriangle_mc.x", &triangleX);
			//movieRoot->SetVariable("root.LooksMenu_mc.WeightTriangle_mc.y", &triangleY);
		}
	}
	return true;
}
#include "f4se_common/BranchTrampoline.h"
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
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging)
		{
			_FATALERROR("couldn't get messaging interface");
			return false;
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		if (g_scaleform)
		{
			g_scaleform->Register("reflectron_loader", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		if (g_messaging != nullptr)
			g_messaging->RegisterListener(g_pluginHandle, "F4SE", MessageCallback);

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

		LooksMenuProcessMessage_Original = HookUtil::SafeWrite64(LooksMenuProcessMessage_HookTarget.GetUIntPtr(), &LooksMenuProcessMessage_Hook);
		
		//unkshdrfnc_Original = HookUtil::SafeWrite64(unkshdrfnc_HookTarget.GetUIntPtr(), &unkshdrfnc_Hook);
		//g_branchTrampoline.Write5Call(unkshdrfnc_HookTarget.GetUIntPtr(), (uintptr_t)unkshdrfnc_Hook);
		return true;
	}

};
