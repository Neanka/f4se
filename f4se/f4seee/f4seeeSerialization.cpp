#include <fstream>

#include "f4seeeSerialization.h"
#include "f4se/PluginAPI.h"
#include "f4seeeEvents.h"

namespace f4eeeSerialization
{
	void RevertCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Clearing f4eee serialization data.");
		g_f4seeeTESActivateEventRegs.Clear();
		g_f4seeeTESExitFurnitureEventRegs.Clear();
		g_f4seeeLevelIncrease__EventRegs.Clear();
		g_f4seeeTESActiveEffectApplyRemoveEventRegs.Clear();
		g_f4seeeTESActorLocationChangeEventRegs.Clear();
	}

	void LoadCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Loading f4eee serialization data.");
		UInt32 type, version, length;
		while (intfc->GetNextRecordInfo(&type, &version, &length))
		{
			_DMESSAGE("type %i", type);
			switch (type)
			{
			case 'E024':
				_DMESSAGE("Loading g_f4seeeTESActivateEventRegs.");
				g_f4seeeTESActivateEventRegs.Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			case 'E025':
				_DMESSAGE("Loading g_f4seeeTESExitFurnitureEventRegs.");
				g_f4seeeTESExitFurnitureEventRegs.Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			case 'E026':
				_DMESSAGE("Loading g_f4seeeTESActiveEffectApplyRemoveEventRegs.");
				g_f4seeeTESActiveEffectApplyRemoveEventRegs.Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			case 'E027':
				_DMESSAGE("Loading g_f4seeeTESActorLocationChangeEventRegs.");
				g_f4seeeTESActorLocationChangeEventRegs.Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			case 'Exx1':
				_DMESSAGE("Loading g_f4seeeLevelIncrease__EventRegs.");
				g_f4seeeLevelIncrease__EventRegs.Load(intfc, InternalEventVersion::kCurrentVersion);
				break;
			}
		}
		
	}

	void SaveCallback(const F4SESerializationInterface * intfc)
	{
		_DMESSAGE("Save f4eee serialization data.");
		g_f4seeeTESActivateEventRegs.Save(intfc, 'E024', InternalEventVersion::kCurrentVersion);
		g_f4seeeTESExitFurnitureEventRegs.Save(intfc, 'E025', InternalEventVersion::kCurrentVersion);
		g_f4seeeTESActiveEffectApplyRemoveEventRegs.Save(intfc, 'E026', InternalEventVersion::kCurrentVersion);
		g_f4seeeTESActorLocationChangeEventRegs.Save(intfc, 'E027', InternalEventVersion::kCurrentVersion);


		g_f4seeeLevelIncrease__EventRegs.Save(intfc, 'Exx1', InternalEventVersion::kCurrentVersion);
		
	}
	
}