#include <fstream>

#include "PRKFSerialization.h"
#include "f4se/PluginAPI.h"


namespace PRKFSerialization
{
	SInt32 PP = 0;
	SInt32 SP = 0;
	bool PRKFStarted = false;
	std::set<UInt32> taggedSkills;

	SInt32 GETPP()
	{
		return PP;
	}

	SInt32 GETSP()
	{
		return SP;
	}

	void SETPP(SInt32 val)
	{
		PP = val;
	}

	void SETSP(SInt32 val)
	{
		SP = val;
	}

	bool GETPRKFStarted()
	{
		return PRKFStarted;
	}

	void SETPRKFStarted(bool val)
	{
		PRKFStarted = val;
	}

	void RevertCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Clearing PRKF serialization data.");
		SETPP(0);
		SETSP(0);
		SETPRKFStarted(false);
		taggedSkills.clear();
	}

	void LoadCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Loading PRKF serialization data.");
		UInt32 type, version, length;
		while (intfc->GetNextRecordInfo(&type, &version, &length))
		{
			_DMESSAGE("type %i", type);
			switch (type)
			{
			case 'PRKF':
				_DMESSAGE("Loading PRKF type");
				Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			}
		}
		
	}

	bool Load(const F4SESerializationInterface * intfc, UInt32 version)
	{
		if (!Serialization::ReadData(intfc, &PRKFStarted))
		{
			_MESSAGE("Error loading PRKFStarted var");
			return false;
		}
		_MESSAGE("PRKFStarted: %s", PRKFStarted ? "true" : "false");
		if (!Serialization::ReadData(intfc, &PP))
		{
			_MESSAGE("Error loading PP var");
			return false;
		}
		_MESSAGE("PP count loaded: %i", PP);
		if (!Serialization::ReadData(intfc, &SP))
		{
			_MESSAGE("Error loading SP var");
			return false;
		}
		_MESSAGE("SP count loaded: %i", SP);
		UInt32 TSCount = 0;
		if (!Serialization::ReadData(intfc, &TSCount))
		{
			_MESSAGE("Error loading tag skills count");
			return false;
		}
		_MESSAGE("Tag skills count loaded: %i", TSCount);
		for (UInt32 i = 0; i < TSCount; i++)
		{
			UInt32 oldformId = 0;
			UInt32 newformId = 0;

			if (!Serialization::ReadData(intfc, &oldformId))
			{
				_MESSAGE("Error loading formId parameter");
				return false;
			}

			// Skip if handle is no longer valid.
			if (!intfc->ResolveFormId(oldformId, &newformId))
				continue;

			taggedSkills.insert(newformId);
		}
		return true;
	}

	void SaveCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Save PRKF serialization data.");
		Save(intfc, 'PRKF', InternalEventVersion::kCurrentVersion);
	}

	bool Save(const F4SESerializationInterface * intfc, UInt32 type, UInt32 version)
	{
		intfc->OpenRecord(type, version);
		_MESSAGE("PRKFStarted: %s", PRKFStarted? "true":"false");
		if (!intfc->WriteRecordData(&PRKFStarted, sizeof(PRKFStarted)))
			return false;
		_MESSAGE("PP count to save: %i", PP);
		if (!intfc->WriteRecordData(&PP, sizeof(PP)))
			return false;
		_MESSAGE("SP count to save: %i", SP);
		if (!intfc->WriteRecordData(&SP, sizeof(SP)))
			return false;
		UInt32 size = taggedSkills.size();
		_MESSAGE("Tag skills count to save: %i", size);
		if (!intfc->WriteRecordData(&size, sizeof(size)))
			return false;

		for (auto & form : taggedSkills)
		{
			UInt32 formId = form;
			if (!intfc->WriteRecordData(&formId, sizeof(formId)))
				return false;
		}
		return true;
	}

	void AddTS(UInt32 formID)
	{
		taggedSkills.insert(formID);
	}

	void RemoveTS(UInt32 formID)
	{
		taggedSkills.erase(formID);
	}

	bool CheckTaggedSkill(UInt32 formID)
	{
		return taggedSkills.find(formID) != taggedSkills.end();
	}
	/*
	
		void AddFilter(TESForm * form1, TESForm * form2)
	{
		pairs.insert(std::make_pair(form1 ? form1->formID : 0, form2 ? form2->formID : 0));
	}

	void RemoveFilter(TESForm * form1, TESForm * form2)
	{
		pairs.erase(std::make_pair(form1 ? form1->formID : 0, form2 ? form2->formID : 0));
	}

	bool HasFilter(TESForm * form1, TESForm * form2) const
	{
		return pairs.find(std::make_pair(form1 ? form1->formID : 0, form2 ? form2->formID : 0)) != pairs.end();
	}

	bool NoFilter() const
	{
		return pairs.size() == 0;
	}
	*/
	
}