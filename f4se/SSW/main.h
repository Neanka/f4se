#pragma once
#include "Shared.h"

class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent>
{
public:
	virtual ~TESLoadGameHandler() { };
	virtual	EventResult	ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher) override;
};

class MenuOpenCloseHandler : public BSTEventSink<MenuOpenCloseEvent>
{
public:
	virtual ~MenuOpenCloseHandler() { };
	virtual	EventResult	ReceiveEvent(MenuOpenCloseEvent * evn, void * dispatcher) override;
};

class DifficultyChangedHandler : public BSTEventSink<PlayerDifficultySettingChanged::Event>
{
public:
	virtual ~DifficultyChangedHandler() { };
	virtual	EventResult	ReceiveEvent(PlayerDifficultySettingChanged::Event * evn, void * dispatcher) override;
};

void UpdateValues_int();
