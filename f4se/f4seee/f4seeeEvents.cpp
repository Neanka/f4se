#include "f4seeeEvents.h"
#include "f4se/PapyrusUtilities.h"

#include "f4se/GameReferences.h"

#include "GameRTTI.h"


// 002

RegistrationSetHolder<NullParameters>							g_f4seeeCellAttachDetachEventRegs;

f4seeeCellAttachDetachEventSink g_f4seeeCellAttachDetachEventSink;

EventResult	f4seeeCellAttachDetachEventSink::ReceiveEvent(CellAttachDetachEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee CellAttachDetachEvent recieved: cell formId: %08X cell edid: %s %s %s", evn->cell->formID, evn->cell->GetEditorID(), (evn->status & evn->finish) ? "finish" : "start", (evn->status & evn->detaching) ? "detaching" : "attaching");
	/*g_f4seeeCellAttachDetachEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnCellAttachDetachEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<CellAttachDetachEvent>*> CellAttachDetachEvent_Dispatcher_address;

void CellAttachDetachEvent_Dispatcher_Init()
{
	CellAttachDetachEvent_Dispatcher_address = RVA <BSTEventDispatcher<CellAttachDetachEvent>*>(
		"CellAttachDetachEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0010B730 },
			{ RUNTIME_VERSION_1_10_40, 0x10B730 },
		}, "48 8B CF E8 ? ? ? ? 89 1C 2E E8 ? ? ? ?", { { 0x3, 1, 5 },{ 0x9,1,5 } });
}

// 024 BasicEventHandler@GameScript@@

RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESActivateEventRegs;

f4seeeTESActivateEventSink g_f4seeeTESActivateEventSink;

EventResult	f4seeeTESActivateEventSink::ReceiveEvent(TESActivateEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESActivateEvent recieved: %s activated by %s", evn->activator->baseForm->GetFullName(), evn->actor->baseForm->GetFullName());
	g_f4seeeTESActivateEventRegs.ForEach(
		[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
		if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->activator) || reg.params.HasFilter(nullptr, evn->activator) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
			SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESActivateEvent", evn->actor, evn->activator);

	}
	);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESActivateEvent>*> TESActivateEvent_Dispatcher_address;

void TESActivateEvent_Dispatcher_Init()
{
	TESActivateEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESActivateEvent>*>(
		"TESActivateEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441B10 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x3f));
}

// 025 BasicEventHandler@GameScript@@

RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESExitFurnitureEventRegs;

f4seeeTESExitFurnitureEventSink g_f4seeeTESExitFurnitureEventSink;

EventResult	f4seeeTESExitFurnitureEventSink::ReceiveEvent(TESExitFurnitureEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESExitFurnitureEvent recieved");
	g_f4seeeTESExitFurnitureEventRegs.ForEach(
		[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
		if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
			SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESExitFurnitureEvent", evn->actor, evn->furniture);

	}
	);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESExitFurnitureEvent>*> TESExitFurnitureEvent_Dispatcher_address;

void TESExitFurnitureEvent_Dispatcher_Init()
{
	TESExitFurnitureEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESExitFurnitureEvent>*>(
		"TESExitFurnitureEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x004428D0 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x4B5));
}


// 026 BasicEventHandler@GameScript@@

RegistrationSetHolder<NullParameters>							g_f4seeeTESActiveEffectApplyRemoveEventRegs;

f4seeeTESActiveEffectApplyRemoveEventSink g_f4seeeTESActiveEffectApplyRemoveEventSink;

EventResult	f4seeeTESActiveEffectApplyRemoveEventSink::ReceiveEvent(TESActiveEffectApplyRemoveEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESActiveEffectApplyRemoveEvent recieved");
	/*g_f4seeeTESExitFurnitureEventRegs.ForEach(
		[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
		if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
			SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESExitFurnitureEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESActiveEffectApplyRemoveEvent>*> TESActiveEffectApplyRemoveEvent_Dispatcher_address;

void TESActiveEffectApplyRemoveEvent_Dispatcher_Init()
{
	TESActiveEffectApplyRemoveEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESActiveEffectApplyRemoveEvent>*>(
		"TESActiveEffectApplyRemoveEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441BB0 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x50));
}

// 027 BasicEventHandler@GameScript@@ 080h

RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESActorLocationChangeEventRegs;

f4seeeTESActorLocationChangeEventSink g_f4seeeTESActorLocationChangeEventSink;

EventResult	f4seeeTESActorLocationChangeEventSink::ReceiveEvent(TESActorLocationChangeEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESActorLocationChangeEvent recieved: %s changed location from %s to %s", evn->actor->baseForm->GetFullName(),evn->oldLoc->GetFullName(),evn->newLoc->GetFullName());
	/*g_f4seeeTESActorLocationChangeEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESActorLocationChangeEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESActorLocationChangeEvent>*> TESActorLocationChangeEvent_Dispatcher_address;

void TESActorLocationChangeEvent_Dispatcher_Init()
{
	TESActorLocationChangeEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESActorLocationChangeEvent>*>(
		"TESActorLocationChangeEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441C50 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x64));
}

// 028 BasicEventHandler@GameScript@@ 088h

RegistrationSetHolder<NullParameters>							g_f4seeeTESBookReadEventRegs;

f4seeeTESBookReadEventSink g_f4seeeTESBookReadEventSink;

EventResult	f4seeeTESBookReadEventSink::ReceiveEvent(TESBookReadEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESBookReadEvent recieved: ");
	_DMESSAGE("						book: %s ", evn->book->GetFullName());
	if (evn->ref)
	{
		_DMESSAGE("						book ref is persistent: %s ", evn->ref->baseForm->GetFullName());
	}
	/*g_f4seeeTESBookReadEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESBookReadEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESBookReadEvent>*> TESBookReadEvent_Dispatcher_address;

void TESBookReadEvent_Dispatcher_Init()
{
	TESBookReadEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESBookReadEvent>*>(
		"TESBookReadEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441CF0 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x78));
}

// 029 BasicEventHandler@GameScript@@ 090h

RegistrationSetHolder<NullParameters>							g_f4seeeTESCellAttachDetachEventRegs;

f4seeeTESCellAttachDetachEventSink g_f4seeeTESCellAttachDetachEventSink;

EventResult	f4seeeTESCellAttachDetachEventSink::ReceiveEvent(TESCellAttachDetachEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESCellAttachDetachEvent recieved:  %s (formID: %08X) parent cell %s", evn->ref->baseForm->GetFullName(), evn->ref->formID, evn->attached?"attached":"detached");
	
	
	//DumpClass(evn, 30);
	/*g_f4seeeTESCellAttachDetachEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESCellAttachDetachEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESCellAttachDetachEvent>*> TESCellAttachDetachEvent_Dispatcher_address;

void TESCellAttachDetachEvent_Dispatcher_Init()
{
	TESCellAttachDetachEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESCellAttachDetachEvent>*>(
		"TESCellAttachDetachEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441D90 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS1(0x8C));
}

// 030 BasicEventHandler@GameScript@@ 098h

RegistrationSetHolder<NullParameters>							g_f4seeeTESCellFullyLoadedEventRegs;

f4seeeTESCellFullyLoadedEventSink g_f4seeeTESCellFullyLoadedEventSink;

EventResult	f4seeeTESCellFullyLoadedEventSink::ReceiveEvent(TESCellFullyLoadedEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESCellFullyLoadedEvent recieved: cell %s (formID: %08X) fully loaded.",evn->cell->GetFullName(), evn->cell->formID);

	/*g_f4seeeTESCellFullyLoadedEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESCellFullyLoadedEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESCellFullyLoadedEvent>*> TESCellFullyLoadedEvent_Dispatcher_address;

void TESCellFullyLoadedEvent_Dispatcher_Init()
{
	TESCellFullyLoadedEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESCellFullyLoadedEvent>*>(
		"TESCellFullyLoadedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441E30 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS1(0xA0));
}

// 031 have no papyrus analog

RegistrationSetHolder<NullParameters>							g_f4seeeTESCellReadyToApplyDecalsEventRegs;

f4seeeTESCellReadyToApplyDecalsEventSink g_f4seeeTESCellReadyToApplyDecalsEventSink;

EventResult	f4seeeTESCellReadyToApplyDecalsEventSink::ReceiveEvent(TESCellReadyToApplyDecalsEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESCellReadyToApplyDecalsEvent recieved: cell %s (formID: %08X) ready for apply decals.", evn->cell->GetFullName(), evn->cell->formID);

	/*g_f4seeeTESCellReadyToApplyDecalsEventRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESCellReadyToApplyDecalsEvent", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESCellReadyToApplyDecalsEvent>*> TESCellReadyToApplyDecalsEvent_Dispatcher_address;

void TESCellReadyToApplyDecalsEvent_Dispatcher_Init()
{
	TESCellReadyToApplyDecalsEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESCellReadyToApplyDecalsEvent>*>(
		"TESCellReadyToApplyDecalsEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441ED0 },
		}, "E8 ? ? ? ? 48 8B 83 D0 00 00 00 C6 80 15 02 00 00 01", { { 0,1,5 },{ 9,1,5 } });
}

// 032 BasicEventHandler@GameScript@@ 0A0h

RegistrationSetHolder<NullParameters>							g_f4seeeTESCombatEvent_xRegs;

f4seeeTESCombatEvent_xSink g_f4seeeTESCombatEvent_xSink;

EventResult	f4seeeTESCombatEvent_xSink::ReceiveEvent(TESCombatEvent_x * evn, void * dispatcher)
{
	if (evn->target != nullptr && evn->source != nullptr)
	{
		_DMESSAGE("f4seee TESCombatEvent_x recieved: %s combat state against %s changed to %i", evn->source->baseForm->GetFullName(), evn->target->baseForm->GetFullName(), evn->state);
	}
	else
	{
		_DMESSAGE("f4seee TESCombatEvent_x recieved: %s combat state changed to %i", evn->source->baseForm->GetFullName(), evn->state);
	}
	/*g_f4seeeTESCombatEvent_xRegs.ForEach(
	[&evn](const EventRegistration<FormsPairParameters> & reg)
	{
	if (reg.params.NoFilter() || reg.params.HasFilter(evn->actor, evn->furniture) || reg.params.HasFilter(nullptr, evn->furniture) || reg.params.HasFilter(evn->actor, nullptr) || reg.params.HasFilter(nullptr, nullptr))
	SendPapyrusEvent2<Actor*, TESObjectREFR*>(reg.handle, reg.scriptName, "OnTESCombatEvent_x", evn->actor, evn->furniture);

	}
	);*/

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESCombatEvent_x>*> TESCombatEvent_x_Dispatcher_address;

void TESCombatEvent_x_Dispatcher_Init()
{
	TESCombatEvent_x_Dispatcher_address = RVA <BSTEventDispatcher<TESCombatEvent_x>*>(
		"TESCombatEvent_x_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441F70 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0xB4));
}







// xx1 

RegistrationSetHolder<NullParameters>							g_f4seeeLevelIncrease__EventRegs;

f4seeeLevelIncrease__EventSink g_f4seeeLevelIncrease__EventSink;

EventResult	f4seeeLevelIncrease__EventSink::ReceiveEvent(LevelIncrease::Event * evn, void * dispatcher)
{
	_DMESSAGE("f4seee LevelIncrease__Event recieved");
	g_f4seeeLevelIncrease__EventRegs.ForEach(
		[&evn](const EventRegistration<NullParameters> & reg)
	{
			SendPapyrusEvent3<UInt32, float, UInt32>(reg.handle, reg.scriptName, "OnLevelIncrease__Event", evn->gainedLevel, evn->gainedExp, evn->fromLevel);
	}
	);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<LevelIncrease::Event>*> LevelIncrease__Event_Dispatcher_address;

void LevelIncrease__Event_Dispatcher_Init()
{
	LevelIncrease__Event_Dispatcher_address = RVA <BSTEventDispatcher<LevelIncrease::Event>*>(
		"LevelIncrease__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_130, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_120, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_114, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_111, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_106, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_98, 0x00EC3020 },
			{ RUNTIME_VERSION_1_10_89, 0x00EC2FE0 },
			{ RUNTIME_VERSION_1_10_82, 0x00EC2F80 },
			{ RUNTIME_VERSION_1_10_75, 0x00EC2F80 },
			{ RUNTIME_VERSION_1_10_64, 0x00EC2FC0 },
			{ RUNTIME_VERSION_1_10_50, 0x00EC2BA0 },
		}, "E8 ? ? ? ? 48 8D 54 24 38 48 8B C8 E8 ? ? ? ? 48 8B CE", 0,1,5);
}


// xx4 BasicEventHandler@GameScript@@ 30h 

RegistrationSetHolder<NullParameters>							g_f4seeeBGSOnPlayerModArmorWeaponEventRegs;

f4seeeBGSOnPlayerModArmorWeaponEventSink g_f4seeeBGSOnPlayerModArmorWeaponEventSink;

EventResult	f4seeeBGSOnPlayerModArmorWeaponEventSink::ReceiveEvent(BGSOnPlayerModArmorWeaponEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee BGSOnPlayerModArmorWeaponEvent recieved: mod %s attached to %s", evn->mod->GetFullName(), evn->object->GetFullName());

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<BGSOnPlayerModArmorWeaponEvent>*> BGSOnPlayerModArmorWeaponEvent_Dispatcher_address;

void BGSOnPlayerModArmorWeaponEvent_Dispatcher_Init()
{
	BGSOnPlayerModArmorWeaponEvent_Dispatcher_address = RVA <BSTEventDispatcher<BGSOnPlayerModArmorWeaponEvent>*>(
		"BGSOnPlayerModArmorWeaponEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441610 },
		}, "E8 ? ? ? ? 49 8B 0F 49 8D 56 10", BASIC_EVENT_HANDLER_INDIRECTIONS(0x2C3));
}


// xx5 FragmentEventHandler@GameScript@@ 0h 

RegistrationSetHolder<NullParameters>							g_f4seeeTerminalMenuItemRunEventRegs;

f4seeeTerminalMenuItemRunEventSink g_f4seeeTerminalMenuItemRunEventSink;

EventResult	f4seeeTerminalMenuItemRunEventSink::ReceiveEvent(TerminalMenuItemRunEvent * evn, void * dispatcher)
{
	auto page = DYNAMIC_CAST(LookupFormByID(evn->terminalPageFormID), TESForm, BGSTerminal);
	if (evn->terminalRef)
	{
		_DMESSAGE("f4seee TerminalMenuItemRunEvent recieved: item #%i selected at %s page on %s terminal", evn->itemID, page->GetFullName(), evn->terminalRef->baseForm->GetFullName());
	}
	else
	{
		_DMESSAGE("f4seee TerminalMenuItemRunEvent recieved: item #%i selected at %s page on pipboy", evn->itemID, page->GetFullName());
	}

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TerminalMenuItemRunEvent>*> TerminalMenuItemRunEvent_Dispatcher_address;

void TerminalMenuItemRunEvent_Dispatcher_Init()
{
	TerminalMenuItemRunEvent_Dispatcher_address = RVA <BSTEventDispatcher<TerminalMenuItemRunEvent>*>(
		"TerminalMenuItemRunEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_64, 0x004443B0 },
		{ RUNTIME_VERSION_1_10_50, 0x004443B0 },
		}, GAME_VM_EVENTS_REG_SIG, FRAGMENT_EVENT_HANDLER_INDIRECTIONS(0x7A));
}

// xx6 FragmentEventHandler@GameScript@@ 8h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESPackageEventRegs;

f4seeeTESPackageEventSink g_f4seeeTESPackageEventSink;

EventResult	f4seeeTESPackageEventSink::ReceiveEvent(TESPackageEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESPackageEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESPackageEvent>*> TESPackageEvent_Dispatcher_address;

void TESPackageEvent_Dispatcher_Init()
{
	TESPackageEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESPackageEvent>*>(
		"TESPackageEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_64, 0x004432D0 },
		}, GAME_VM_EVENTS_REG_SIG, FRAGMENT_EVENT_HANDLER_INDIRECTIONS(0x1D));
}

// xx7 FragmentEventHandler@GameScript@@ 10h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESPerkEntryRunEventRegs;

f4seeeTESPerkEntryRunEventSink g_f4seeeTESPerkEntryRunEventSink;

EventResult	f4seeeTESPerkEntryRunEventSink::ReceiveEvent(TESPerkEntryRunEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESPerkEntryRunEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESPerkEntryRunEvent>*> TESPerkEntryRunEvent_Dispatcher_address;

void TESPerkEntryRunEvent_Dispatcher_Init()
{
	TESPerkEntryRunEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESPerkEntryRunEvent>*>(
		"TESPerkEntryRunEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_64, 0x00443370 },
		}, GAME_VM_EVENTS_REG_SIG, FRAGMENT_EVENT_HANDLER_INDIRECTIONS(0x2E));
}

// xx8 FragmentEventHandler@GameScript@@ 18h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESQuestStageEventRegs;

f4seeeTESQuestStageEventSink g_f4seeeTESQuestStageEventSink;

EventResult	f4seeeTESQuestStageEventSink::ReceiveEvent(TESQuestStageEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESQuestStageEvent recieved: quest - %s stage - %u", LookupFormByID(evn->questFormID)->GetFullName(), evn->stage);
	//DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESQuestStageEvent>*> TESQuestStageEvent_Dispatcher_address;

void TESQuestStageEvent_Dispatcher_Init()
{
	TESQuestStageEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESQuestStageEvent>*>(
		"TESQuestStageEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_64, 0x004435F0 },
		}, GAME_VM_EVENTS_REG_SIG, FRAGMENT_EVENT_HANDLER_INDIRECTIONS(0x3F));
}

// xx9 FragmentEventHandler@GameScript@@ 20h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESSceneActionEventRegs;

f4seeeTESSceneActionEventSink g_f4seeeTESSceneActionEventSink;

EventResult	f4seeeTESSceneActionEventSink::ReceiveEvent(TESSceneActionEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESSceneActionEvent recieved: scene formid - %08X  actionIndex - %u   quest formid - %08X  referenceAliasID - %u", evn->sceneFormID, evn->actionIndex, evn->questFormID, evn->referenceAliasID);
	//DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESSceneActionEvent>*> TESSceneActionEvent_Dispatcher_address;

void TESSceneActionEvent_Dispatcher_Init()
{
	TESSceneActionEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESSceneActionEvent>*>(
		"TESSceneActionEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_64, 0x00443910 },
		}, GAME_VM_EVENTS_REG_SIG, FRAGMENT_EVENT_HANDLER_INDIRECTIONS(0x61));
}

// unk1

RegistrationSetHolder<NullParameters>							g_f4seeeActorItemEquipped__EventRegs;

f4seeeActorItemEquipped__EventSink g_f4seeeActorItemEquipped__EventSink;

EventResult	f4seeeActorItemEquipped__EventSink::ReceiveEvent(ActorItemEquipped::Event * evn, void * dispatcher)
{
	_DMESSAGE("f4seee ActorItemEquipped__Event recieved: ");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<ActorItemEquipped::Event>*> ActorItemEquipped__Event_Dispatcher_address;

void ActorItemEquipped__Event_Dispatcher_Init()
{
	ActorItemEquipped__Event_Dispatcher_address = RVA <BSTEventDispatcher<ActorItemEquipped::Event>*>(
		"ActorItemEquipped__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_89, 0x00DC5DD0 },
		}, "E8 ? ? ? ? 48 85 DB 74 ? 48 8D 8B C0 00 00 00", { { 0, 1, 5 },{ 0x9,1,5 } });
}

// inv1 InventoryEventHandler@GameScript@@ 0h 

RegistrationSetHolder<NullParameters>							g_f4seeeHolotapeChatterEventRegs;

f4seeeHolotapeChatterEventSink g_f4seeeHolotapeChatterEventSink;

EventResult	f4seeeHolotapeChatterEventSink::ReceiveEvent(HolotapeChatterEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee HolotapeChatterEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<HolotapeChatterEvent>*> HolotapeChatterEvent_Dispatcher_address;

void HolotapeChatterEvent_Dispatcher_Init()
{
	HolotapeChatterEvent_Dispatcher_address = RVA <BSTEventDispatcher<HolotapeChatterEvent>*>(
		"HolotapeChatterEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_89, 0x00441A30 },
		}, InventoryEventHandler_EVENTS_REG_SIG, InventoryEventHandler_INDIRECTIONS(0x36));
}

// inv2 InventoryEventHandler@GameScript@@ 8h 

RegistrationSetHolder<NullParameters>							g_f4seeeHolotapePlayEventRegs;

f4seeeHolotapePlayEventSink g_f4seeeHolotapePlayEventSink;

EventResult	f4seeeHolotapePlayEventSink::ReceiveEvent(HolotapePlayEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee HolotapePlayEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<HolotapePlayEvent>*> HolotapePlayEvent_Dispatcher_address;

void HolotapePlayEvent_Dispatcher_Init()
{
	HolotapePlayEvent_Dispatcher_address = RVA <BSTEventDispatcher<HolotapePlayEvent>*>(
		"HolotapePlayEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_89, 0x00441AD0 },
		}, InventoryEventHandler_EVENTS_REG_SIG, InventoryEventHandler_INDIRECTIONS(0x51));
}

// inv3 InventoryEventHandler@GameScript@@ 10h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESContainerChangedEventRegs;

f4seeeTESContainerChangedEventSink g_f4seeeTESContainerChangedEventSink;

EventResult	f4seeeTESContainerChangedEventSink::ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESContainerChangedEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESContainerChangedEvent>*> TESContainerChangedEvent_Dispatcher_address;

void TESContainerChangedEvent_Dispatcher_Init()
{
	TESContainerChangedEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESContainerChangedEvent>*>(
		"TESContainerChangedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_130, 0x00442390 },
			{ RUNTIME_VERSION_1_10_120, 0x00442390 },
			{ RUNTIME_VERSION_1_10_114, 0x00442390 },
			{ RUNTIME_VERSION_1_10_111, 0x00442390 },
			{ RUNTIME_VERSION_1_10_106, 0x00442390 },
			{ RUNTIME_VERSION_1_10_98, 0x00442390 },
			{ RUNTIME_VERSION_1_10_89, 0x00442390 },
		}, InventoryEventHandler_EVENTS_REG_SIG, InventoryEventHandler_INDIRECTIONS(0x1D));
}

// inv4 InventoryEventHandler@GameScript@@ 18h 

RegistrationSetHolder<NullParameters>							g_f4seeeTESEquipEventRegs;

f4seeeTESEquipEventSink g_f4seeeTESEquipEventSink;

EventResult	f4seeeTESEquipEventSink::ReceiveEvent(TESEquipEvent * evn, void * dispatcher)
{
	_DMESSAGE("f4seee TESEquipEvent recieved:");
	DumpClass(evn, 20);

	return kEvent_Continue;
}

RVA <BSTEventDispatcher<TESEquipEvent>*> TESEquipEvent_Dispatcher_address;

void TESEquipEvent_Dispatcher_Init()
{
	TESEquipEvent_Dispatcher_address = RVA <BSTEventDispatcher<TESEquipEvent>*>(
		"TESEquipEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_130, 0x00442750 },
			{ RUNTIME_VERSION_1_10_120, 0x00442750 },
			{ RUNTIME_VERSION_1_10_114, 0x00442750 },
			{ RUNTIME_VERSION_1_10_111, 0x00442750 },
			{ RUNTIME_VERSION_1_10_106, 0x00442750 },
			{ RUNTIME_VERSION_1_10_98, 0x00442750 },
			{ RUNTIME_VERSION_1_10_89, 0x00442750 },
		}, InventoryEventHandler_EVENTS_REG_SIG, InventoryEventHandler_INDIRECTIONS(0x2E));
}



void InitEvents()
{
	CellAttachDetachEvent_Dispatcher_Init();				// 002


	TESActivateEvent_Dispatcher_Init();						// 024
	TESExitFurnitureEvent_Dispatcher_Init();				// 025
	TESActiveEffectApplyRemoveEvent_Dispatcher_Init();		// 026
	TESActorLocationChangeEvent_Dispatcher_Init();			// 027
	TESBookReadEvent_Dispatcher_Init();						// 028
	TESCellAttachDetachEvent_Dispatcher_Init();				// 029
	TESCellFullyLoadedEvent_Dispatcher_Init();				// 030
	TESCellReadyToApplyDecalsEvent_Dispatcher_Init();		// 031 
	TESCombatEvent_x_Dispatcher_Init();					// 032




	LevelIncrease__Event_Dispatcher_Init();					// x01

	BGSOnPlayerModArmorWeaponEvent_Dispatcher_Init();		// x4
	TerminalMenuItemRunEvent_Dispatcher_Init();				// x5 prob 023
	TESPackageEvent_Dispatcher_Init();						// x6
	TESPerkEntryRunEvent_Dispatcher_Init();					// x7
	TESQuestStageEvent_Dispatcher_Init();					// x8
	TESSceneActionEvent_Dispatcher_Init();					// x9

	ActorItemEquipped__Event_Dispatcher_Init();				//unk1

	HolotapeChatterEvent_Dispatcher_Init();					// inv1
	HolotapePlayEvent_Dispatcher_Init();					// inv2
	TESContainerChangedEvent_Dispatcher_Init();				// inv3
	TESEquipEvent_Dispatcher_Init();						// inv4


}