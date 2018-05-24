#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"

#include <shlobj.h>
#include <string>

#include "main.h"
#include "Shared.h"
#include "Events.h"
#include "eventsx.h"
#include "Events3.h"

#include "f4se_common/f4se_version.h"
#include "papfunctions.h"

std::string mName = "def_w_ammo3";
UInt32 mVer = 1;


PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;
F4SEScaleformInterface		*g_scaleform = NULL;


class PlayerCrosshairModeEventSink : public BSTEventSink<PlayerCrosshairModeEvent>
{
public:
	virtual    EventResult    ReceiveEvent(PlayerCrosshairModeEvent * evn, void * dispatcher)
	{
		_MESSAGE("PlayerCrosshairModeEvent");

		DumpClass(evn, 30);

		return kEvent_Continue;
	};
};

PlayerCrosshairModeEventSink _PlayerCrosshairModeEventSink;

struct VATSCommandTargetEvent
{
	UInt32				targetRefHandle;		// 00
};

class VATSCommandTargetEventSink : public BSTEventSink<VATSCommandTargetEvent>
{
public:
	virtual    EventResult    ReceiveEvent(VATSCommandTargetEvent * evn, void * dispatcher)
	{
		_MESSAGE("VATSCommandTargetEvent");

		DumpClass(evn, 30);
		TESObjectREFR * pRef = nullptr;
		LookupREFRByHandle(&(evn->targetRefHandle), &pRef);
		if (pRef != nullptr)
		{
			_MESSAGE("%s", pRef->baseForm->GetFullName());

		}
		return kEvent_Continue;
	};
};

VATSCommandTargetEventSink _VATSCommandTargetEventSink;



class CombatEventSink : public BSTEventSink<TESCombatEvent>
{
public:
	virtual    EventResult    ReceiveEvent(TESCombatEvent * evn, void * dispatcher)
	{
		_MESSAGE("TESCombatEvent");
		if (evn->source != nullptr)
		{

		}
		else
		{
			_MESSAGE("evn->source = nullptr");
		}
		if (evn->target != nullptr)
		{

		}
		else
		{
			_MESSAGE("evn->target = nullptr");
		}
		//DumpClass(evn, 20);
		return kEvent_Continue;
	};
};

CombatEventSink g_combatSink;

class PlayerAmmoCountEventSink : public BSTEventSink<PlayerAmmoCountEvent>
{
public:
    virtual    EventResult    ReceiveEvent(PlayerAmmoCountEvent * evn, void * dispatcher) override
    {  
		_MESSAGE("PlayerAmmoCountEvent");
		//DumpClass(evn,20);
        return kEvent_Continue;
    }
};

PlayerAmmoCountEventSink playerAmmoCountEventSink;

class HUDEnemyHealthDisplayEventSink : public BSTEventSink<HUDEnemyHealthDisplayEvent>
{
public:
	virtual    EventResult    ReceiveEvent(HUDEnemyHealthDisplayEvent * evn, void * dispatcher) override
	{
		_MESSAGE("HUDEnemyHealthDisplayEvent");
		if (evn->show) {
			_MESSAGE("HUDEnemyHealthDisplayEvent show");
			_MESSAGE("Target: %s", evn->name.c_str());
			_MESSAGE("Health: %.6f", evn->healthPercent);
		}
		else {
			_MESSAGE("HUDEnemyHealthDisplayEvent hide");
		}
		return kEvent_Continue;
	}
};

HUDEnemyHealthDisplayEventSink _HUDEnemyHealthDisplayEventSink;

class ViewCasterUpdateEventSink : public BSTEventSink<ViewCasterUpdateEvent>
{
public:
	virtual    EventResult    ReceiveEvent(ViewCasterUpdateEvent * evn, void * dispatcher) override
	{
		_MESSAGE("ViewCasterUpdateEvent");
		//DumpClass(evn, 20);
		return kEvent_Continue;
	}
};

ViewCasterUpdateEventSink _ViewCasterUpdateEventSink;

class PlayerWeaponReloadEventSink : public BSTEventSink<PlayerWeaponReloadEvent>
{
public:
	virtual    EventResult    ReceiveEvent(PlayerWeaponReloadEvent * evn, void * dispatcher) override
	{
		_MESSAGE("PlayerWeaponReloadEvent");
		//DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

PlayerWeaponReloadEventSink _PlayerWeaponReloadEventSink;

class AnimationDataSetupEventSink : public BSTEventSink<AnimationDataSetupEvent>
{
public:
	virtual    EventResult    ReceiveEvent(AnimationDataSetupEvent * evn, void * dispatcher) override
	{
		_MESSAGE("AnimationDataSetupEvent");
		DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

AnimationDataSetupEventSink _AnimationDataSetupEventSink;

class AnimationDataCleanupEventSink : public BSTEventSink<AnimationDataCleanupEvent>
{
public:
	virtual    EventResult    ReceiveEvent(AnimationDataCleanupEvent * evn, void * dispatcher) override
	{
		_MESSAGE("AnimationDataCleanupEvent");
		DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

AnimationDataCleanupEventSink _AnimationDataCleanupEventSink;

class TESHitEventSink : public BSTEventSink<TESHitEvent_x>
{
public:
	virtual    EventResult    ReceiveEvent(TESHitEvent_x * evn, void * dispatcher) override
	{
		_MESSAGE("TESHitEvent");
		//DumpClass(evn->target, 40);
		
		return kEvent_Continue;
	}
};

TESHitEventSink _TESHitEventSink;

class TESEquipEventSink : public BSTEventSink<TESEquipEvent>
{
public:
	virtual    EventResult    ReceiveEvent(TESEquipEvent * evn, void * dispatcher) override
	{
		_MESSAGE("TESEquipEvent: %s %s %#x",evn->ref->baseForm->GetFullName(),evn->equip?"equip":"unequip",evn->FormID);
		DumpClass(evn, 40);
		return kEvent_Continue;
	}
};

TESEquipEventSink _TESEquipEventSink;



class WorkshopNPCTransferEventSink : public BSTEventSink<WorkshopNPCTransferEvent>
{
public:
	virtual    EventResult    ReceiveEvent(WorkshopNPCTransferEvent * evn, void * dispatcher) override
	{
		_MESSAGE("WorkshopNPCTransferEvent: %s going to %s with %s keyword", evn->NPCref->baseForm->GetFullName(), evn->targetloc->fullName.name.c_str(), evn->keyword->keyword.c_str());
		return kEvent_Continue;
	}
};

WorkshopNPCTransferEventSink _WorkshopNPCTransferEventSink;




class HolotapePlayEventSink : public BSTEventSink<HolotapePlayEvent>
{
public:
	virtual    EventResult    ReceiveEvent(HolotapePlayEvent * evn, void * dispatcher) override
	{
		//DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

HolotapePlayEventSink _HolotapePlayEventSink;

class BGSOnPlayerFireWeaponEventSink : public BSTEventSink<BGSOnPlayerFireWeaponEvent>
{
public:
	virtual    EventResult    ReceiveEvent(BGSOnPlayerFireWeaponEvent * evn, void * dispatcher) override
	{
		//DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

BGSOnPlayerFireWeaponEventSink _BGSOnPlayerFireWeaponEventSink;

typedef bool(*_Actor_Unk_C4_Int)(Actor* actor);
class TESContainerChangedEventSink : public BSTEventSink<TESContainerChangedEvent>
{
public:
	virtual    EventResult    ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("TESContainerChangedEvent");




		/*uintptr_t ea = 0xBD73B7; // 48 8D 8E C8 00 00 00 83 F8 02
		ea += 0xC; // offset
		SInt32 rel32 = 0;
		RVAUtils::ReadMemory(RelocationManager::s_baseAddr+ea+1, &rel32, sizeof(SInt32)); // 1 - indirectOffset
		ea += 5 + rel32; // 5 - instruction length

		ea += 9;
		RVAUtils::ReadMemory(RelocationManager::s_baseAddr + ea + 1, &rel32, sizeof(SInt32)); // 1 - indirectOffset
		ea += 5 + rel32; // 5 - instruction length

		char buff[100];
		snprintf(buff, sizeof(buff), "TESContainerChangedEvent address %p", ea);
		papNotification(buff);*/
		//auto Actor_Unk_C4_Int = Utils::GetVirtualFunction<_Actor_Unk_C4_Int>((Actor*)(*g_player), 0x8c);
		//_MESSAGE("%p", (uintptr_t)Actor_Unk_C4_Int-RelocationManager::s_baseAddr);
		//changesex((*g_player));
//		_MESSAGE("%i %s moved from %s to %s", evn->count, (TESForm*)LookupFormByID(evn->itemFormID)->GetFullName(), ((TESObjectREFR*)LookupFormByID(evn->sourceContainerFormID))->baseForm->GetFullName(), ((TESObjectREFR*)LookupFormByID(evn->targetContainerFormID))->baseForm->GetFullName());
//		DumpClass(evn, 100);
		return kEvent_Continue;
	}
};

TESContainerChangedEventSink _TESContainerChangedEventSink;




class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override
	{
		RegisterEvents();
		gameloaded = true;
		return kEvent_Continue;
	}
};


F4SEMessagingInterface		*g_messaging = NULL;


void GameDataReady()
{
	static auto pLoadGameHandler = new TESLoadGameHandler();
	GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);

}

bool TESHitEvent_event_sink()
{
	// Add TESHitEvent event sink
	auto eventDispatcher = GetEventDispatcher<TESHitEvent_x>();
	eventDispatcher->lock.Lock();
	for (int i = 0; i < eventDispatcher->eventSinks.count; i++) {
		if (eventDispatcher->eventSinks[i] == &_TESHitEventSink)
			return false;
	}
	eventDispatcher->eventSinks.Push(&_TESHitEventSink);
	eventDispatcher->lock.Release();
	return true;
}

void RegisterEvents()
{
	/*
	auto PlayerAmmoCountEventEventDispatcher = GET_EVENT_DISPATCHER(PlayerAmmoCountEvent);
	if (PlayerAmmoCountEventEventDispatcher) {
		PlayerAmmoCountEventEventDispatcher->AddEventSink(&playerAmmoCountEventSink);
	}
	auto HUDEnemyHealthDisplayEventDispatcher = GET_EVENT_DISPATCHER(HUDEnemyHealthDisplayEvent);
	if (HUDEnemyHealthDisplayEventDispatcher) {
		HUDEnemyHealthDisplayEventDispatcher->AddEventSink(&_HUDEnemyHealthDisplayEventSink);
	}
	auto ViewCasterUpdateEventDispatcher = GET_EVENT_DISPATCHER(ViewCasterUpdateEvent);
	if (ViewCasterUpdateEventDispatcher) {
		ViewCasterUpdateEventDispatcher->AddEventSink(&_ViewCasterUpdateEventSink);
	}

	auto PlayerWeaponReloadEventDispatcher = GET_EVENT_DISPATCHER(PlayerWeaponReloadEvent);
	if (PlayerWeaponReloadEventDispatcher) {
		PlayerWeaponReloadEventDispatcher->AddEventSink(&_PlayerWeaponReloadEventSink);
	}

	auto AnimationDataSetupEventDispatcher = GET_EVENT_DISPATCHER(AnimationDataSetupEvent);
	if (AnimationDataSetupEventDispatcher) {
		AnimationDataSetupEventDispatcher->AddEventSink(&_AnimationDataSetupEventSink);
	}

	auto AnimationDataCleanupEventDispatcher = GET_EVENT_DISPATCHER(AnimationDataCleanupEvent);
	if (AnimationDataCleanupEventDispatcher) {
		AnimationDataCleanupEventDispatcher->AddEventSink(&_AnimationDataCleanupEventSink);
	}
	*/
//	GetEventDispatcher<TESCombatEvent>()->AddEventSink(&g_combatSink);
//	GetEventDispatcher<TESEquipEvent>()->AddEventSink(&_TESEquipEventSink);
//	TESHitEvent_event_sink();
	
//	GetEventDispatcher<WorkshopNPCTransferEvent>()->AddEventSink(&_WorkshopNPCTransferEventSink);
//	GetEventDispatcher<Workshop::PowerOnEvent>()->AddEventSink(&_Workshop__PowerOnEventSink);
//	GetEventDispatcher<Workshop::PowerOffEvent>()->AddEventSink(&_Workshop__PowerOffEventSink);
//	GetEventDispatcher<Workshop::ItemGrabbedEvent>()->AddEventSink(&_Workshop__ItemGrabbedEventSink);
//	GetEventDispatcher<Workshop::ItemRepairedEvent>()->AddEventSink(&_Workshop__ItemRepairedEventSink);
//	GetEventDispatcher<Workshop::ItemPlacedEvent>()->AddEventSink(&_Workshop__ItemPlacedEventSink);
//	GetEventDispatcher<Workshop::ItemMovedEvent>()->AddEventSink(&_Workshop__ItemMovedEventSink);
//	GetEventDispatcher<Workshop::ItemDestroyedEvent>()->AddEventSink(&_Workshop__ItemDestroyedEventSink);

//	GetEventDispatcher<HolotapePlayEvent>()->AddEventSink(&_HolotapePlayEventSink);
	
//	GetEventDispatcher<BGSOnPlayerFireWeaponEvent>()->AddEventSink(&_BGSOnPlayerFireWeaponEventSink);

//	GetEventDispatcher<TESContainerChangedEvent>()->AddEventSink(&_TESContainerChangedEventSink);
//	auto PlayerCrosshairModeEventDispatcher = GET_EVENT_DISPATCHER(PlayerCrosshairModeEvent);
//	if (PlayerCrosshairModeEventDispatcher) {
//		PlayerCrosshairModeEventDispatcher->AddEventSink(&_PlayerCrosshairModeEventSink);
//	}
	//RegisterAllEvents();
	auto VATSCommandTargetEventDispatcher = GET_EVENT_DISPATCHER(VATSCommandTargetEvent);
	if (VATSCommandTargetEventDispatcher) {
		VATSCommandTargetEventDispatcher->AddEventSink(&_VATSCommandTargetEventSink);
	}
	//registerextraevents();
}


void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
    switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		GameDataReady();
		break;
    case F4SEMessagingInterface::kMessage_PostLoadGame:

        break;

    }
}

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

F4SEPapyrusInterface		*g_papyrus = NULL;

void registerevent(StaticFunctionTag *)
{
	logMessage("registerevent");
}

bool DoMagic(StaticFunctionTag *base) {
	//startdump = true;
	logMessage("DoMagic");
	DumpClass(*g_favoritesManager, 100);
	DumpClass(*g_PipboyDataManager, 500);
	DumpClass((*g_PipboyDataManager)->inventoryObjects[0], 30);

	//((*g_PipboyDataObject)->inventoryObjects[0])->table.Dump();
	for (size_t i = 0; i < (*g_PipboyDataManager)->inventoryObjects.count; i++)
	{
		_MESSAGE("\n\n\t\t====================================================");
		tracePipboyObj((*g_PipboyDataManager)->inventoryObjects[i]);
	}
	
	
	//RegisterAllEvents();


	//changesex((*g_player));
	return true;
}



bool DoMagic2(StaticFunctionTag *base) {

	logMessage("DoMagic2");

	//PlaySound_int("UIMenuOK");

//	DumpClass(_unk5A14C38,10);
//	DumpClass(_unk5A14C00, 10);
//	_MESSAGE("%s", (*_unk5A14C00)->GetFullName());




	//DumpClass(*_unk5AA0238, 4);

	//TESRace* temprace = ((TESNPC*)(*g_player)->baseForm)->race.race;
	//DumpClass(temprace, 0x6C8/8);
	//startdumps = !startdumps;



	/*TESAmmo* ammo = DYNAMIC_CAST(LookupFormByID(0x1F66B),TESForm, TESAmmo);
	unkstruct _unkstruct = {};
	_unkstruct.form = ammo;
	_unkstruct.count = 1;
	DumpClass(&_unkstruct, 11);
	unkstruct1 _unkstruct1 = {};
	_unkstruct1.ref = (*g_player);
	DumpClass(&_unkstruct1, 2);
	testF3(&_unkstruct1, &_unkstruct);*/

	return true;
}

bool exe(StaticFunctionTag *base, BSFixedString str) {

	logMessage("exe");
	ExecuteCommand(str);
	return true;
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, bool, BSFixedString>("exe", "MyDebug:debugS", exe, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("DoMagic", "MyDebug:debugS", DoMagic, vm));
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("DoMagic2", "MyDebug:debugS", DoMagic2, vm));
	return true;
}
#include "f4se/ObScript.h"
#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"

class Scaleform_getDT : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
	// here code to get u DT value
		auto val = 14;
		args->result->SetInt(val);
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
		/*if (currentSWFPathString.find("PipboyMenu.swf") != std::string::npos)
		{
			if (!movieRoot)
				return false;
			GFxValue loader, urlRequest, root;
			movieRoot->GetVariable(&root, "root");
			movieRoot->CreateObject(&loader, "flash.display.Loader");
			movieRoot->CreateObject(&urlRequest, "flash.net.URLRequest", &GFxValue("xxx/dt_pipboy_bottom_bar_widget.swf"), 1);
			root.SetMember("dt_pipboy_bottom_bar_widget_loader", &loader);
			GFxValue codeObj;
			movieRoot->GetVariable(&codeObj, "root.Menu_mc.BGSCodeObj");
			if (!codeObj.IsUndefined()) {
				RegisterFunction<Scaleform_getDT>(&codeObj, movieRoot, "getDT");
			}
			movieRoot->Invoke("root.dt_pipboy_bottom_bar_widget_loader.load", nullptr, &urlRequest, 1);
			movieRoot->Invoke("root.Menu_mc.BottomBar_mc.Info_mc.addChild", nullptr, &loader, 1);
		}*/
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
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_75) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.75 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.75). \n"+mName+" will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			//return false;
		}

		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			errorMessage("couldn't get messaging interface");
			return false;
		}
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if(!g_papyrus)
		{
			errorMessage("couldn't get papyrus interface");
			return false;
		} else {
			logMessage("got papyrus interface");
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
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			logMessage("Papyrus Register Succeeded");
		}
		if (g_scaleform)
		{
			g_scaleform->Register("defammo3", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		InitExeAddress();
		InitAddresses();
		//InitTIMAddress();
		InitUIManager();
		//InitSexChangeAddresses();
		//Debug_Events_Init();

		RVAManager::UpdateAddresses(f4se->runtimeVersion);

		//_MESSAGE("ObScriptCommands");
		//for (ObScriptCommand* iter = g_firstObScriptCommand; iter->opcode < (kObScript_NumObScriptCommands + kObScript_ScriptOpBase); iter++) {
		//	if (strcmp(iter->longName, "AddItem") == 0) {
		//	if (iter->params)
		//	{
		//		_MESSAGE("%s: numParams: %i)", iter->longName, iter->numParams);
		//		DumpClass(iter->params, iter->numParams*2);
		//	}

			//_MESSAGE("%s (%s): 0x%08X", iter->longName, iter->shortName, (uintptr_t)iter->execute-RelocationManager::s_baseAddr);
			//}
		//}
		//_MESSAGE("ConsoleCommands");
		//for (ObScriptCommand* iter = g_firstConsoleCommand; iter->opcode < (kObScript_NumConsoleCommands + kObScript_ConsoleOpBase); iter++) {
		//	_MESSAGE("%s (%s): 0x%08X", iter->longName, iter->shortName, (uintptr_t)iter->execute - RelocationManager::s_baseAddr);
		//}
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
	/*	{
			struct CalcDR_Code : Xbyak::CodeGenerator {
				CalcDR_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(rax, rsp);
					sub(rsp, 0x88);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(CalculateDR.GetUIntPtr() + 10);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			CalcDR_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			CalculateDR_Original = (_CalculateDR)codeBuf;

			g_branchTrampoline.Write6Branch(CalculateDR.GetUIntPtr(), (uintptr_t)CalculateDR_Hook);
		}
*/ /*
		{
			struct ModAV_h_Code : Xbyak::CodeGenerator {
				ModAV_h_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x08], rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(ModAV_h.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			ModAV_h_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			ModAV_h_Original = (_ModAV_h)codeBuf;

			g_branchTrampoline.Write5Branch(ModAV_h.GetUIntPtr(), (uintptr_t)ModAV_h_Hook);
		} */
		//ModAV_h_Original = Utils::Hook(ModAV_h_Hook, ModAV_h.GetUIntPtr());

		/*{
			struct sub_1405BA310_Code : Xbyak::CodeGenerator {
				sub_1405BA310_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x08], rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(sub_1405BA310.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			sub_1405BA310_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			sub_1405BA310_Original = (_sub_1405BA310)codeBuf;

			g_branchTrampoline.Write5Branch(sub_1405BA310.GetUIntPtr(), (uintptr_t)sub_1405BA310_Hook);
		}

		{
			struct sub_1405B8E70_Code : Xbyak::CodeGenerator {
				sub_1405B8E70_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x08], rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(sub_1405B8E70.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			sub_1405B8E70_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			sub_1405B8E70_Original = (_sub_1405B8E70)codeBuf;

			g_branchTrampoline.Write5Branch(sub_1405B8E70.GetUIntPtr(), (uintptr_t)sub_1405B8E70_Hook);
		}

		{
			struct sub_1405B9900_Code : Xbyak::CodeGenerator {
				sub_1405B9900_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;
					push(rbx);
					sub(rsp, 0x30);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(sub_1405B9900.GetUIntPtr() + 6);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			sub_1405B9900_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			sub_1405B9900_Original = (_sub_1405B9900)codeBuf;

			g_branchTrampoline.Write6Branch(sub_1405B9900.GetUIntPtr(), (uintptr_t)sub_1405B9900_Hook);
		}*/
		
		/*{
		struct ParseParams_Code : Xbyak::CodeGenerator {
			ParseParams_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp + 0x20], r9);
				jmp(ptr[rip + retnLabel]);

				L(retnLabel);
				dq(ParseParams.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		ParseParams_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		ParseParams_Original = (_ParseParams)codeBuf;

		g_branchTrampoline.Write5Branch(ParseParams.GetUIntPtr(), (uintptr_t)ParseParams_Hook);
		}
		return true;
	}*/
		/*{
		struct testF_Code : Xbyak::CodeGenerator {
			testF_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp+0x8],rbx);
				jmp(ptr[rip + retnLabel]);

				L(retnLabel);
				dq(testF.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		testF_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		testF_Original = (_testF)codeBuf;

		g_branchTrampoline.Write5Branch(testF.GetUIntPtr(), (uintptr_t)testF_Hook);
		}
		*/

	/*	{
			struct testF1_Code : Xbyak::CodeGenerator {
				testF1_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x20], r9);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(testF1.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			testF1_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			testF1_Original = (_testF1)codeBuf;

			g_branchTrampoline.Write5Branch(testF1.GetUIntPtr(), (uintptr_t)testF1_Hook);
		}*/

	/*	{
			struct testF2_Code : Xbyak::CodeGenerator {
				testF2_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(r10d, r8d);
					mov(r11, rdx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(testF2.GetUIntPtr() + 6);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			testF2_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			testF2_Original = (_testF2)codeBuf;

			g_branchTrampoline.Write6Branch(testF2.GetUIntPtr(), (uintptr_t)testF2_Hook);
		}*/
/*
		{
			struct testF3_Code : Xbyak::CodeGenerator {
				testF3_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					push(rbp);
					push(r14);
					push(r15);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(testF3.GetUIntPtr() + 6);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			testF3_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			testF3_Original = (_testF3)codeBuf;

			g_branchTrampoline.Write6Branch(testF3.GetUIntPtr(), (uintptr_t)testF3_Hook);
		}*/
/*
		{
		struct dispatcher_Code : Xbyak::CodeGenerator {
			dispatcher_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;
				Xbyak::Label foo;
				sub(rsp, 0x28);
				mov(eax, ptr[rip + foo]);
				L(foo);
				dq(0x591BA38 + RelocationManager::s_baseAddr);

				jmp(ptr[rip + retnLabel]);

				L(retnLabel);
				dq(dispatcher.GetUIntPtr() + 10);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		dispatcher_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		dispatcher_Original = (_dispatcher)codeBuf;

		g_branchTrampoline.Write6Branch(dispatcher.GetUIntPtr(), (uintptr_t)dispatcher_Hook);
		}
		*//*
		{
			struct aSETPP_Code : Xbyak::CodeGenerator {
				aSETPP_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					sub(rsp, 0x28);
					mov(ptr[rcx + 0xCF1], dl);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(aSETPP.GetUIntPtr() + 10);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			aSETPP_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			aSETPP_Original = (_aSETPP)codeBuf;

			g_branchTrampoline.Write6Branch(aSETPP.GetUIntPtr(), (uintptr_t)aSETPP_Hook);
		}
		{
			struct s140EC19A0_Code : Xbyak::CodeGenerator {
				s140EC19A0_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x10], rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(s140EC19A0.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			s140EC19A0_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			s140EC19A0_Original = (_s140EC19A0)codeBuf;

			g_branchTrampoline.Write5Branch(s140EC19A0.GetUIntPtr(), (uintptr_t)s140EC19A0_Hook);
		}
		*/
		/*{
		struct sub_140B39750_Code : Xbyak::CodeGenerator {
			sub_140B39750_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp + 8], rbx);
				jmp(ptr[rip + retnLabel]);

				L(retnLabel);
				dq(sub_140B39750.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		sub_140B39750_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		sub_140B39750_Original = (_sub_140B39750)codeBuf;

		g_branchTrampoline.Write5Branch(sub_140B39750.GetUIntPtr(), (uintptr_t)sub_140B39750_Hook);
		}*/
		{
		struct sub_140B3BB20_Code : Xbyak::CodeGenerator {
			sub_140B3BB20_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				push(rbx);
				sub(rsp, 0x20);
				jmp(ptr[rip + retnLabel]);

				L(retnLabel);
				dq(sub_140B3BB20.GetUIntPtr() + 6);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		sub_140B3BB20_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		sub_140B3BB20_Original = (_sub_140B3BB20)codeBuf;

		/*{ // pipboy item selection hook
			struct sub_01A3530_Code : Xbyak::CodeGenerator {
				sub_01A3530_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp+8],rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(sub_01A3530.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			sub_01A3530_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			sub_01A3530_Original = (_sub_01A3530)codeBuf;

			g_branchTrampoline.Write5Branch(sub_01A3530.GetUIntPtr(), (uintptr_t)sub_01A3530_Hook);
		}*/

		{ // pipboy item selection hook
			struct PipboyMenu_SelectItem_Code : Xbyak::CodeGenerator {
				PipboyMenu_SelectItem_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 8], rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(PipboyMenu_SelectItem.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			PipboyMenu_SelectItem_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			PipboyMenu_SelectItem_Original = (_PipboyMenu_SelectItem)codeBuf;

			g_branchTrampoline.Write5Branch(PipboyMenu_SelectItem.GetUIntPtr(), (uintptr_t)PipboyMenu_SelectItem_Hook);
		}

		{
			struct sub_1A3650_Code : Xbyak::CodeGenerator {
				sub_1A3650_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 0x10], edx);
					sub(rsp, 0x38);
					//mov(rax, rsp);
					//mov(ptr[rax + 0x18], r8d);
					//mov(ptr[rsp + 0x18], rbp);
					//push(rbx);
					//push(rsi);
					//push(rdi);
					//sub(rsp,0x20);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(sub_1A3650.GetUIntPtr() + 8);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			sub_1A3650_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			sub_1A3650_Original = (_sub_1A3650)codeBuf;

			g_branchTrampoline.Write6Branch(sub_1A3650.GetUIntPtr(), (uintptr_t)sub_1A3650_Hook);
		}

		}

		return true;

	}

};
