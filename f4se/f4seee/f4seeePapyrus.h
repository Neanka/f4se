#pragma once
#include "f4seeeEvents.h"

#define ADD_FormsPairParameters_EVENT_HANDLER(_event, _paramtype1, _paramtype2) \
	void RegisterFor##_event(VMObject * thisObject, _paramtype1* param1,  _paramtype2* param2) \
	{ \
	if (!thisObject) \
		return; \
	EventRegistration<FormsPairParameters> p; \
	p.handle = thisObject->GetHandle(); \
	p.scriptName = thisObject->GetObjectType(); \
	FormsPairParameters * params = &p.params; \
 \
	g_f4seee##_event##Regs.Lock(); \
 \
	bool regExists = false; \
	auto it = g_f4seee##_event##Regs.m_data.find(p); \
	if (it != g_f4seee##_event##Regs.m_data.end()) { \
		params = const_cast<FormsPairParameters*>(&it->params); \
		regExists = true; \
	} \
 \
	params->AddFilter(param1, param2); \
 \
	if (!regExists) \
	{ \
		g_f4seee##_event##Regs.Register(thisObject->GetHandle(), thisObject->GetObjectType(), params); \
	} \
 \
	g_f4seee##_event##Regs.Release(); \
	} \
 \
void UnregisterFor##_event##(VMObject * thisObject, _paramtype1* param1,  _paramtype2* param2) \
{ \
 \
	if (!thisObject) \
		return; \
 \
	EventRegistration<FormsPairParameters> p; \
	p.handle = thisObject->GetHandle(); \
	p.scriptName = thisObject->GetObjectType(); \
	FormsPairParameters * params = &p.params; \
 \
	g_f4seee##_event##Regs.Lock(); \
 \
	auto it = g_f4seee##_event##Regs.m_data.find(p); \
	if (it != g_f4seee##_event##Regs.m_data.end()) { \
		params = const_cast<FormsPairParameters*>(&it->params); \
	} \
 \
	if (param1 || param2) \
	{ \
		params->RemoveFilter(param1, param2); \
	} \
	else  \
		g_f4seee##_event##Regs.Unregister(thisObject->GetHandle(), thisObject->GetObjectType()); \
 \
	g_f4seee##_event##Regs.Release(); \
}

namespace f4seeePapyrus
{
	void RegisterFuncs(VirtualMachine* vm);
}