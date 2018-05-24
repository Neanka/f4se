#include <fstream>

#include "PBTSerialization.h"
#include "f4se/PluginAPI.h"


namespace PBTSerialization
{
	std::set<UInt32> readedNotes;


	void RevertCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Clearing PBT serialization data.");
		readedNotes.clear();
	}

	void LoadCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Loading PBT serialization data.");
		UInt32 type, version, length;
		while (intfc->GetNextRecordInfo(&type, &version, &length))
		{
			_DMESSAGE("type %i", type);
			switch (type)
			{
			case 'PBT':
				_DMESSAGE("Loading PBT type");
				Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			}
		}
		
	}

	bool Load(const F4SESerializationInterface * intfc, UInt32 version)
	{
		UInt32 TSCount = 0;
		if (!Serialization::ReadData(intfc, &TSCount))
		{
			_MESSAGE("Error loading readed notes count");
			return false;
		}
		_MESSAGE("readed notes count loaded: %i", TSCount);
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

			readedNotes.insert(newformId);
		}
		return true;
	}

	void SaveCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Save PBT serialization data.");
		Save(intfc, 'PBT', InternalEventVersion::kCurrentVersion);
	}

	bool Save(const F4SESerializationInterface * intfc, UInt32 type, UInt32 version)
	{
		intfc->OpenRecord(type, version);

		UInt32 size = readedNotes.size();
		_MESSAGE("readed notes count to save: %i", size);
		if (!intfc->WriteRecordData(&size, sizeof(size)))
			return false;

		for (auto & form : readedNotes)
		{
			UInt32 formId = form;
			if (!intfc->WriteRecordData(&formId, sizeof(formId)))
				return false;
		}
		return true;
	}

	void AddRN(UInt32 formID)
	{
		readedNotes.insert(formID);
	}

	void RemoveRN(UInt32 formID)
	{
		readedNotes.erase(formID);
	}

	bool CheckRN(UInt32 formID)
	{
		return readedNotes.find(formID) != readedNotes.end();
	}
}