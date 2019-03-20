#include "main.h"
#include "SSWTranslator.h"

std::string mName = "SSW";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEScaleformInterface			* g_scaleform = nullptr;
F4SEMessagingInterface			* g_messaging = nullptr;
F4SEPapyrusInterface			* g_papyrus = NULL;

#include "ScaleformLoader.h"
#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/SafeWrite.h"

#define ScriptFunctionReg_HookTarget_ADDRESS 0x278D421 // E8 ? ? ? ? EB ? 49 8B C4 48 8B 95 08 01 00 00 
#define ScriptFunctionReg_Original_ADDRESS 0x27AC750
#define ScriptFunction_Invoke_HookTarget_ADDRESS 0x30835A0 // Unk_OF()
#define Message_Show_ADDRESS 0x13AEF60 // 89 54 24 10 55 53 57 41 54 41 56 41 57 48 8D 6C 24 88 
#define PlayerDifficultySettingChangedEventDispatcher_ADDRESS 0x00EC3340

int numMenus = 0; // for widget hiding
bool isSurvival = false;

UInt8 iShowIcon = 1;
UInt8 iShowPercents = 1;
UInt8 iShowBar = 1;
UInt8 iShowTextStatus = 1;

UInt8 iSuppressFoodMessages = 1;
UInt8 iSuppressDrinkMessages = 1;
UInt8 iSuppressSleepMessages = 1;

UInt8 iShowInPipboy = 1;

UInt8 iColored = 1;

float fFoodBarX = 37.5;
float fFoodBarY = 9.05;
float fFoodBarScaleX = 1.0;
float fFoodBarScaleY = 1.0;
float fFoodBarRotation = 0.0;
UInt8 iFoodBarVisible = 1;

float fDrinkBarX = 37.5;
float fDrinkBarY = 47;
float fDrinkBarScaleX = 1.0;
float fDrinkBarScaleY = 1.0;
float fDrinkBarRotation = 0.0;
UInt8 iDrinkBarVisible = 1;

float fSleepBarX = 37.5;
float fSleepBarY = 84.95;
float fSleepBarScaleX = 1.0;
float fSleepBarScaleY = 1.0;
float fSleepBarRotation = 0.0;
UInt8 iSleepBarVisible = 1;

#define ReadSettingMainInt(key)	\
	key = GetPrivateProfileInt("Main", #key, key, "./Data/MCM/Settings/SSW.ini"); \
	_MESSAGE("%s=%i", #key, key);

#define ReadSettingMainFloat(key)	\
	GetPrivateProfileStringA("Main", #key, (LPCSTR)std::to_string(key).c_str(), sResult.get(), MAX_PATH, "./Data/MCM/Settings/SSW.ini"); \
	key = std::stof(sResult.get()); \
	_MESSAGE("%s=%f", #key, key);

void ReadSettings()
{
	std::unique_ptr<char[]> sResult(new char[MAX_PATH]);

	ReadSettingMainInt(iShowIcon);
	ReadSettingMainInt(iShowPercents);
	ReadSettingMainInt(iShowBar);
	ReadSettingMainInt(iShowTextStatus);

	ReadSettingMainInt(iSuppressFoodMessages);
	ReadSettingMainInt(iSuppressDrinkMessages);
	ReadSettingMainInt(iSuppressSleepMessages);

	ReadSettingMainInt(iShowInPipboy);

	ReadSettingMainInt(iColored);

	ReadSettingMainFloat(fFoodBarX);
	ReadSettingMainFloat(fFoodBarY);
	ReadSettingMainFloat(fFoodBarScaleX);
	ReadSettingMainFloat(fFoodBarScaleY);
	ReadSettingMainFloat(fFoodBarRotation);
	ReadSettingMainInt(iFoodBarVisible);

	ReadSettingMainFloat(fDrinkBarX);
	ReadSettingMainFloat(fDrinkBarY);
	ReadSettingMainFloat(fDrinkBarScaleX);
	ReadSettingMainFloat(fDrinkBarScaleY);
	ReadSettingMainFloat(fDrinkBarRotation);
	ReadSettingMainInt(iDrinkBarVisible);

	ReadSettingMainFloat(fSleepBarX);
	ReadSettingMainFloat(fSleepBarY);
	ReadSettingMainFloat(fSleepBarScaleX);
	ReadSettingMainFloat(fSleepBarScaleY);
	ReadSettingMainFloat(fSleepBarRotation);
	ReadSettingMainInt(iSleepBarVisible);
}

VMIdentifier* hcScriptIdentifier = nullptr;

SInt32 iFoodPoolStarvingAmount = -256;

SInt32 iDrinkPoolSeverelyDehydratedAmount = -180;

SInt32 iFoodPool = 0;

SInt32 iDrinkPool = 0;

ActorValueInfo* HC_HungerEffect = nullptr;
ActorValueInfo* HC_ThirstEffect = nullptr;
ActorValueInfo* HC_SleepEffect = nullptr;

#define HC_HungerEffect_FormID 0x855
#define HC_ThirstEffect_FormID 0x868
#define HC_SleepEffect_FormID 0x828

UInt32 GetDifficulty()
{
	UInt32 result;

	result = GetINISetting("iDifficulty:GamePlay")->data.u32;
	if (result > 6)
		goto LABEL_8;
	if (result < 0)
		return 0;
	if (result >= 5)
		LABEL_8:
	result = (GetINISetting("bStroud:GamePlay")->data.u8 != 0) + 5;
	return result;
}

class SSW_Menu : public GameMenuBase
{
public:

	enum
	{
		kMessage_UpdateModSettings = 0x10,
		kMessage_UpdateColorSettings,
		kMessage_UpdateAmounts,
		kMessage_UpdateValues
	};

	SSW_Menu() : GameMenuBase()
	{
		flags = kFlag_DoNotPreventGameSave | kFlag_DisableInteractive | kFlag_Unk800000 | kFlag_ApplyDropDownFilter | kFlag_DoNotDeleteOnClose;
		depth = 0x6;
		if (CALL_MEMBER_FN((*g_scaleformManager), LoadMovie)(this, this->movie, "SSW_Menu", "root1.Menu_mc", 2))
		{

			_DMESSAGE("LoadMovie done");

			CreateBaseShaderTarget(this->shaderTarget, this->stage);

			this->shaderTarget->SetFilterColor(false);
			(*g_colorUpdateDispatcher)->eventDispatcher.AddEventSink(this->shaderTarget);

			this->subcomponents.Push(this->shaderTarget);
		}
	}

	virtual void	Invoke(Args * args) final
	{
		switch (args->optionID)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
	}

	virtual void	RegisterFunctions() final
	{
		_DMESSAGE("RegisterFunctions");
	}

	virtual UInt32	ProcessMessage(UIMessage * msg) final
	{
		GFxMovieRoot * root = movie->movieRoot;
		GFxValue ValueToSet;
		switch (msg->type)
		{
		case kMessage_UpdateModSettings:
		{
			_MESSAGE("UpdateModSettings");

			ValueToSet.SetInt(iColored);
			root->SetVariable("root.Menu_mc.iColored", &ValueToSet);

			ValueToSet.SetInt(iShowIcon);
			root->SetVariable("root.Menu_mc.iShowIcon", &ValueToSet);

			ValueToSet.SetInt(iShowPercents);
			root->SetVariable("root.Menu_mc.iShowPercents", &ValueToSet);

			ValueToSet.SetInt(iShowBar);
			root->SetVariable("root.Menu_mc.iShowBar", &ValueToSet);

			ValueToSet.SetInt(iShowTextStatus);
			root->SetVariable("root.Menu_mc.iShowTextStatus", &ValueToSet);

			ValueToSet.SetNumber(fFoodBarX);
			root->SetVariable("root.Menu_mc.fFoodBarX", &ValueToSet);
			ValueToSet.SetNumber(fFoodBarY);
			root->SetVariable("root.Menu_mc.fFoodBarY", &ValueToSet);
			ValueToSet.SetNumber(fFoodBarScaleX);
			root->SetVariable("root.Menu_mc.fFoodBarScaleX", &ValueToSet);
			ValueToSet.SetNumber(fFoodBarScaleY);
			root->SetVariable("root.Menu_mc.fFoodBarScaleY", &ValueToSet);
			ValueToSet.SetNumber(fFoodBarRotation);
			root->SetVariable("root.Menu_mc.fFoodBarRotation", &ValueToSet);
			ValueToSet.SetInt(iFoodBarVisible);
			root->SetVariable("root.Menu_mc.iFoodBarVisible", &ValueToSet);

			ValueToSet.SetNumber(fDrinkBarX);
			root->SetVariable("root.Menu_mc.fDrinkBarX", &ValueToSet);
			ValueToSet.SetNumber(fDrinkBarY);
			root->SetVariable("root.Menu_mc.fDrinkBarY", &ValueToSet);
			ValueToSet.SetNumber(fDrinkBarScaleX);
			root->SetVariable("root.Menu_mc.fDrinkBarScaleX", &ValueToSet);
			ValueToSet.SetNumber(fDrinkBarScaleY);
			root->SetVariable("root.Menu_mc.fDrinkBarScaleY", &ValueToSet);
			ValueToSet.SetNumber(fDrinkBarRotation);
			root->SetVariable("root.Menu_mc.fDrinkBarRotation", &ValueToSet);
			ValueToSet.SetInt(iDrinkBarVisible);
			root->SetVariable("root.Menu_mc.iDrinkBarVisible", &ValueToSet);

			ValueToSet.SetNumber(fSleepBarX);
			root->SetVariable("root.Menu_mc.fSleepBarX", &ValueToSet);
			ValueToSet.SetNumber(fSleepBarY);
			root->SetVariable("root.Menu_mc.fSleepBarY", &ValueToSet);
			ValueToSet.SetNumber(fSleepBarScaleX);
			root->SetVariable("root.Menu_mc.fSleepBarScaleX", &ValueToSet);
			ValueToSet.SetNumber(fSleepBarScaleY);
			root->SetVariable("root.Menu_mc.fSleepBarScaleY", &ValueToSet);
			ValueToSet.SetNumber(fSleepBarRotation);
			root->SetVariable("root.Menu_mc.fSleepBarRotation", &ValueToSet);
			ValueToSet.SetInt(iSleepBarVisible);
			root->SetVariable("root.Menu_mc.iSleepBarVisible", &ValueToSet);

			root->Invoke("root.Menu_mc.UpdateModSettings", nullptr, nullptr, 0);
			break;
		}
		case kMessage_UpdateValues:
		{
			_MESSAGE("UpdateValues");

			ValueToSet.SetInt(iFoodPool);
			root->SetVariable("root.Menu_mc.iFoodPool", &ValueToSet);

			ValueToSet.SetInt(iDrinkPool);
			root->SetVariable("root.Menu_mc.iDrinkPool", &ValueToSet);

			ValueToSet.SetInt((SInt32)(*g_player)->actorValueOwner.GetValue(HC_HungerEffect));
			root->SetVariable("root.Menu_mc.iFoodStatus", &ValueToSet);

			ValueToSet.SetInt((SInt32)(*g_player)->actorValueOwner.GetValue(HC_ThirstEffect));
			root->SetVariable("root.Menu_mc.iDrinkStatus", &ValueToSet);

			ValueToSet.SetInt((SInt32)(*g_player)->actorValueOwner.GetValue(HC_SleepEffect));
			root->SetVariable("root.Menu_mc.iSleepStatus", &ValueToSet);

			root->Invoke("root.Menu_mc.UpdateValues", nullptr, nullptr, 0);
			break;
		}
		case kMessage_UpdateAmounts:
		{
			_MESSAGE("UpdateAmounts");

			ValueToSet.SetInt(iFoodPoolStarvingAmount);
			root->SetVariable("root.Menu_mc.iFoodPoolStarvingAmount", &ValueToSet);

			ValueToSet.SetInt(iDrinkPoolSeverelyDehydratedAmount);
			root->SetVariable("root.Menu_mc.iDrinkPoolSeverelyDehydratedAmount", &ValueToSet);


			root->Invoke("root.Menu_mc.UpdateAmounts", nullptr, nullptr, 0);
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

	static IMenu * CreateSSW_Menu()
	{
		return new SSW_Menu();
	}

	static void UpdateModSettings()
	{
		static BSFixedString menuName("SSW_Menu");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_UpdateModSettings);
	}

	static void UpdateAmounts()
	{
		static BSFixedString menuName("SSW_Menu");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_UpdateAmounts);
	}

	static void UpdateValues()
	{
		static BSFixedString menuName("SSW_Menu");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_UpdateValues);
	}

	static void OpenMenu()
	{
		static BSFixedString menuName("SSW_Menu");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Open);
	}

	static void CloseMenu()
	{
		static BSFixedString menuName("SSW_Menu");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Close);
	}

	static void RegisterMenu()
	{
		static BSFixedString menuName("SSW_Menu");
		if ((*g_ui) != nullptr && !(*g_ui)->IsMenuRegistered(menuName))
		{
			(*g_ui)->Register("SSW_Menu", CreateSSW_Menu);
		}
		_DMESSAGE("RegisterMenu %s", (*g_ui)->IsMenuRegistered(menuName) ? "registered" : "not registered");
	}
};


#include "f4se/PapyrusNativeFunctions.h"

bool SSWtestfunk(StaticFunctionTag *base) {
	_MESSAGE("SSWtestfunk");
	UpdateValues_int();
	return true;

}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("SSWtestfunk", "MyDebug:debugS", SSWtestfunk, vm));
	return true;
}

class Scaleform_UpdateSettings : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		_MESSAGE("Scaleform_UpdateSettings");
		ReadSettings();
		SSW_Menu::UpdateModSettings();
	}
};

class Scaleform_RequestSettings : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		_MESSAGE("Scaleform_RequestSettings");
		ReadSettings();
		GFxValue ValueToSet;
		args->movie->movieRoot->CreateObject(args->result);
		ValueToSet.SetInt(iShowIcon);
		args->result->SetMember("iShowIcon", &ValueToSet);
		ValueToSet.SetInt(iShowPercents);
		args->result->SetMember("iShowPercents", &ValueToSet);
		ValueToSet.SetInt(iShowBar);
		args->result->SetMember("iShowBar", &ValueToSet);
		ValueToSet.SetInt(iShowTextStatus);
		args->result->SetMember("iShowTextStatus", &ValueToSet);
		ValueToSet.SetInt(iColored);
		args->result->SetMember("iColored", &ValueToSet);

		ValueToSet.SetNumber(fFoodBarX);
		args->result->SetMember("fFoodBarX", &ValueToSet);
		ValueToSet.SetNumber(fFoodBarY);
		args->result->SetMember("fFoodBarY", &ValueToSet);
		ValueToSet.SetNumber(fFoodBarScaleX);
		args->result->SetMember("fFoodBarScaleX", &ValueToSet);
		ValueToSet.SetNumber(fFoodBarScaleY);
		args->result->SetMember("fFoodBarScaleY", &ValueToSet);
		ValueToSet.SetNumber(fFoodBarRotation);
		args->result->SetMember("fFoodBarRotation", &ValueToSet);
		ValueToSet.SetInt(iFoodBarVisible);
		args->result->SetMember("iFoodBarVisible", &ValueToSet);

		ValueToSet.SetNumber(fDrinkBarX);
		args->result->SetMember("fDrinkBarX", &ValueToSet);
		ValueToSet.SetNumber(fDrinkBarY);
		args->result->SetMember("fDrinkBarY", &ValueToSet);
		ValueToSet.SetNumber(fDrinkBarScaleX);
		args->result->SetMember("fDrinkBarScaleX", &ValueToSet);
		ValueToSet.SetNumber(fDrinkBarScaleY);
		args->result->SetMember("fDrinkBarScaleY", &ValueToSet);
		ValueToSet.SetNumber(fDrinkBarRotation);
		args->result->SetMember("fDrinkBarRotation", &ValueToSet);
		ValueToSet.SetInt(iDrinkBarVisible);
		args->result->SetMember("iDrinkBarVisible", &ValueToSet);

		ValueToSet.SetNumber(fSleepBarX);
		args->result->SetMember("fSleepBarX", &ValueToSet);
		ValueToSet.SetNumber(fSleepBarY);
		args->result->SetMember("fSleepBarY", &ValueToSet);
		ValueToSet.SetNumber(fSleepBarScaleX);
		args->result->SetMember("fSleepBarScaleX", &ValueToSet);
		ValueToSet.SetNumber(fSleepBarScaleY);
		args->result->SetMember("fSleepBarScaleY", &ValueToSet);
		ValueToSet.SetNumber(fSleepBarRotation);
		args->result->SetMember("fSleepBarRotation", &ValueToSet);
		ValueToSet.SetInt(iSleepBarVisible);
		args->result->SetMember("iSleepBarVisible", &ValueToSet);
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		RegisterFunction<Scaleform_UpdateSettings>(f4se_root, view->movieRoot, "UpdateSettings");
		RegisterFunction<Scaleform_RequestSettings>(f4se_root, view->movieRoot, "RequestSettings");
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
		if (currentSWFPathString.find("ContainerMenu.swf") != std::string::npos)
		{
			//	_DMESSAGE("hooking ContainerMenu");


		}
	}
	return true;
}

void FindHCScriptIdentifier()
{
	hcScriptIdentifier = nullptr;
	TESQuest* hc = DYNAMIC_CAST(LookupFormByID(0x80E), TESForm, TESQuest);
	IObjectHandlePolicy * hp = (*g_gameVM)->m_virtualMachine->GetHandlePolicy();
	UInt64 hdl = hp->Create(hc->kTypeID, hc);
	(*g_gameVM)->m_virtualMachine->GetObjectIdentifier(hdl, "Hardcore:HC_ManagerScript", 1, &hcScriptIdentifier, 0);
	if (hcScriptIdentifier) _MESSAGE("Hardcore:HC_ManagerScript script identifier found");



	VMValue tempvar;

	if (hcScriptIdentifier)
	{
		if (GetScriptVariableValue(hcScriptIdentifier, "::iDrinkPoolSeverelyDehydratedAmount_var", &tempvar))
		{
			iDrinkPoolSeverelyDehydratedAmount = tempvar.data.i;
			_MESSAGE("iDrinkPoolSeverelyDehydratedAmount %d", iDrinkPoolSeverelyDehydratedAmount);
		}
		if (GetScriptVariableValue(hcScriptIdentifier, "::iFoodPoolStarvingAmount_var", &tempvar))
		{
			iFoodPoolStarvingAmount = tempvar.data.i;
			_MESSAGE("iFoodPoolStarvingAmount %d", iFoodPoolStarvingAmount);
		}
		SSW_Menu::UpdateAmounts();
		SSW_Menu::UpdateModSettings();
	}
}

EventResult	TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher)
{
	_DMESSAGE("TESLoadGameEvent recieved");
	isSurvival = (GetDifficulty() == 6);
	if (isSurvival)
	{
		SSW_Menu::OpenMenu();
	}	
	FindHCScriptIdentifier();
	return kEvent_Continue;
}

DECLARE_EVENT_DISPATCHER(PlayerDifficultySettingChanged::Event, PlayerDifficultySettingChangedEventDispatcher_ADDRESS)

EventResult	DifficultyChangedHandler::ReceiveEvent(PlayerDifficultySettingChanged::Event * evn, void * dispatcher)
{
	_DMESSAGE("PlayerDifficultySettingChanged::Event recieved");
	isSurvival = (evn->to == 6);
	if (numMenus > 0 || !isSurvival)
	{
		SSW_Menu::CloseMenu();
	}
	else
	{
		SSW_Menu::OpenMenu();
	}
	return kEvent_Continue;
}



EventResult	MenuOpenCloseHandler::ReceiveEvent(MenuOpenCloseEvent * evn, void * dispatcher)
{
	//_DMESSAGE("MenuOpenCloseEvent recieved %s, %d", evn->menuName.c_str(),evn->isOpen);
	if (!_strcmpi("ContainerMenu", evn->menuName.c_str()) || !_strcmpi("BarterMenu", evn->menuName.c_str()) || !_strcmpi("ExamineMenu", evn->menuName.c_str()) || !_strcmpi("WorkshopMenu", evn->menuName.c_str()) || !_strcmpi("Workshop_CaravanMenu", evn->menuName.c_str()) || !_strcmpi("LevelUpMenu", evn->menuName.c_str()) || !_strcmpi("BookMenu", evn->menuName.c_str()) || !_strcmpi("CookingMenu", evn->menuName.c_str()))
	{

		if (evn->isOpen)
		{
			numMenus++;
		}
		else
		{
			numMenus--;
		}
		if (numMenus > 0 || !isSurvival)
		{
			SSW_Menu::CloseMenu();
		}
		else
		{
			SSW_Menu::OpenMenu();
		}
	}
	return kEvent_Continue;
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		_MESSAGE("kMessage_GameDataReady");

		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);

		static auto pMenuOpenCloseHandler = new MenuOpenCloseHandler();
		(*g_ui)->menuOpenCloseEventSource.AddEventSink(pMenuOpenCloseHandler);

		static auto pDifficultyChangedHandler = new DifficultyChangedHandler();
		GetEventDispatcher<PlayerDifficultySettingChanged::Event>()->AddEventSink(pDifficultyChangedHandler);

		ReadSettings();

		HC_HungerEffect = DYNAMIC_CAST(LookupFormByID(HC_HungerEffect_FormID), TESForm, ActorValueInfo);
		HC_ThirstEffect = DYNAMIC_CAST(LookupFormByID(HC_ThirstEffect_FormID), TESForm, ActorValueInfo);
		HC_SleepEffect = DYNAMIC_CAST(LookupFormByID(HC_SleepEffect_FormID), TESForm, ActorValueInfo);

		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:
		_MESSAGE("kMessage_GameLoaded");
		// Inject translations
		BSScaleformTranslator * translator = (BSScaleformTranslator*)(*g_scaleformManager)->stateBag->GetStateAddRef(GFxState::kInterface_Translator);
		if (translator) {
			SSWTranslator::LoadTranslations(translator);
		}
		SSW_Menu::RegisterMenu();
		break;
	}
}


// 0x80
class ScriptFunction : public IFunction
{
public:
	BSFixedString * functionName;
	BSFixedString*	scriptName;
	BSFixedString*	str20;
	UInt64*			returnType;
	void*			params;
	UInt16			numParams;

};

ScriptFunction* HC_ApplyEffectFunction = nullptr;

typedef UInt32(*_Message_Show)(VirtualMachine* vm, UInt32 stackId, BGSMessage* msg, float param1, float param2, float param3, float param4, float param5, float param6, float param7, float param8, float param9);
RelocAddr <_Message_Show> Message_Show(Message_Show_ADDRESS);
_Message_Show Message_Show_Original = nullptr;

UInt32 Message_Show_Hook(VirtualMachine* vm, UInt32 stackId, BGSMessage* msg, float param1, float param2, float param3, float param4, float param5, float param6, float param7, float param8, float param9)
{
	_MESSAGE("Message_Show_Hook");
	UInt32 result = 0;
	switch (msg->formID)
	{
		// Food effect messages
	case 0x85D:
	case 0x249F41:
	case 0x860:
	case 0x249F3C:
	case 0x85C:
	case 0x249F3D:
	case 0x85B:
	case 0x249F3E:
	case 0x85E:
	case 0x249F40:
	case 0x85F:
	case 0x249F3F:
		if (iSuppressFoodMessages) return result;
		break;
		// Sleep effect messages
	case 0x830:
	case 0x837:
	case 0x832:
	case 0x839:
	case 0x824:
	case 0x825:
	case 0x834:
	case 0x83C:
	case 0x836:
	case 0x83A:
	case 0x833:
	case 0x83B:
	case 0x831:
	case 0x838:
	case 0x835:
	case 0x83D:
		if (iSuppressSleepMessages) return result;
		break;
		// Drink effect messages
	case 0x881:
	case 0x249F44:
	case 0x87D:
	case 0x249F49:
	case 0x880:
	case 0x249F45:
	case 0x87F:
	case 0x249F46:
	case 0x882:
	case 0x249F47:
	case 0x87E:
	case 0x249F48:
		if (iSuppressDrinkMessages) return result;
		break;
	default:
		break;
	}
	result = Message_Show_Original(vm, stackId, msg, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	return result;
}

struct ScriptFunctionRegParam2
{
public:
	BSFixedString functionName;
	BSFixedString scriptName;
	//...
};

typedef void*(*_ScriptFunctionReg)(ScriptFunction* param1, ScriptFunctionRegParam2* param2);
RelocAddr <_ScriptFunctionReg> ScriptFunctionReg_HookTarget(ScriptFunctionReg_HookTarget_ADDRESS);
RelocAddr <_ScriptFunctionReg> ScriptFunctionReg_Original(ScriptFunctionReg_Original_ADDRESS);

void* ScriptFunctionReg_Hook(ScriptFunction* param1, ScriptFunctionRegParam2* param2)
{
	if (!_strcmpi("DamageFatigue", param2->functionName.c_str()) && !_strcmpi("hardcore:hc_managerscript", param2->scriptName.c_str())) // using DamageFatigue instead of ApplyEffect
	{
		_MESSAGE("hardcore:hc_managerscript.ApplyEffect() function address found");
		HC_ApplyEffectFunction = param1;
		unsigned char data[] = { 0xE8, 0x2A, 0xF3, 0x01, 0x00 };
		SafeWriteBuf(ScriptFunctionReg_HookTarget.GetUIntPtr(), &data, sizeof(data));
	}
	return ScriptFunctionReg_Original(param1, param2);
}

typedef UInt32(*_ScriptFunction_Invoke)(ScriptFunction* param1, void* param2, void* param3, VirtualMachine* param4, UInt8 param5);
RelocAddr <_ScriptFunction_Invoke> ScriptFunction_Invoke_HookTarget(ScriptFunction_Invoke_HookTarget_ADDRESS);
_ScriptFunction_Invoke ScriptFunction_Invoke_Original;


void UpdateValues_int()
{
	VMValue FoodPool, DrinkPool;

	if (hcScriptIdentifier)
	{
		if (GetScriptVariableValue(hcScriptIdentifier, "FoodPool", &FoodPool))
		{
			iFoodPool = FoodPool.data.i;
			_MESSAGE("FoodPool %d", iFoodPool);
		}
		if (GetScriptVariableValue(hcScriptIdentifier, "DrinkPool", &DrinkPool))
		{
			iDrinkPool = DrinkPool.data.i;
			_MESSAGE("DrinkPool %d", iDrinkPool);
		}
		SSW_Menu::UpdateValues();
	}
}

UInt32 ScriptFunction_Invoke_Hook(ScriptFunction* param1, void* param2, void* param3, VirtualMachine* param4, UInt8 param5) {

	if (HC_ApplyEffectFunction && param1 == HC_ApplyEffectFunction)
	{
		_MESSAGE("ApplyEffect Hook");
		UpdateValues_int();
	}
	UInt32 result = ScriptFunction_Invoke_Original(param1, param2, param3, param4, param5);
	return result;
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
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_FATALERROR("couldn't get scaleform interface");
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
		if (CheckModDropClientService() == 0)
		{
			_WARNING("WARNING: ModDropClient found.");
			MessageBox(NULL, (LPCSTR)("ModDropClient found. \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		if (g_scaleform)
		{
			g_scaleform->Register("SSW", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);

		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
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

		{
			struct Message_Show_Code : Xbyak::CodeGenerator {
				Message_Show_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x10], edx);
					push(rbp);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(Message_Show.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			Message_Show_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			Message_Show_Original = (_Message_Show)codeBuf;

			g_branchTrampoline.Write5Branch(Message_Show.GetUIntPtr(), (uintptr_t)Message_Show_Hook);
		}

		ScriptFunction_Invoke_Original = HookUtil::SafeWrite64(ScriptFunction_Invoke_HookTarget.GetUIntPtr(), &ScriptFunction_Invoke_Hook);
		g_branchTrampoline.Write5Call(ScriptFunctionReg_HookTarget.GetUIntPtr(), (uintptr_t)ScriptFunctionReg_Hook);
		return true;
	}

};
