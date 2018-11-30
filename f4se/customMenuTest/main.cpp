#include "main.h"

#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"

#include "Shared.h"

#include "Tests.h"

std::string mName = "CWMenu";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEScaleformInterface			* g_scaleform = nullptr;
F4SEMessagingInterface			* g_messaging = nullptr;
F4SEPapyrusInterface			* g_papyrus = NULL;

#define CA_AffinityFormID 0xA1B80
#define CA_CurrentTresholdFormID 0xA1B81
#define FollowerDistanceFormID 0x345
#define FollowerStanceFormID 0x346
#define FollowerStanceAllowCombatOverrideFormID 0x347
#define FollowerStateFormID 0x344

ActorValueInfo* CA_Affinity;
ActorValueInfo* CA_CurrentTreshold;
ActorValueInfo* FollowerDistance;
ActorValueInfo* FollowerStance;
ActorValueInfo* FollowerStanceAllowCombatOverride;
ActorValueInfo* FollowerState;

void FillConsts()
{
	CA_Affinity = DYNAMIC_CAST(LookupFormByID(CA_AffinityFormID), TESForm, ActorValueInfo);
	CA_CurrentTreshold = DYNAMIC_CAST(LookupFormByID(CA_CurrentTresholdFormID), TESForm, ActorValueInfo);
	FollowerDistance = DYNAMIC_CAST(LookupFormByID(FollowerDistanceFormID), TESForm, ActorValueInfo);
	FollowerStance = DYNAMIC_CAST(LookupFormByID(FollowerStanceFormID), TESForm, ActorValueInfo);
	FollowerStanceAllowCombatOverride = DYNAMIC_CAST(LookupFormByID(FollowerStanceAllowCombatOverrideFormID), TESForm, ActorValueInfo);
	FollowerState = DYNAMIC_CAST(LookupFormByID(FollowerStateFormID), TESForm, ActorValueInfo);
}

#include "ScaleformLoader.h"

class CustomMenu_x : public GameMenuBase
{
public:

	enum
	{
		kMessage_UpdateModSettings = 0x10,
		kMessage_UpdateColorSettings
	};

	CustomMenu_x() : GameMenuBase()
	{
		//default menu depth is 6.
		flags = kFlag_EnableMenuControl | kFlag_ShowCursor;
		depth = 0x6;
		if (CALL_MEMBER_FN((*g_scaleformManager), LoadMovie)(this, this->movie, "CustomMenu_x", "root1.Menu_mc", 2))
		{

			_DMESSAGE("LoadMovie done");

			CreateBaseShaderTarget(this->shaderTarget, this->stage);

			this->shaderTarget->SetFilterColor(false);
			(*g_colorUpdateDispatcher)->eventDispatcher.AddEventSink(this->shaderTarget);

			this->subcomponents.Push(this->shaderTarget);
		}
		//IMenu* menu = (*g_ui)->GetMenu(BSFixedString("HUDMenu"));
		//menu->depth = 0x15;
	}

	virtual void	Invoke(Args * args) final
	{
		switch (args->optionID)
		{
		case 0:
		{
			_DMESSAGE("ExitCommandMode");
			CompanionListenerUnk03((*g_multiActivateManager)->listener1.companionListener, 1);
		}
		break;
		case 1:
		{
			_DMESSAGE("OpenInventory");
			CompanionListenerUnk03((*g_multiActivateManager)->listener1.companionListener, 2);
		}
		break;
		case 2:
		{
			_DMESSAGE("TalkTo");
			CompanionListenerUnk03((*g_multiActivateManager)->listener1.companionListener, 0);
			TESObjectREFR* ref = FindBestWeapons::GetCommandTarget();
			if (ref)
			{
				float fstate = 0.0;
				fstate = ref->actorValueOwner.GetValue(FollowerState);
				_MESSAGE("state %f", fstate);
			}

			BSExtraData* edl = ref->extraDataList->m_data;
			while (edl)
			{
				_MESSAGE("%s", GetObjectClassName(edl));
				edl = edl->next;
			}

			//_MESSAGE("state flags %i", (*g_player)->actorState.flags );
			//_MESSAGE("flags %i", (*g_player)->actorFlags);
			//ExtraFlags * ef = DYNAMIC_CAST((*g_player)->extraDataList->GetByType(kExtraData_Flags), BSExtraData, ExtraFlags);
			//if (ef)
			//{
			//	_MESSAGE("extraflags %i", ef->flags);
			//}
			//_MESSAGE("actor+0x43C %i", *((UInt64*)(uintptr_t)ref+ 0x43C));
			//DumpClass(ref, 0x440 / 8);
			//RelocPtr <void*> yy(0x591BB80);
			//DumpClass(*yy, 20);

			//DumpClass(*g_player, 1000);


		}
		break;
		default:
			break;
		}
	}

	virtual void	RegisterFunctions() final
	{
		_DMESSAGE("RegisterFunctions");
		this->RegisterNativeFunction("ExitCommandMode", 0);
		this->RegisterNativeFunction("OpenInventory", 1);
		this->RegisterNativeFunction("TalkTo", 2);
	}

	virtual UInt32	ProcessMessage(UIMessage * msg) final
	{
		GFxMovieRoot * root = movie->movieRoot;
		switch (msg->type)
		{
		case kMessage_UpdateModSettings:
		{
			GFxValue invWg, carryWg;
			TESObjectREFR* ref = FindBestWeapons::GetCommandTarget();
			if (ref)
			{
				//_DMESSAGE("%s", ref->baseForm->GetFullName());
				//_DMESSAGE("invWg %f", CALL_MEMBER_FN(ref, GetInventoryWeight)());
				//_DMESSAGE("carryWg %f", CALL_MEMBER_FN(ref, GetCarryWeight)());
				invWg.SetInt((int)CALL_MEMBER_FN(ref, GetInventoryWeight)());
				carryWg.SetInt((int)CALL_MEMBER_FN(ref, GetCarryWeight)());
				root->SetVariable("root.Menu_mc.invWg", &invWg);
				root->SetVariable("root.Menu_mc.carryWg", &carryWg);

				FindBestWeapons::FindBestWeapons(ref, true);
			}
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

	static IMenu * CreateCustomMenu_x()
	{
		return new CustomMenu_x();
	}

	static void UpdateModSettings()
	{
		static BSFixedString menuName("CustomMenu_x");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_UpdateModSettings);
	}

	static void OpenMenu()
	{
		static BSFixedString menuName("CustomMenu_x");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Open);
	}

	static void CloseMenu()
	{
		static BSFixedString menuName("CustomMenu_x");
		CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Close);
	}

	static void RegisterMenu()
	{
		static BSFixedString menuName("CustomMenu_x");
		if ((*g_ui) != nullptr && !(*g_ui)->IsMenuRegistered(menuName))
		{
			(*g_ui)->Register("CustomMenu_x", CreateCustomMenu_x);
		}
		_DMESSAGE("RegisterMenu %s", (*g_ui)->IsMenuRegistered(menuName) ? "registered" : "not registered");
	}
};


void MessageCallback(F4SEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case F4SEMessagingInterface::kMessage_GameLoaded:
		CustomMenu_x::RegisterMenu();
		break;
	case F4SEMessagingInterface::kMessage_GameDataReady:
		FindBestWeapons::FillConsts();
		FillConsts();
		break;
	default:
		break;
	}
}

bool ScaleformCallback(GFxMovieView * view, GFxValue * value)
{
	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
	}
	return true;
}

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
TESObjectREFR* testref = nullptr;
bool custommenutest(StaticFunctionTag*)
{
	if (!testref)
	testref = FindBestWeapons::GetCommandTarget();

	_DMESSAGE("custommenutest");
	TESObjectREFR* ref2 = nullptr;
	//UInt32 handle = ;
	LookupREFRByHandle((UInt32*)((uintptr_t)(*g_player) + 0xB1C), &ref2);
	if (ref2)
	{
		_MESSAGE("name %s", ref2->baseForm->GetFullName());
	}


	DumpClass(*g_multiActivateManager, 0xE8/8);
	DumpClass((*g_multiActivateManager)->listener1.companionListener, 0x30 / 8);
	DumpClass((*g_multiActivateManager)->unkArray20.entries, 0x30 / 8);

	//FindBestWeapons::FindBestWeapons(*g_player, false);
	//FindBestWeapons::EquipWeapon(FindBestWeapons::rangedWeapForUI.weapToEquip, *g_player);


	// perkentries tests
	/*RelocAddr <uintptr_t> s_visitor(0x2D3AEA8);
	RelocAddr<void(*)(Actor*, HasPerkVisitor&)> DumpPerks = 0xDA5FC0;
		HasPerkVisitor visitor;
		DumpPerks(*g_player, visitor);
		for (auto& pEntry : visitor.result)
		{
			//_DMESSAGE("perk %s \t\t rank: %i", pEntry.perk->fullName.name.c_str(),pEntry.rank);
			if (pEntry.perk->perkEntries.entries)
			{
			//	DumpClass(*pEntry.perk->perkEntries.entries, 10);
			}
			//DumpClass(pEntry.perk->perkEntries.entries,10);
		}
		BGSPerk* testperk = DYNAMIC_CAST(LookupFormByID(0x65e52), TESForm, BGSPerk);
		DumpClass(testperk, 0x98/8);
		DumpClass(testperk->perkEntries.entries, 20);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[0])), 6);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[0]))->unk20, 20);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[0]))->function, 4);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[1])), 6);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[1]))->unk20, 20);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[1]))->function, 4);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[2])), 6);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[2]))->unk20, 20);
		DumpClass(((BGSEntryPointPerkEntry*)(testperk->perkEntries.entries[2]))->function, 4);
		*/

	//CustomMenu_x::OpenMenu();
	return true;
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("custommenutest", "MyDebug:debugS", custommenutest, vm));
	return true;
}

_MultiActivateMenuProcessMessage MultiActivateMenuProcessMessage_Original;

UInt32 MultiActivateMenuProcessMessage_Hook(MultiActivateMenu * menu, UIMessage * message) {
	//_DMESSAGE("MultiActivateMenuProcessMessage_Hook command %i", message->type);
	if (message->type == 1)
	{
		CustomMenu_x::OpenMenu();
		CustomMenu_x::UpdateModSettings();
		//DumpClass(*g_multiActivateManager,50);
		//DumpClass((*g_multiActivateManager)->unk20, 50);
		//DumpClass((*g_multiActivateManager)->unk50, 50);
	}
	else if (message->type == 3)
	{
		CustomMenu_x::CloseMenu();

	}
	//return MultiActivateMenuProcessMessage_Original(menu, message);
	return 0;
}

#include "f4se_common/SafeWrite.h"

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
		InitCWAddresses();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		if (g_scaleform)
			g_scaleform->Register("NVCW", ScaleformCallback);

		if (g_messaging != nullptr)
			g_messaging->RegisterListener(g_pluginHandle, "F4SE", MessageCallback);
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
			struct MultiActivateMenuProcessMessage_Code : Xbyak::CodeGenerator {
				MultiActivateMenuProcessMessage_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					sub(rsp, 0x28);
					mov(r8d, ptr[rdx + 0x10]);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(MultiActivateMenuProcessMessage.GetUIntPtr() + 8);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			MultiActivateMenuProcessMessage_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			MultiActivateMenuProcessMessage_Original = (_MultiActivateMenuProcessMessage)codeBuf;

			g_branchTrampoline.Write6Branch(MultiActivateMenuProcessMessage.GetUIntPtr(), (uintptr_t)MultiActivateMenuProcessMessage_Hook);
		}

		unsigned char data[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		//SafeWriteBuf(RelocAddr<uintptr_t>(0x9FFB36).GetUIntPtr(), &data, sizeof(data)); // hold/follow function
		//SafeWriteBuf(RelocAddr<uintptr_t>(0xEACE86).GetUIntPtr(), &data, sizeof(data)); // hold/follow 1st function
		//SafeWriteBuf(RelocAddr<uintptr_t>(0xEACE98).GetUIntPtr(), &data, sizeof(data)); // hold/follow 2nd function
		//SafeWriteBuf(RelocAddr<uintptr_t>(0xEACEF9).GetUIntPtr(), &data, sizeof(data)); // hold/follow 3rd function
		//unsigned char data2[] = { 0xC3 };
		//SafeWriteBuf(RelocAddr<uintptr_t>(0xEAD312).GetUIntPtr(), &data2, sizeof(data2)); // hold/follow 3rd function

		return true;
	}

};
