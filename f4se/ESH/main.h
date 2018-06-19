#pragma once

#include "Shared.h"

struct WeapStruct
{
	TESObjectWEAP* weap;
	int prefPos;

	WeapStruct(TESObjectWEAP* w, int p) : weap(w), prefPos(p) {}

	bool operator < (const WeapStruct& str) const
	{
		return (prefPos < str.prefPos);
	}
};

class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override;
};

class ESH_TESEquipEventSink : public BSTEventSink<TESEquipEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESEquipEvent * evn, void * dispatcher) override;
};

extern ESH_TESEquipEventSink g_ESH_TESEquipEventSink;

class ESH_TESContainerChangedEventSink : public BSTEventSink<TESContainerChangedEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher) override;
};

extern ESH_TESContainerChangedEventSink g_ESH_TESContainerChangedEventSink;

void checkEquippedExplosiveListPosition();

void checkEquippedExplosive();
