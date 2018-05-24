#pragma once
#include "f4se/PluginAPI.h"
#include "f4se/PapyrusEvents.h"
#include <unordered_map>

namespace PRKFSerialization
{
	SInt32 GETPP();

	SInt32 GETSP();

	void SETPP(SInt32 val);

	void SETSP(SInt32 val);

	bool GETPRKFStarted();

	void SETPRKFStarted(bool val);

	void RevertCallback(const F4SESerializationInterface * intfc);
	void LoadCallback(const F4SESerializationInterface * intfc);
	void SaveCallback(const F4SESerializationInterface * intfc);

	bool Load(const F4SESerializationInterface * intfc, UInt32 version);
	bool Save(const F4SESerializationInterface * intfc, UInt32 type, UInt32 version);
	void AddTS(UInt32 formID);
	void RemoveTS(UInt32 formID);
	bool CheckTaggedSkill(UInt32 formID);
}