#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"

#include "main.h"
#include "Shared.h"

#include "f4se/GameMenus.h"
#include "f4seeeSerialization.h"
#include "f4seeeEvents.h"
#include "f4seeePapyrus.h"

std::string mName = "f4seee";
UInt32 mVer = 1;

F4SEScaleformInterface		*g_scaleform = NULL;
F4SEPapyrusInterface		*g_papyrus = NULL;
F4SEMessagingInterface		*g_messaging = NULL;
F4SESerializationInterface	*g_serialization = NULL;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;



bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	return true;
}

void RegisterDataReadyEvents()
{
	//REGISTER_EVENT(TESCellAttachDetachEvent, g_f4seeeTESCellAttachDetachEventSink);								// 029
	//REGISTER_EVENT(TESCellFullyLoadedEvent, g_f4seeeTESCellFullyLoadedEventSink);									// 030
	//REGISTER_EVENT(TESCellReadyToApplyDecalsEvent, g_f4seeeTESCellReadyToApplyDecalsEventSink);					// 031
	REGISTER_EVENT(TESCombatEvent_x, g_f4seeeTESCombatEvent_xSink);													// 032
	REGISTER_EVENT(ActorItemEquipped::Event, g_f4seeeActorItemEquipped__EventSink);									// unk1
	
}


void RegisterLoadGameEvents()
{
	//REGISTER_EVENT(CellAttachDetachEvent, g_f4seeeCellAttachDetachEventSink);										// 002



	//REGISTER_EVENT(TESActivateEvent, g_f4seeeTESActivateEventSink);												// 024
	//REGISTER_EVENT(TESExitFurnitureEvent, g_f4seeeTESExitFurnitureEventSink);										// 025
	//REGISTER_EVENT(TESActiveEffectApplyRemoveEvent, g_f4seeeTESActiveEffectApplyRemoveEventSink);					// 026
	//REGISTER_EVENT(TESActorLocationChangeEvent, g_f4seeeTESActorLocationChangeEventSink);							// 027
	//REGISTER_EVENT(TESBookReadEvent, g_f4seeeTESBookReadEventSink);												// 028


	
	
	


	//REGISTER_EVENT(LevelIncrease::Event, g_f4seeeLevelIncrease__EventSink);										// x01
	REGISTER_EVENT(BGSOnPlayerModArmorWeaponEvent, g_f4seeeBGSOnPlayerModArmorWeaponEventSink);						// x04


	//REGISTER_EVENT(TerminalMenuItemRunEvent, g_f4seeeTerminalMenuItemRunEventSink);						// x05  prob 023
	//REGISTER_EVENT(TESPackageEvent, g_f4seeeTESPackageEventSink);						// x06
	//REGISTER_EVENT(TESPerkEntryRunEvent, g_f4seeeTESPerkEntryRunEventSink);						// x07
	//REGISTER_EVENT(TESQuestStageEvent, g_f4seeeTESQuestStageEventSink);						// x08
	REGISTER_EVENT(TESSceneActionEvent, g_f4seeeTESSceneActionEventSink);						// x09
	
	
}



class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override
	{
		RegisterLoadGameEvents();
		return kEvent_Continue;
	}
};

void GameDataReady()
{
	RegisterDataReadyEvents();
	static auto pLoadGameHandler = new TESLoadGameHandler();
	GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
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

bool RegisterPapyrus(VirtualMachine *vm) {
	f4seeePapyrus::RegisterFuncs(vm);
	_MESSAGE("Registered Papyrus native functions.");

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
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_64) {
			//_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.64 only.", f4se->runtimeVersion);
			//MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.64). \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			//return false;
		}

		// Get the scaleform interface
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform) {
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}

		// Get the papyrus interface
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus) {
			_MESSAGE("couldn't get papyrus interface");
			return false;
		}

		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			_MESSAGE("couldn't get messaging interface");
			return false;
		}

		// Get the serialization interface
		g_serialization = (F4SESerializationInterface *)f4se->QueryInterface(kInterface_Serialization);
		if (!g_serialization) {
			_MESSAGE("couldn't get serialization interface");
			return false;
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("f4seee load");
		g_papyrus->Register(RegisterPapyrus);
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);

		g_serialization->SetUniqueID(g_pluginHandle, 'SEEE');
		g_serialization->SetRevertCallback(g_pluginHandle, f4eeeSerialization::RevertCallback);
		g_serialization->SetLoadCallback(g_pluginHandle, f4eeeSerialization::LoadCallback);
		g_serialization->SetSaveCallback(g_pluginHandle, f4eeeSerialization::SaveCallback);
		InitEvents();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		return true;
	}

};
