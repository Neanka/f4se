#pragma once
#include "f4seee\f4seeeEvents.h"
#include "Shared.h"

#define MAKE_DUMPS 1

#if MAKE_DUMPS == 1
#define DUMP_CLASS(_var) DumpClass(_var, 40);
#else
#define DUMP_CLASS(_var) ;
#endif
/*
#define DECLARE_EVENT_DISPATCHER_EX(Event, address) \
template<> inline BSTEventDispatcher<Event> * GetEventDispatcher() \
{ \
	typedef BSTEventDispatcher<Event> * (*_GetEventDispatcher)(); \
	RelocAddr<_GetEventDispatcher> GetDispatcher(address.GetUIntPtr()-RelocationManager::s_baseAddr); \
	return GetDispatcher(); \
}

#define BASIC_EVENT_HANDLER_INDIRECTIONS(_offset) { {0,1,5},{0x14,1,5},{ _offset,1,5 },{ 0x9,1,5 } }
*/
class ScrapHeap;

struct LoadingStatusChanged
{
	struct Event
	{

	};
};

RVA <BSTEventDispatcher<LoadingStatusChanged::Event>*> LoadingStatusChanged__Event_Dispatcher_address;

void LoadingStatusChanged__Event_Dispatcher_Init()
{
	LoadingStatusChanged__Event_Dispatcher_address = RVA <BSTEventDispatcher<LoadingStatusChanged::Event>*>(
		"LoadingStatusChanged__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00100E80 },
			{ RUNTIME_VERSION_1_10_40, 0x100e80 },
		}, "E8 ? ? ? ? 48 8D 54 24 40 48 8B C8 E8 ? ? ? ? 4C 8D 5C 24 60", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(LoadingStatusChanged::Event, LoadingStatusChanged__Event_Dispatcher_address);

class LoadingStatusChanged__EventSink : public BSTEventSink<LoadingStatusChanged::Event>
{
public:
	virtual EventResult ReceiveEvent(LoadingStatusChanged::Event * evn, void * dispatcher) override
	{
		_MESSAGE("LoadingStatusChanged::Event:");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

LoadingStatusChanged__EventSink _LoadingStatusChanged__EventSink;

class CellAttachDetachEventSink : public BSTEventSink<CellAttachDetachEvent>
{
public:
	virtual EventResult ReceiveEvent(CellAttachDetachEvent * evn, void * dispatcher) override
	{
		_MESSAGE("CellAttachDetachEvent:");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

CellAttachDetachEventSink _CellAttachDetachEventSink;

struct TESHarvestEvent
{
	struct ItemHarvested
	{
		TESForm*			item;		// 00
		TESObjectREFR*		from;		// 08
		//...
	};
};

RVA <BSTEventDispatcher<TESHarvestEvent::ItemHarvested>*> TESHarvestEvent__ItemHarvested_Dispatcher_address;

void TESHarvestEvent__ItemHarvested_Dispatcher_Init()
{
	TESHarvestEvent__ItemHarvested_Dispatcher_address = RVA <BSTEventDispatcher<TESHarvestEvent::ItemHarvested>*>(
		"TESHarvestEvent__ItemHarvested_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00162970 },
			{ RUNTIME_VERSION_1_10_40, 0x162970 },
		}, "E8 ? ? ? ? 48 8D 55 07 48 8B C8", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(TESHarvestEvent::ItemHarvested, TESHarvestEvent__ItemHarvested_Dispatcher_address);

class TESHarvestEvent__ItemHarvestedSink : public BSTEventSink<TESHarvestEvent::ItemHarvested>
{
public:
	virtual EventResult ReceiveEvent(TESHarvestEvent::ItemHarvested * evn, void * dispatcher) override
	{
		_MESSAGE("TESHarvestEvent::ItemHarvested: %s from %s", evn->item->GetFullName(), evn->from->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

TESHarvestEvent__ItemHarvestedSink _TESHarvestEvent__ItemHarvestedSink;

struct PlayerUpdateEvent
{
	// 00
};

RVA <BSTEventDispatcher<PlayerUpdateEvent>*> PlayerUpdateEvent_Dispatcher_address;

void PlayerUpdateEvent_Dispatcher_Init()
{
	PlayerUpdateEvent_Dispatcher_address = RVA <BSTEventDispatcher<PlayerUpdateEvent>*>(
		"PlayerUpdateEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x001A8D90 },
			{ RUNTIME_VERSION_1_10_40, 0x1A8D90 },
		}, "E8 ? ? ? ? 48 8D 54 24 40 48 8B C8 E8 ? ? ? ? 48 8D 4C 24 44", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(PlayerUpdateEvent, PlayerUpdateEvent_Dispatcher_address);

class PlayerUpdateEventSink : public BSTEventSink<PlayerUpdateEvent>
{
public:
	virtual EventResult ReceiveEvent(PlayerUpdateEvent * evn, void * dispatcher) override
	{
		_MESSAGE("PlayerUpdateEvent:");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

PlayerUpdateEventSink _PlayerUpdateEventSink;

class TESObjectMISC;
struct Component
{
	TESObjectMISC*		component;		// 00
	UInt32				count;			// 08
	UInt32				pad0C;			// 0C
};

class bhkWorldM;
struct Workshop
{
	struct WorkshopModeEvent
	{
		TESObjectREFR*	WorkshopRef;		// 00
		bool			start;				// 08
	};
	struct PowerOnEvent
	{
		TESObjectREFR*	ref;				// 00
	};
	struct PowerOffEvent
	{
		TESObjectREFR*	ref;				// 00
	};
	struct ItemGrabbedEvent
	{
		TESObjectREFR*	workshopRef;					// 00
		TESObjectREFR*	objectRef;						// 08
	};
	struct ItemRepairedEvent
	{
		TESObjectREFR*	workshopRef;					// 00
		TESObjectREFR*	objectRef;						// 08
	};
	struct ItemPlacedEvent
	{
		TESObjectREFR*	workshopRef;					// 00
		TESObjectREFR*	objectRef;						// 08
		NiTransform		transform;						// 10
														//...
	};
	struct ItemMovedEvent
	{
		TESObjectREFR*	workshopRef;					// 00
		TESObjectREFR*	objectRef;						// 08
		UInt32          unk10[(0x50 - 0x10) / 4];       // 10
		NiPoint3        position;						// 50

	};
	struct ItemDestroyedEvent
	{
		TESObjectREFR*	workshopRef;					// 00
		TESObjectREFR*	objectRef;						// 08
	};
	struct BuildableAreaEvent							// sink should be added after entering workshop mode
	{
		UInt8			leaveArea;						// 00
	};
	struct ItemScrappedEvent
	{
		void*						unk00;				// 00
		tArray<Component>*			components;			// 08
	};
	struct PlacementStatusEvent							// sink should be added after entering workshop mode
	{
		UInt32						flags;				// 00 flags?
		float						unk04;				// 04 kinda Z coord?
		bhkWorldM*					_bhkWorldM;			// 08
		float						unk10[8];			// 10
		TESObjectREFR*				objectRef;			// 38
		UInt64						unk40;				// 40
		TESObjectREFR*				workshopRef;		// 48
		float						unk50[10];			// 50
		NiTransform					transform;			// 70 
	};
};
STATIC_ASSERT(sizeof(Workshop::PlacementStatusEvent) == 0xB0);

RVA <BSTEventDispatcher<Workshop::ItemPlacedEvent>*> Workshop__ItemPlacedEvent_Dispatcher_address;

void Workshop__ItemPlacedEvent_Dispatcher_Init()
{
	Workshop__ItemPlacedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemPlacedEvent>*>(
		"Workshop__ItemPlacedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00229FB0 },
			{ RUNTIME_VERSION_1_10_40, 0x229FB0 },
			{ RUNTIME_VERSION_1_10_26, 0x229FB0 },
		}, "E8 ? ? ? ? 48 8D 55 90 48 8B C8 E8 ? ? ? ? 48 8B 4D 98", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemPlacedEvent, Workshop__ItemPlacedEvent_Dispatcher_address);

class Workshop__ItemPlacedEventSink : public BSTEventSink<Workshop::ItemPlacedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemPlacedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemPlacedEvent: %s placed in %s at (%f, %f, %f)", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName(), evn->transform.pos.x, evn->transform.pos.y, evn->transform.pos.z);
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemPlacedEventSink _Workshop__ItemPlacedEventSink;

RVA <BSTEventDispatcher<Workshop::ItemRepairedEvent>*> Workshop__ItemRepairedEvent_Dispatcher_address;

void Workshop__ItemRepairedEvent_Dispatcher_Init()
{
	Workshop__ItemRepairedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemRepairedEvent>*>(
		"Workshop__ItemRepairedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A050 },
			{ RUNTIME_VERSION_1_10_40, 0x22A050 },
			{ RUNTIME_VERSION_1_10_26, 0x22A050 },
		}, "E8 ? ? ? ? 48 8D 54 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 28 83 CE FF", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemRepairedEvent, Workshop__ItemRepairedEvent_Dispatcher_address);

class Workshop__ItemRepairedEventSink : public BSTEventSink<Workshop::ItemRepairedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemRepairedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemRepairedEvent: %s repaired in %s", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemRepairedEventSink _Workshop__ItemRepairedEventSink;

RVA <BSTEventDispatcher<Workshop::ItemDestroyedEvent>*> Workshop__ItemDestroyedEvent_Dispatcher_address;

void Workshop__ItemDestroyedEvent_Dispatcher_Init()
{
	Workshop__ItemDestroyedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemDestroyedEvent>*>(
		"Workshop__ItemDestroyedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00229DD0 },
			{ RUNTIME_VERSION_1_10_40, 0x229DD0 },
			{ RUNTIME_VERSION_1_10_26, 0x229DD0 },
		}, "E8 ? ? ? ? 48 8D 55 F0 48 8B C8 E8 ? ? ? ? 48 8B 4D F8", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemDestroyedEvent, Workshop__ItemDestroyedEvent_Dispatcher_address);

class Workshop__ItemDestroyedEventSink : public BSTEventSink<Workshop::ItemDestroyedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemDestroyedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemDestroyedEvent: %s destroyed in %s", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemDestroyedEventSink _Workshop__ItemDestroyedEventSink;

RVA <BSTEventDispatcher<Workshop::ItemMovedEvent>*> Workshop__ItemMovedEvent_Dispatcher_address;

void Workshop__ItemMovedEvent_Dispatcher_Init()
{
	Workshop__ItemMovedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemMovedEvent>*>(
		"Workshop__ItemMovedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00229F10 },
			{ RUNTIME_VERSION_1_10_40, 0x229F10 },
			{ RUNTIME_VERSION_1_10_26, 0x229F10 },
		}, "E8 ? ? ? ? 48 8D 55 D7 48 8B C8", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemMovedEvent, Workshop__ItemMovedEvent_Dispatcher_address);

class Workshop__ItemMovedEventSink : public BSTEventSink<Workshop::ItemMovedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemMovedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemMovedEvent: %s moved in %s to (%f, %f, %f)", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName(), evn->position.x, evn->position.y, evn->position.z);
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemMovedEventSink _Workshop__ItemMovedEventSink;

RVA <BSTEventDispatcher<Workshop::ItemGrabbedEvent>*> Workshop__ItemGrabbedEvent_Dispatcher_address;

void Workshop__ItemGrabbedEvent_Dispatcher_Init()
{
	Workshop__ItemGrabbedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemGrabbedEvent>*>(
		"Workshop__ItemGrabbedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00229E70 },
			{ RUNTIME_VERSION_1_10_40, 0x229E70 },
			{ RUNTIME_VERSION_1_10_26, 0x229E70 },
		}, "E8 ? ? ? ? 48 8D 55 10 48 8B C8 E8 ? ? ? ? 48 8B 4D 18", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemGrabbedEvent, Workshop__ItemGrabbedEvent_Dispatcher_address);

class Workshop__ItemGrabbedEventSink : public BSTEventSink<Workshop::ItemGrabbedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemGrabbedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemGrabbedEvent: %s grabbed in %s", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemGrabbedEventSink _Workshop__ItemGrabbedEventSink;

RVA <BSTEventDispatcher<Workshop::PowerOnEvent>*> Workshop__PowerOnEvent_Dispatcher_address;

void Workshop__PowerOnEvent_Dispatcher_Init()
{
	Workshop__PowerOnEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::PowerOnEvent>*>(
		"Workshop__PowerOnEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A370 },
			{ RUNTIME_VERSION_1_10_40, 0x22A370 },
			{ RUNTIME_VERSION_1_10_26, 0x22A370 },
		}, "48 89 74 24 28 E8 ? ? ? ? 48 8D 54 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 28", 0x5, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::PowerOnEvent, Workshop__PowerOnEvent_Dispatcher_address);

class Workshop__PowerOnEventSink : public BSTEventSink<Workshop::PowerOnEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::PowerOnEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::PowerOnEvent: %s", evn->ref->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__PowerOnEventSink _Workshop__PowerOnEventSink;

RVA <BSTEventDispatcher<Workshop::PowerOffEvent>*> Workshop__PowerOffEvent_Dispatcher_address;

void Workshop__PowerOffEvent_Dispatcher_Init()
{
	Workshop__PowerOffEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::PowerOffEvent>*>(
		"Workshop__PowerOffEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A2D0 },
			{ RUNTIME_VERSION_1_10_40, 0x22A2D0 },
			{ RUNTIME_VERSION_1_10_26, 0x22A2D0 },
		}, "E8 ? ? ? ? 48 8D 94 24 A0 00 00 00 48 8B C8 E8 ? ? ? ? 48 8B 84 24 A0 00 00 00", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::PowerOffEvent, Workshop__PowerOffEvent_Dispatcher_address);

class Workshop__PowerOffEventSink : public BSTEventSink<Workshop::PowerOffEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::PowerOffEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::PowerOffEvent: %s", evn->ref->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__PowerOffEventSink _Workshop__PowerOffEventSink;

struct PickRefUpdateEvent						//sink should be added after entering workshop mode (or when MultiActivateManager active ?)
{
	UInt32				targetRefHandle;		// 00
	UInt32				unk04;					// 04 always 1?
	TESObjectREFR*		workshopRef;			// 08
	void*				unk10;					// 10
	TESObjectREFR*		targetRef;				// 18

};

RVA <BSTEventDispatcher<PickRefUpdateEvent>*> PickRefUpdateEvent_Dispatcher_address;

void PickRefUpdateEvent_Dispatcher_Init()
{
	PickRefUpdateEvent_Dispatcher_address = RVA <BSTEventDispatcher<PickRefUpdateEvent>*>(
		"PickRefUpdateEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A190 },
			{ RUNTIME_VERSION_1_10_40, 0x22A190 },
		}, "E8 ? ? ? ? 48 8D 54 24 58 48 8B C8 E8 ? ? ? ? 48 8B 74 24 30", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(PickRefUpdateEvent, PickRefUpdateEvent_Dispatcher_address);

class PickRefUpdateEventSink : public BSTEventSink<PickRefUpdateEvent>
{
public:
	virtual EventResult ReceiveEvent(PickRefUpdateEvent * evn, void * dispatcher) override
	{
		TESObjectREFR * pRef = nullptr;
		LookupREFRByHandle(&(evn->targetRefHandle), &pRef);
		if (pRef != nullptr)
		{
			_MESSAGE("PickRefUpdateEvent: %s picked, %s, %s", pRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName(), evn->targetRef->baseForm->GetFullName());
			DumpClass(evn->unk10, 30);
		}
		else
		{
			_MESSAGE("PickRefUpdateEvent: pick clear");
		}
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

PickRefUpdateEventSink _PickRefUpdateEventSink;

RVA <BSTEventDispatcher<Workshop::BuildableAreaEvent>*> Workshop__BuildableAreaEvent_Dispatcher_address;

void Workshop__BuildableAreaEvent_Dispatcher_Init()
{
	Workshop__BuildableAreaEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::BuildableAreaEvent>*>(
		"Workshop__BuildableAreaEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00229D30 },
			{ RUNTIME_VERSION_1_10_40, 0x229D30 },
		}, "C6 84 24 40 01 00 00 00", 0x8, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::BuildableAreaEvent, Workshop__BuildableAreaEvent_Dispatcher_address);

class Workshop__BuildableAreaEventSink : public BSTEventSink<Workshop::BuildableAreaEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::BuildableAreaEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::BuildableAreaEvent:");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__BuildableAreaEventSink _Workshop__BuildableAreaEventSink;

RVA <BSTEventDispatcher<Workshop::ItemScrappedEvent>*> Workshop__ItemScrappedEvent_Dispatcher_address;

void Workshop__ItemScrappedEvent_Dispatcher_Init()
{
	Workshop__ItemScrappedEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::ItemScrappedEvent>*>(
		"Workshop__ItemScrappedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A0F0 },
			{ RUNTIME_VERSION_1_10_40, 0x22A0F0 },
		}, "E8 ? ? ? ? 48 8D 55 6F 48 8B C8 E8 ? ? ? ? 48 8B 4D 67", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::ItemScrappedEvent, Workshop__ItemScrappedEvent_Dispatcher_address);

class Workshop__ItemScrappedEventSink : public BSTEventSink<Workshop::ItemScrappedEvent>
{
public:
	virtual EventResult ReceiveEvent(Workshop::ItemScrappedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::ItemScrappedEvent:");
		for (int i = 0; i < evn->components->count; i++)
		{
			Component component;
			evn->components->GetNthItem(i, component);
			_MESSAGE("						got %i %s", component.count, component.component->GetFullName());
		}

		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__ItemScrappedEventSink _Workshop__ItemScrappedEventSink;

RVA <BSTEventDispatcher<Workshop::WorkshopModeEvent>*> Workshop__WorkshopModeEvent_Dispatcher_address;

void Workshop__WorkshopModeEvent_Dispatcher_Init()
{
	Workshop__WorkshopModeEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::WorkshopModeEvent>*>(
		"Workshop__WorkshopModeEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A410 },
			{ RUNTIME_VERSION_1_10_40, 0x22A410 },
			{ RUNTIME_VERSION_1_10_26, 0x22A410 },
		}, "E8 ? ? ? ? 48 8D 55 E0 48 8B C8 E8 ? ? ? ? 48 8B 4D E0", 0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::WorkshopModeEvent, Workshop__WorkshopModeEvent_Dispatcher_address);

class Workshop__WorkshopModeEventSink : public BSTEventSink<Workshop::WorkshopModeEvent>
{
public:
	virtual    EventResult    ReceiveEvent(Workshop::WorkshopModeEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::WorkshopModeEvent: %s %s", evn->WorkshopRef->baseForm->GetFullName(), evn->start ? "start" : "finish");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__WorkshopModeEventSink _Workshop__WorkshopModeEventSink;

RVA <BSTEventDispatcher<Workshop::PlacementStatusEvent>*> Workshop__PlacementStatusEvent_Dispatcher_address;

void Workshop__PlacementStatusEvent_Dispatcher_Init()
{
	Workshop__PlacementStatusEvent_Dispatcher_address = RVA <BSTEventDispatcher<Workshop::PlacementStatusEvent>*>(
		"Workshop__PlacementStatusEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0022A230 },
			{ RUNTIME_VERSION_1_10_40, 0x22A230 },
		}, "88 44 24 70 E8 ? ? ? ? 48 8D 54 24 70 48 8B C8", 0x4, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(Workshop::PlacementStatusEvent, Workshop__PlacementStatusEvent_Dispatcher_address);

class Workshop__PlacementStatusEventSink : public BSTEventSink<Workshop::PlacementStatusEvent>
{
public:
	virtual    EventResult    ReceiveEvent(Workshop::PlacementStatusEvent * evn, void * dispatcher) override
	{
		_MESSAGE("Workshop::PlacementStatusEvent: object: %s workshop: %s ", evn->objectRef->baseForm->GetFullName(), evn->workshopRef->baseForm->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

Workshop__PlacementStatusEventSink _Workshop__PlacementStatusEventSink;


struct BooksRead							// triggered only when u read book first time
{
	struct Event
	{
		TESObjectBOOK*		book;			// 00
	};
};

RVA <BSTEventDispatcher<BooksRead::Event>*> BooksRead__Event_Dispatcher_address;

void BooksRead__Event_Dispatcher_Init()
{
	BooksRead__Event_Dispatcher_address = RVA <BSTEventDispatcher<BooksRead::Event>*>(
		"BooksRead__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00337110 },
		}, "88 4C 24 39 E8 ? ? ? ? 48 8D 54 24 30", 0x4, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(BooksRead::Event, BooksRead__Event_Dispatcher_address);

class BooksRead__EventSink : public BSTEventSink<BooksRead::Event>
{
public:
	virtual EventResult ReceiveEvent(BooksRead::Event * evn, void * dispatcher) override
	{
		_MESSAGE("BooksRead::Event: book %s read ", evn->book->GetFullName());
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

BooksRead__EventSink _BooksRead__EventSink;

struct unk33F6C0Event
{

};

RVA <BSTEventDispatcher<unk33F6C0Event>*> unk33F6C0Event_Dispatcher_address;

void unk33F6C0Event_Dispatcher_Init()
{
	unk33F6C0Event_Dispatcher_address = RVA <BSTEventDispatcher<unk33F6C0Event>*>(
		"unk33F6C0Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x0033F6C0 },
		}, "75 ? 48 85 C9 74 ? 48 8D 81 F0 00 00 00 C3 33 C0", 0x1A);
}
DECLARE_EVENT_DISPATCHER_EX(unk33F6C0Event, unk33F6C0Event_Dispatcher_address);

class unk33F6C0EventSink : public BSTEventSink<unk33F6C0Event>
{
public:
	virtual EventResult ReceiveEvent(unk33F6C0Event * evn, void * dispatcher) override
	{
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

unk33F6C0EventSink _unk33F6C0EventSink;

struct LocationCleared							// triggered only when u clear location first time
{
	struct Event
	{
		void*				unk00;				// 00 
		UInt32				unk08;				// 08 always 1 ?
		UInt32				unk0C;				// 0C
		TESObjectWEAP*		weapon;				// 10
	};
};

RVA <BSTEventDispatcher<LocationCleared::Event>*> LocationCleared__Event_Dispatcher_address;

void LocationCleared__Event_Dispatcher_Init()
{
	LocationCleared__Event_Dispatcher_address = RVA <BSTEventDispatcher<LocationCleared::Event>*>(
		"LocationCleared__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00382500 },
		}, "E8 ? ? ? ? 48 8D 54 24 70 48 8B C8 E8 ? ? ? ? 0F B6 83 34 01 00 00", 0x0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(LocationCleared::Event, LocationCleared__Event_Dispatcher_address);

class LocationCleared__EventSink : public BSTEventSink<LocationCleared::Event>
{
public:
	virtual EventResult ReceiveEvent(LocationCleared::Event * evn, void * dispatcher) override
	{
		_MESSAGE("LocationCleared::Event: with %s", evn->weapon->GetFullName());

		DUMP_CLASS(evn);
		DUMP_CLASS(evn->unk00);

		return kEvent_Continue;
	}
};

LocationCleared__EventSink _LocationCleared__EventSink;

struct LocationLinked								// triggered when assign caravan
{
	struct Event
	{
		BGSLocation*		linkedLoc;				// 00
		BGSLocation*		linkedWith;				// 08
		BGSKeyword*			keyword;				// 10
	};
};

RVA <BSTEventDispatcher<LocationLinked::Event>*> LocationLinked__Event_Dispatcher_address;

void LocationLinked__Event_Dispatcher_Init()
{
	LocationLinked__Event_Dispatcher_address = RVA <BSTEventDispatcher<LocationLinked::Event>*>(
		"LocationLinked__Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x003825D0 },
		}, "4C 89 74 24 40 C6 44 24 48 01", 0xA, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(LocationLinked::Event, LocationLinked__Event_Dispatcher_address);

class LocationLinked__EventSink : public BSTEventSink<LocationLinked::Event>
{
public:
	virtual EventResult ReceiveEvent(LocationLinked::Event * evn, void * dispatcher) override
	{
		_MESSAGE("LocationLinked::Event: %s linked with %s, keyword %s", evn->linkedLoc->GetFullName(), evn->linkedWith->GetFullName(), evn->keyword->keyword.c_str());
		DUMP_CLASS(evn);

		return kEvent_Continue;
	}
};

LocationLinked__EventSink _LocationLinked__EventSink;

struct unk414F60Event
{

};

RVA <BSTEventDispatcher<unk414F60Event>*> unk414F60Event_Dispatcher_address;

void unk414F60Event_Dispatcher_Init()
{
	unk414F60Event_Dispatcher_address = RVA <BSTEventDispatcher<unk414F60Event>*>(
		"unk414F60Event_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00414F60 },
		}, "E8 ? ? ? ? 48 8D 55 17 48 8B C8", 0x0, 1, 5);
}
DECLARE_EVENT_DISPATCHER_EX(unk414F60Event, unk414F60Event_Dispatcher_address);

class unk414F60EventSink : public BSTEventSink<unk414F60Event>
{
public:
	virtual EventResult ReceiveEvent(unk414F60Event * evn, void * dispatcher) override
	{
		_MESSAGE("unk414F60Event:");
		DUMP_CLASS(evn);

		return kEvent_Continue;
	}
};

unk414F60EventSink _unk414F60EventSink;

struct BGSEventProcessedEvent				// ??_7QuestCallbackMgr@GameScript@@6B?$BSTEventSink@UBGSEventProcessedEvent@@@@@
{
	UInt64					unk00;			// 00 kinda counter?
	void*					unk08;			// 08
	void*					unk10;			// 10
	void*					unk18;			// 18
	void*					unk20;			// 20
	void*					unk28;			// 28
};

RVA <BSTEventDispatcher<BGSEventProcessedEvent>*> BGSEventProcessedEvent_Dispatcher_address;

void BGSEventProcessedEvent_Dispatcher_Init()
{
	BGSEventProcessedEvent_Dispatcher_address = RVA <BSTEventDispatcher<BGSEventProcessedEvent>*>(
		"BGSEventProcessedEvent_Dispatcher_address", {
			{ RUNTIME_VERSION_1_10_50, 0x00441110 },
		}, "E8 ? ? ? ? 48 8D 8E A0 00 00 00 48 8D 15 ? ? ? ?", { {0,1,5},{ 0x9,1,5 } });
}
DECLARE_EVENT_DISPATCHER_EX(BGSEventProcessedEvent, BGSEventProcessedEvent_Dispatcher_address);

class BGSEventProcessedEventSink : public BSTEventSink<BGSEventProcessedEvent>
{
public:
	virtual EventResult ReceiveEvent(BGSEventProcessedEvent * evn, void * dispatcher) override
	{
		_MESSAGE("BGSEventProcessedEvent:");
		DUMP_CLASS(evn);
		return kEvent_Continue;
	}
};

BGSEventProcessedEventSink _BGSEventProcessedEventSink;

//class TerminalRunResultsCallback;
//
//struct TerminalMenuItemRunEvent
//{
//	TerminalRunResultsCallback*			terminalRunResultsCallback;			// 00
//	TESObjectREFR*						terminalRef;						// 08
//	UInt32								terminalPageFormID;					// 10
//	UInt16								itemID;								// 1C
//	UInt16								unk1E;								// 1E
//};
//
//RVA <BSTEventDispatcher<TerminalMenuItemRunEvent>*> TerminalMenuItemRunEvent_Dispatcher_address;
//
//void TerminalMenuItemRunEvent_Dispatcher_Init()
//{
//	TerminalMenuItemRunEvent_Dispatcher_address = RVA <BSTEventDispatcher<TerminalMenuItemRunEvent>*>(
//		"TerminalMenuItemRunEvent_Dispatcher_address", {
//			{ RUNTIME_VERSION_1_10_50, 0x004443B0 },
//		}, "4C 89 44 24 28 89 4C 24 30", 0xE, 1, 5);
//}
//DECLARE_EVENT_DISPATCHER_EX(TerminalMenuItemRunEvent, TerminalMenuItemRunEvent_Dispatcher_address);
//
//class TerminalMenuItemRunEventSink : public BSTEventSink<TerminalMenuItemRunEvent>
//{
//public:
//	virtual EventResult ReceiveEvent(TerminalMenuItemRunEvent * evn, void * dispatcher) override
//	{
//		auto page = DYNAMIC_CAST(LookupFormByID(evn->terminalPageFormID), TESForm, BGSTerminal);
//		if (evn->terminalRef)
//		{
//			_MESSAGE("TerminalMenuItemRunEvent: item #%i selected at %s page on %s terminal", evn->itemID, page->GetFullName(), evn->terminalRef->baseForm->GetFullName());
//		}
//		else
//		{
//			_MESSAGE("TerminalMenuItemRunEvent: item #%i selected at %s page on pipboy", evn->itemID, page->GetFullName());
//		}
//
//		DUMP_CLASS(evn);
//		return kEvent_Continue;
//	}
//};
//
//TerminalMenuItemRunEventSink _TerminalMenuItemRunEventSink;

// 024

class TESActivateEventSink : public BSTEventSink<TESActivateEvent>
{
public:
	virtual EventResult ReceiveEvent(TESActivateEvent * evn, void * dispatcher) override
	{
		_MESSAGE("TESActivateEvent: %s activated by %s", evn->activator->baseForm->GetFullName(), evn->actor->baseForm->GetFullName());
		DUMP_CLASS(evn);

		return kEvent_Continue;
	}
};

TESActivateEventSink _TESActivateEventSink;

// 025

class TESExitFurnitureEventSink : public BSTEventSink<TESExitFurnitureEvent>
{
public:
	virtual EventResult ReceiveEvent(TESExitFurnitureEvent * evn, void * dispatcher) override
	{
		_MESSAGE("TESExitFurnitureEvent: %s exit %s furniture", evn->actor->baseForm->GetFullName(), evn->furniture->baseForm->GetFullName());
		DUMP_CLASS(evn);

		return kEvent_Continue;
	}
};

TESExitFurnitureEventSink _TESExitFurnitureEventSink;

// 026

class TESActiveEffectApplyRemoveEventSink : public BSTEventSink<TESActiveEffectApplyRemoveEvent>
{
public:
	virtual EventResult ReceiveEvent(TESActiveEffectApplyRemoveEvent * evn, void * dispatcher) override
	{
		_MESSAGE("TESActiveEffectApplyRemoveEvent:");
		DUMP_CLASS(evn);
		_MESSAGE("%s", evn->activeEffect->effectSettingStruct->effectSetting->fullName.name.c_str());

		return kEvent_Continue;
	}
};

TESActiveEffectApplyRemoveEventSink _TESActiveEffectApplyRemoveEventSink;

void All_Events_Init()
{
	LoadingStatusChanged__Event_Dispatcher_Init();
	CellAttachDetachEvent_Dispatcher_Init(); //+
	TESHarvestEvent__ItemHarvested_Dispatcher_Init();
	PlayerUpdateEvent_Dispatcher_Init();
	Workshop__ItemPlacedEvent_Dispatcher_Init();
	Workshop__ItemRepairedEvent_Dispatcher_Init();
	Workshop__ItemDestroyedEvent_Dispatcher_Init();
	Workshop__ItemMovedEvent_Dispatcher_Init();
	Workshop__ItemGrabbedEvent_Dispatcher_Init();
	Workshop__PowerOnEvent_Dispatcher_Init();
	Workshop__PowerOffEvent_Dispatcher_Init();
	PickRefUpdateEvent_Dispatcher_Init();
	Workshop__BuildableAreaEvent_Dispatcher_Init();
	Workshop__ItemScrappedEvent_Dispatcher_Init();
	Workshop__WorkshopModeEvent_Dispatcher_Init();
	Workshop__PlacementStatusEvent_Dispatcher_Init();
	BooksRead__Event_Dispatcher_Init();
	unk33F6C0Event_Dispatcher_Init();
	LocationCleared__Event_Dispatcher_Init();
	LocationLinked__Event_Dispatcher_Init();
	unk414F60Event_Dispatcher_Init();
	BGSEventProcessedEvent_Dispatcher_Init();
	TerminalMenuItemRunEvent_Dispatcher_Init();
	TESActivateEvent_Dispatcher_Init(); //+
	TESExitFurnitureEvent_Dispatcher_Init(); //+
	TESActiveEffectApplyRemoveEvent_Dispatcher_Init(); //+
}



void Debug_Events_Init()
{
	TESActiveEffectApplyRemoveEvent_Dispatcher_Init();
	unk414F60Event_Dispatcher_Init();
}

#define REGISTER_EVENT(_event, _sink) GetEventDispatcher<_event>()->AddEventSink(&_sink);

void RegisterAllEvents()
{
	//REGISTER_EVENT(LoadingStatusChanged::Event, _LoadingStatusChanged__EventSink);
	//REGISTER_EVENT(CellAttachDetachEvent, _CellAttachDetachEventSink);
	//REGISTER_EVENT(TESHarvestEvent::ItemHarvested, _TESHarvestEvent__ItemHarvestedSink);
	//REGISTER_EVENT(PlayerUpdateEvent, _PlayerUpdateEventSink);
	//REGISTER_EVENT(Workshop::ItemPlacedEvent, _Workshop__ItemPlacedEventSink);
	//REGISTER_EVENT(Workshop::ItemRepairedEvent, _Workshop__ItemRepairedEventSink);
	//REGISTER_EVENT(Workshop::ItemDestroyedEvent, _Workshop__ItemDestroyedEventSink);
	//REGISTER_EVENT(Workshop::ItemMovedEvent, _Workshop__ItemMovedEventSink);
	//REGISTER_EVENT(Workshop::ItemGrabbedEvent, _Workshop__ItemGrabbedEventSink);
	//REGISTER_EVENT(Workshop::PowerOnEvent, _Workshop__PowerOnEventSink);
	//REGISTER_EVENT(Workshop::PowerOffEvent, _Workshop__PowerOffEventSink);
	//REGISTER_EVENT(PickRefUpdateEvent, _PickRefUpdateEventSink);	
	//REGISTER_EVENT(Workshop::BuildableAreaEvent, _Workshop__BuildableAreaEventSink);
	//REGISTER_EVENT(Workshop::ItemScrappedEvent, _Workshop__ItemScrappedEventSink);
	//REGISTER_EVENT(Workshop::WorkshopModeEvent, _Workshop__WorkshopModeEventSink);
	//REGISTER_EVENT(Workshop::PlacementStatusEvent, _Workshop__PlacementStatusEventSink);
	//REGISTER_EVENT(BooksRead::Event, _BooksRead__EventSink);
	//REGISTER_EVENT(unk33F6C0Event, _unk33F6C0EventSink);
	//REGISTER_EVENT(LocationCleared::Event, _LocationCleared__EventSink);
	//REGISTER_EVENT(LocationLinked::Event, _LocationLinked__EventSink);
	//REGISTER_EVENT(unk414F60Event, _unk414F60EventSink);
	//REGISTER_EVENT(BGSEventProcessedEvent, _BGSEventProcessedEventSink);
	//REGISTER_EVENT(TerminalMenuItemRunEvent, _TerminalMenuItemRunEventSink);
	//REGISTER_EVENT(TESActivateEvent, _TESActivateEventSink);
	//REGISTER_EVENT(TESExitFurnitureEvent, _TESExitFurnitureEventSink);
	//REGISTER_EVENT(TESActiveEffectApplyRemoveEvent, _TESActiveEffectApplyRemoveEventSink);

	auto dispatcher = GetEventDispatcher<TESExitFurnitureEvent>();//
	_MESSAGE("DumpClass(dispatcher, 0xC);");
	DumpClass(dispatcher, 0xC);
	DumpClass(*(Utils::GetOffsetPtr<void*>(dispatcher, 0x8)), 0xD);

}





#include "papfunctions.h"
typedef BSTEventDispatcher<unk33F6C0Event>*(*_dispatcher)();
RelocAddr <_dispatcher> dispatcher(0x033F6C0);
_dispatcher dispatcher_Original = nullptr;

void* dispatcher_Hook() {


	BSTEventDispatcher<unk33F6C0Event>* result = dispatcher_Original();
	_MESSAGE("got unk33F6C0Event dispatcher");
	papMessageBox("got unk33F6C0Event dispatcher");
	DUMP_CLASS(result);
	return result;
}