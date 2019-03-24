#pragma once
#include "Shared.h"
#include "f4se/PapyrusNativeFunctions.h"

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

/*class DifficultyChangedHandler : public BSTEventSink<PlayerDifficultySettingChanged::Event>
{
public:
	virtual ~DifficultyChangedHandler() { };
	virtual	EventResult	ReceiveEvent(PlayerDifficultySettingChanged::Event * evn, void * dispatcher) override;
};*/

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

struct ScriptFunctionRegParam2
{
public:
	BSFixedString functionName;
	BSFixedString scriptName;
	//...
};

void * ScriptFunctionReg_Hook(ScriptFunction * param1, ScriptFunctionRegParam2 * param2);

struct PlayerStats
{
public:
	VMValue maxHunger;
	VMValue maxThirst;
	VMValue maxSleepless;
	VMValue currentHunger;
	VMValue currentThirst;
	VMValue currentSleepless;
};

void UpdateValues_int();

void UpdateValues_int_HMO(PlayerStats* stats);
