#include "f4seeePapyrus.h"

#include "f4se/PapyrusScriptObject.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/PapyrusEvents.h"

#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"



namespace f4seeePapyrus
{
	ADD_FormsPairParameters_EVENT_HANDLER(TESActivateEvent, Actor, TESObjectREFR);
	ADD_FormsPairParameters_EVENT_HANDLER(TESExitFurnitureEvent, Actor, TESObjectREFR);
	/*void RegisterForTESActivateEvent(VMObject * thisObject, Actor* actor, TESObjectREFR* ref)
	{
		if (!thisObject)
			return;
		EventRegistration<FormsPairParameters> p;
		p.handle = thisObject->GetHandle();
		p.scriptName = thisObject->GetObjectType();
		FormsPairParameters * params = &p.params;

		g_f4seeeTESActivateEventRegs.Lock();

		bool regExists = false;
		auto it = g_f4seeeTESActivateEventRegs.m_data.find(p);
		if (it != g_f4seeeTESActivateEventRegs.m_data.end()) {
			params = const_cast<FormsPairParameters*>(&it->params);
			regExists = true;
		}
		
		params->AddFilter(actor, ref);

		if (!regExists)
		{
			g_f4seeeTESActivateEventRegs.Register(thisObject->GetHandle(), thisObject->GetObjectType(), params);
		}
		
		g_f4seeeTESActivateEventRegs.Release();
	}

	void UnregisterForTESActivateEvent(VMObject * thisObject, Actor* actor, TESObjectREFR* ref)
	{
		
		if (!thisObject)
			return;

		EventRegistration<FormsPairParameters> p;
		p.handle = thisObject->GetHandle();
		p.scriptName = thisObject->GetObjectType();
		FormsPairParameters * params = &p.params;

		g_f4seeeTESActivateEventRegs.Lock();
		
		// Lookup the existing params from the registrations if it exists
		// Set contents are normally const, we are casting because the order of the set is unchanged by this
		auto it = g_f4seeeTESActivateEventRegs.m_data.find(p);
		if (it != g_f4seeeTESActivateEventRegs.m_data.end()) {
			params = const_cast<FormsPairParameters*>(&it->params);
		}

		if (actor || ref)
		{
			params->RemoveFilter(actor, ref);
		}
		else // No parameter, remove all registrations
			g_f4seeeTESActivateEventRegs.Unregister(thisObject->GetHandle(), thisObject->GetObjectType());
			
		g_f4seeeTESActivateEventRegs.Release();
		
	}*/
	void RegisterForLevelIncrease__Event(VMObject * thisObject)
	{
		if (!thisObject)
			return;

		g_f4seeeLevelIncrease__EventRegs.Register(thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void UnregisterForLevelIncrease__Event(VMObject * thisObject)
	{
		if (!thisObject)
			return;

		g_f4seeeLevelIncrease__EventRegs.Unregister(thisObject->GetHandle(), thisObject->GetObjectType());
	}
}

void f4seeePapyrus::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction2 <VMObject, void, Actor*, TESObjectREFR*>("RegisterForTESActivateEvent", "ScriptObject", f4seeePapyrus::RegisterForTESActivateEvent, vm));

	vm->RegisterFunction(
		new NativeFunction2 <VMObject, void, Actor*, TESObjectREFR*>("UnregisterForTESActivateEvent", "ScriptObject", f4seeePapyrus::UnregisterForTESActivateEvent, vm));

	vm->RegisterFunction(
		new NativeFunction2 <VMObject, void, Actor*, TESObjectREFR*>("RegisterForTESExitFurnitureEvent", "ScriptObject", f4seeePapyrus::RegisterForTESExitFurnitureEvent, vm));

	vm->RegisterFunction(
		new NativeFunction2 <VMObject, void, Actor*, TESObjectREFR*>("UnregisterForTESExitFurnitureEvent", "ScriptObject", f4seeePapyrus::UnregisterForTESExitFurnitureEvent, vm));

	vm->RegisterFunction(
		new NativeFunction0 <VMObject, void>("RegisterForLevelIncrease__Event", "ScriptObject", f4seeePapyrus::RegisterForLevelIncrease__Event, vm));

	vm->RegisterFunction(
		new NativeFunction0 <VMObject, void>("UnregisterForLevelIncrease__Event", "ScriptObject", f4seeePapyrus::UnregisterForLevelIncrease__Event, vm));
}
