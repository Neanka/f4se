#pragma once
#include "f4se/PapyrusEvents.h"
#include "RVA.h"
#include "f4se/GameObjects.h"

/* added in f4se 0.6.7
// 2F0
class TESQuest : public TESForm
{
public:

	enum { kTypeID = kFormType_QUST };

	UInt64	parentData;		// 020 - From BGSStoryManagerTreeForm, not defined yet in F4SE

	TESFullName	fullName;	// 028
	UInt8	unk038[0xF0 - 0x38];	// 038

	UInt32	unk0F0;		// 0F0
	UInt16	flags;		// 0F4
	UInt8	priority;	// 0F6
	UInt8	type;		// 0F7

	UInt8	unk0F8[0x2F0 - 0xF8];	// 0F8

	bool IsCompleted()
	{
		return ((flags >> 1) & 1);
	}

	void SetActive(bool active)
	{
		if (active)
		{
			flags |= 0x800;
		}
		else
		{
			flags &= ~0x800;
		}
	}
};
STATIC_ASSERT(offsetof(TESQuest, type) == 0xF7);
*/

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

struct PickRefUpdateEvent						//sink should be added after entering workshop mode (or when MultiActivateManager active ?)
{
	UInt32				targetRefHandle;		// 00
	UInt32				unk04;					// 04 always 1?
	TESObjectREFR*		workshopRef;			// 08
	void*				unk10;					// 10
	TESObjectREFR*		targetRef;				// 18

};

class FormsPairParameters
{
public:
	std::set<std::pair<UInt32, UInt32>> pairs;

	bool Save(const F4SESerializationInterface * intfc, UInt32 version) const
	{
		UInt32 size = pairs.size();
		_MESSAGE("pairs size: %i", size);
		if (!intfc->WriteRecordData(&size, sizeof(size)))
			return false;
		_MESSAGE("WriteRecordData size successed");

		for (auto & pair : pairs)
		{
			if (!intfc->WriteRecordData(&pair, sizeof(pair)))
				return false;
			_MESSAGE("WriteRecordData pair successed");
		}

		return true;
	}

	bool Load(const F4SESerializationInterface * intfc, UInt32 version)
	{
		UInt32 size = 0;
		if (!Serialization::ReadData(intfc, &size))
		{
			_MESSAGE("Error loading pairs size parameter");
			return false;
		}
		_MESSAGE("pairs size: %i", size);
		for (UInt32 i = 0; i < size; i++)
		{
			std::pair<UInt32, UInt32> pair;
			if (!Serialization::ReadData(intfc, &pair))
			{
				_MESSAGE("Error loading pair parameter");
				return false;
			}
			UInt32 oldformId1 = pair.first;
			UInt32 newformId1 = 0;

			UInt32 oldformId2 = pair.second;
			UInt32 newformId2 = 0;

			// Skip if handle is no longer valid.
			if (oldformId1 != 0)
			{
				if (!intfc->ResolveFormId(oldformId1, &newformId1))
					continue;
			}
			if (oldformId2 != 0)
			{
				if (!intfc->ResolveFormId(oldformId2, &newformId2))
					continue;
			}

			pairs.insert(std::make_pair(newformId1, newformId2));
		}

		return true;
	}

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

	void Dump(void)
	{
		_MESSAGE("> formId:\t%08X", pairs.size());
	}
};



#define DECLARE_EVENT_DISPATCHER_EX(Event, address) \
template<> inline BSTEventDispatcher<Event> * GetEventDispatcher() \
{ \
	typedef BSTEventDispatcher<Event> * (*_GetEventDispatcher)(); \
	RelocAddr<_GetEventDispatcher> GetDispatcher(address.GetUIntPtr()-RelocationManager::s_baseAddr); \
	return GetDispatcher(); \
}

#define GAME_VM_EVENTS_REG_SIG "E8 ? ? ? ? 49 8B 0F 49 8D 56 10"

#define InventoryEventHandler_EVENTS_REG_SIG "48 89 5C 24 08 57 48 83 EC 20 33 FF 48 8B D9 48 85 C9 74 ? 48 83 C1 10 EB ?"
#define InventoryEventHandler_INDIRECTIONS(_offset) { { _offset,1,5 },{ 0x9,1,5 } }

#define BASIC_EVENT_HANDLER_INDIRECTIONS(_offset) { {0,1,5},{0x14,1,5},{ _offset,1,5 },{ 0x9,1,5 } }
#define BASIC_EVENT_HANDLER_INDIRECTIONS1(_offset) { {0,1,5},{0x14,1,5},{ _offset,1,5 },{ 0x35,1,5 } }

#define FRAGMENT_EVENT_HANDLER_INDIRECTIONS(_offset) { {0,1,5},{0x2C,1,5},{ _offset,1,5 },{ 0x9,1,5 } }


#define REGISTER_EVENT(_event, _sink) GetEventDispatcher<_event>()->AddEventSink(&_sink);

// 002 

struct CellAttachDetachEvent
{
	enum status {
		finish		= (1 << 0),
		detaching	= (1 << 1)
	};
	TESObjectCELL*				cell;			// 00
	UInt32						status;			// 08  0 start attach 1 finish attach 2 start detach 3 finish detach
};

extern RVA <BSTEventDispatcher<CellAttachDetachEvent>*> CellAttachDetachEvent_Dispatcher_address;

void CellAttachDetachEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(CellAttachDetachEvent, CellAttachDetachEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeCellAttachDetachEventRegs;

class f4seeeCellAttachDetachEventSink : public BSTEventSink<CellAttachDetachEvent>
{
public:
	virtual	EventResult	ReceiveEvent(CellAttachDetachEvent * evn, void * dispatcher) override;
};

extern f4seeeCellAttachDetachEventSink g_f4seeeCellAttachDetachEventSink;

// 024 BasicEventHandler@GameScript@@

struct TESActivateEvent
{
	TESObjectREFR*			activator;		// 00
	Actor*					actor;		// 08
};

extern RVA <BSTEventDispatcher<TESActivateEvent>*> TESActivateEvent_Dispatcher_address;

void TESActivateEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESActivateEvent, TESActivateEvent_Dispatcher_address);

extern RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESActivateEventRegs;

class f4seeeTESActivateEventSink : public BSTEventSink<TESActivateEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESActivateEvent * evn, void * dispatcher) override;
};

extern f4seeeTESActivateEventSink g_f4seeeTESActivateEventSink;

// 025 BasicEventHandler@GameScript@@

struct TESExitFurnitureEvent
{
	TESObjectREFR*			furniture;		// 00
	Actor*					actor;			// 08
};

extern RVA <BSTEventDispatcher<TESExitFurnitureEvent>*> TESExitFurnitureEvent_Dispatcher_address;

void TESExitFurnitureEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESExitFurnitureEvent, TESExitFurnitureEvent_Dispatcher_address);

extern RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESExitFurnitureEventRegs;

class f4seeeTESExitFurnitureEventSink : public BSTEventSink<TESExitFurnitureEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESExitFurnitureEvent * evn, void * dispatcher) override;
};

extern f4seeeTESExitFurnitureEventSink g_f4seeeTESExitFurnitureEventSink;

// 026 BasicEventHandler@GameScript@@

class ReferenceEffectController
{
public:
	void*											unk00;				// 00
};

class ActiveEffectReferenceEffectController
{
public:
	ReferenceEffectController						unk00;				// 00
};

/*
class ActiveEffect
{
public:
enum
{
kFlag_Inactive = 0x8000
};

void												** _vtbl;								// 00
UInt64												unk08;									// 08
ActiveEffectReferenceEffectController				controller;								// 10
UInt64												unk20[(0x38 - 0x20) >> 3];				// 20
UInt32												casterHandle;							// 38
NiNode												* niNode;								// 40  NiNode
MagicItem											* item;									// 48
MagicItem::EffectItem								* effect;								// 50  effectsettings???????????
TESObjectREFR										* reference;							// 58  -0x110 MagicTarget; DYNAMIC_CAST
UInt64												unk68;									// 60
UInt64												unk70;									// 68
UInt64												unk78;									// 70
float												elapsed;								// 78
float												duration;								// 7C
float												magnitude;								// 80
UInt32												flags;									// 84
UInt32												unk88;									// 88
UInt32												unk8C;									// 8C
UInt32												effectNum;								// 90 - Somekind of counter used to determine whether the ActiveMagicEffect handle is valid
UInt32												unk94;									// 94
ActorValueInfo										* actorValue;							// 98 - Only seems to appear on value modifiers
float												unkA0;									// A0  //float
UInt32												unkA4;									// A4
};
static_assert(sizeof(ActiveEffect) == 0xA8, "sizeof(ActiveEffect) != 0xA8");


class MagicItem : public TESBoundObject
{
public:

// @members
struct EffectItem
{
struct Description
{
const char        * pDescription;
UInt16            unk08;
UInt16            unk0A;
UInt16            unk0C;
UInt16            unk0E;
};

float                magnitude;        // 00
UInt32                area;            // 04
UInt32                duration;        // 08
UInt32                unk0C;            // 0C
EffectSetting        * mgef;            // 10
float                cost;            // 18 - ?
UInt32                unk14;            // 1C - ?
Condition            * conditions;    // 20

EffectItem()
{
magnitude = 0;
area = 0;
duration = 0;
mgef = nullptr;
cost = 0.0;
unk14 = 0;
}
DEFINE_MEMBER_FUNCTION(GetMagnitude, float, 0x6D1D0);//48 8B 41 10 8B 50 70 C1 EA 0A F6 C2 01 74 04
DEFINE_MEMBER_FUNCTION(GetDuration, UInt32, 0x6D290);//48 8B 41 10 8B 50 70 C1 EA 09
DEFINE_MEMBER_FUNCTION(CalcDescription, void, 0x06D480, Description&, const char *, const char *, float magnitude, float duration);//4C 8B DC 49 89 5B 08 49 89 6B 10 49 89 73 18 57 48 83 EC 50 44 8B 15 ? ? ? ?
};

TESFullName                name;            // 68
BGSKeywordForm            keywordForm;    // 78
tArray<EffectItem*>        effectItems;    // 98
UInt64                    unk0B0[4];        // B0
};
STATIC_ASSERT(offsetof(MagicItem, unk0B0) == 0x0B0);
STATIC_ASSERT(sizeof(MagicItem) == 0x0D0);


*/
class ActiveEffect
{
	ActiveEffect() { }
	virtual ~ActiveEffect() { }
public:
	//	void	** _vtbl;	// 00
	BSIntrusiveRefCounted							unk08;						// 08
	UInt32											pad0C;						// 0C
	ActiveEffectReferenceEffectController			unk10;						// 10
	ActiveEffect*									activeEffect;				// 18 why it always point to itself ?
	UInt32											unk20;						// 20
	UInt32											unk24;						// 24
	UInt32											unk28;						// 28
	UInt32											unk2C;						// 2C
	SInt32											unk30;						// 30 always -1 ?
	UInt16											unk34;						// 34
	UInt16											pad36;						// 36
	UInt32											unk38;						// 38
	NiNode*											niNode;						// 40
	MagicItem*										magicItem;					// 48 AlchemyItem, SpellItem etc.

	struct EffectSettingStruct
	{
		float						magnitude;			// 00
		UInt32						unk04;				// 04
		UInt32						unk08;				// 08
		UInt32						unk0C;				// 0C
		EffectSetting*				effectSetting;		// 10
		UInt64						unk18;				// 18
		UInt64						unk20;				// 20
	};
	STATIC_ASSERT(sizeof(EffectSettingStruct) == 0x28);

	EffectSettingStruct*							effectSettingStruct;		// 50



};
STATIC_ASSERT(sizeof(ActiveEffect) == 0x58);

struct TESActiveEffectApplyRemoveEvent
{
	Actor*					actor1;					// 00
	Actor*					actor2;					// 08
	UInt32					unk10[2];				// 10
	ActiveEffect*			activeEffect;			// 18
};

extern RVA <BSTEventDispatcher<TESActiveEffectApplyRemoveEvent>*> TESActiveEffectApplyRemoveEvent_Dispatcher_address;

void TESActiveEffectApplyRemoveEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESActiveEffectApplyRemoveEvent, TESActiveEffectApplyRemoveEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESActiveEffectApplyRemoveEventRegs;

class f4seeeTESActiveEffectApplyRemoveEventSink : public BSTEventSink<TESActiveEffectApplyRemoveEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESActiveEffectApplyRemoveEvent * evn, void * dispatcher) override;
};

extern f4seeeTESActiveEffectApplyRemoveEventSink g_f4seeeTESActiveEffectApplyRemoveEventSink;

// 027 BasicEventHandler@GameScript@@ 

struct TESActorLocationChangeEvent
{
	Actor*						actor;				// 00
	BGSLocation*				oldLoc;				// 08
	BGSLocation*				newLoc;				// 10
};

extern RVA <BSTEventDispatcher<TESActorLocationChangeEvent>*> TESActorLocationChangeEvent_Dispatcher_address;

void TESActorLocationChangeEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESActorLocationChangeEvent, TESActorLocationChangeEvent_Dispatcher_address);

extern RegistrationSetHolder<FormsPairParameters>							g_f4seeeTESActorLocationChangeEventRegs;

class f4seeeTESActorLocationChangeEventSink : public BSTEventSink<TESActorLocationChangeEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESActorLocationChangeEvent * evn, void * dispatcher) override;
};

extern f4seeeTESActorLocationChangeEventSink g_f4seeeTESActorLocationChangeEventSink;

// 028 BasicEventHandler@GameScript@@ 

#include "GameExtraData.h"
class TESObjectBOOK : public TESBoundObject
{

public:
	enum { kTypeID = kFormType_BOOK };

	enum	// type - these are technically flags
	{
		kType_None = 0,
		kType_Skill = 1 << 0,	// 01
		kType_CantBeTaken = 1 << 1,	// 02
		kType_Spell = 1 << 2,	// 04 takes priority over skill
		kType_Read = 1 << 3,	// 08 set once the book is equipped by the player, along with the CHANGE_BOOK_READ (0x40) change flag
		kType_AddPerk = 1 << 4
	};

	TESFullName					fullName;
	BGSModelMaterialSwap		materialSwap;
	TESIcon						icon;
	TESValueForm				value;
	TESWeightForm				weight;
	TESDescription				description; // E8
	BGSDestructibleObjectForm	destructible;
	BGSMessageIcon				messageIcon;
	BGSPickupPutdownSounds		pickupSounds;
	BGSKeywordForm				keyword;
	BGSFeaturedItemMessage		featuredMessage;

	UInt8						flags;					// 0x170
	BGSPerk						* unk178;
	UInt64						unk180;
	void						* unk188;				// TESObjectSTAT
	TESDescription				description2;
};
STATIC_ASSERT(sizeof(TESObjectBOOK) == 0x1A8);
STATIC_ASSERT(offsetof(TESObjectBOOK, description) == 0xE8);

class ExtraStartingPosition : public BSExtraData
{
public:
	float				xPos;					// 18
	float				yPos;					// 1C
	float				zPos;					// 20
	float				xRot;					// 24
	float				yRot;					// 28
	float				zRot;					// 2C
	BGSLocation*		location;				// 30
};
STATIC_ASSERT(sizeof(ExtraStartingPosition) == 0x38);

struct TESBookReadEvent
{
	TESObjectREFR*							ref;					// 00
	UInt32									unk08;					// 08
	UInt32									unk0C;					// 0C
	UInt64									unk10;					// 10
	void*									unk18;					// 18
	ExtraDataList*							unk20;					// 20 if ref
	UInt32									unk28[4];				// 28
	TESObjectBOOK*							book;					// 38
	void*									unk40;					// 40
};
STATIC_ASSERT(sizeof(TESBookReadEvent) == 0x48);

extern RVA <BSTEventDispatcher<TESBookReadEvent>*> TESBookReadEvent_Dispatcher_address;

void TESBookReadEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESBookReadEvent, TESBookReadEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESBookReadEventRegs;

class f4seeeTESBookReadEventSink : public BSTEventSink<TESBookReadEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESBookReadEvent * evn, void * dispatcher) override;
};

extern f4seeeTESBookReadEventSink g_f4seeeTESBookReadEventSink;

// 029 BasicEventHandler@GameScript@@ 

struct TESCellAttachDetachEvent
{
	TESObjectREFR*							ref;					// 00
	UInt8									attached;				// 08
	UInt8									pad09[7];				// 09
};

extern RVA <BSTEventDispatcher<TESCellAttachDetachEvent>*> TESCellAttachDetachEvent_Dispatcher_address;

void TESCellAttachDetachEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESCellAttachDetachEvent, TESCellAttachDetachEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESCellAttachDetachEventRegs;

class f4seeeTESCellAttachDetachEventSink : public BSTEventSink<TESCellAttachDetachEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESCellAttachDetachEvent * evn, void * dispatcher) override;
};

extern f4seeeTESCellAttachDetachEventSink g_f4seeeTESCellAttachDetachEventSink;

// 030 BasicEventHandler@GameScript@@ 

struct TESCellFullyLoadedEvent
{
	TESObjectCELL*				cell;			// 00
};

extern RVA <BSTEventDispatcher<TESCellFullyLoadedEvent>*> TESCellFullyLoadedEvent_Dispatcher_address;

void TESCellFullyLoadedEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESCellFullyLoadedEvent, TESCellFullyLoadedEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESCellFullyLoadedEventRegs;

class f4seeeTESCellFullyLoadedEventSink : public BSTEventSink<TESCellFullyLoadedEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESCellFullyLoadedEvent * evn, void * dispatcher) override;
};

extern f4seeeTESCellFullyLoadedEventSink g_f4seeeTESCellFullyLoadedEventSink;

// 031 have no papyrus analog

struct TESCellReadyToApplyDecalsEvent
{
	TESObjectCELL*				cell;			// 00
};

extern RVA <BSTEventDispatcher<TESCellReadyToApplyDecalsEvent>*> TESCellReadyToApplyDecalsEvent_Dispatcher_address;

void TESCellReadyToApplyDecalsEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESCellReadyToApplyDecalsEvent, TESCellReadyToApplyDecalsEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESCellReadyToApplyDecalsEventRegs;

class f4seeeTESCellReadyToApplyDecalsEventSink : public BSTEventSink<TESCellReadyToApplyDecalsEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESCellReadyToApplyDecalsEvent * evn, void * dispatcher) override;
};

extern f4seeeTESCellReadyToApplyDecalsEventSink g_f4seeeTESCellReadyToApplyDecalsEventSink;


// 032 BasicEventHandler@GameScript@@ A0h

struct TESCombatEvent_x // defined in GameEvents.h
{
	TESObjectREFR*						source;		// 00
	TESObjectREFR*						target;		// 08
	UInt32								state;		// 10
};

extern RVA <BSTEventDispatcher<TESCombatEvent_x>*> TESCombatEvent_x_Dispatcher_address;

void TESCombatEvent_x_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESCombatEvent_x, TESCombatEvent_x_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESCombatEvent_xRegs;

class f4seeeTESCombatEvent_xSink : public BSTEventSink<TESCombatEvent_x>
{
public:
	virtual	EventResult	ReceiveEvent(TESCombatEvent_x * evn, void * dispatcher) override;
};

extern f4seeeTESCombatEvent_xSink g_f4seeeTESCombatEvent_xSink;





// xx1 

struct LevelIncrease
{
	struct Event
	{
		UInt32				gainedLevel;			// 00
		UInt32				pad04;					// 04
		Actor*				actor;					// 08
		UInt32				unk10;					// 10 always 1 ?
		UInt32				unk14;					// 14
		float				gainedExp;				// 18
		UInt32				unk1C[3];				// 1C
		Actor*				actor1;					// 28
		void*				unk30;					// 30
		Actor*				actor2;					// 38
		UInt32				fromLevel;				// 40
		UInt32				pad44;					// 44
	};
};

extern RVA <BSTEventDispatcher<LevelIncrease::Event>*> LevelIncrease__Event_Dispatcher_address;

void LevelIncrease__Event_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(LevelIncrease::Event, LevelIncrease__Event_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeLevelIncrease__EventRegs;

class f4seeeLevelIncrease__EventSink : public BSTEventSink<LevelIncrease::Event>
{
public:
	virtual	EventResult	ReceiveEvent(LevelIncrease::Event * evn, void * dispatcher) override;
};

extern f4seeeLevelIncrease__EventSink g_f4seeeLevelIncrease__EventSink;




// xx2 

struct DoBeforeNewOrLoadCompletedEvent // dispatcher address 5A9C460 (5A9C450+10)
{

};

// xx3
struct PerkAdded // sub_140571710
{
	struct Event
	{

	};
};


// xx4 BasicEventHandler@GameScript@@ 30h 
struct BGSOnPlayerModArmorWeaponEvent
{
	TESBoundObject*						object;			// 00 TESObjectWEAP or TESObjectARMO
	BGSMod::Attachment::Mod*			mod;			// 08
};

extern RVA <BSTEventDispatcher<BGSOnPlayerModArmorWeaponEvent>*> BGSOnPlayerModArmorWeaponEvent_Dispatcher_address;

void BGSOnPlayerModArmorWeaponEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(BGSOnPlayerModArmorWeaponEvent, BGSOnPlayerModArmorWeaponEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeBGSOnPlayerModArmorWeaponEventRegs;

class f4seeeBGSOnPlayerModArmorWeaponEventSink : public BSTEventSink<BGSOnPlayerModArmorWeaponEvent>
{
public:
	virtual	EventResult	ReceiveEvent(BGSOnPlayerModArmorWeaponEvent * evn, void * dispatcher) override;
};

extern f4seeeBGSOnPlayerModArmorWeaponEventSink g_f4seeeBGSOnPlayerModArmorWeaponEventSink;


class TerminalRunResultsCallback;

// xx5 FragmentEventHandler@GameScript@@ 0h 
struct TerminalMenuItemRunEvent
{
	TerminalRunResultsCallback*			terminalRunResultsCallback;			// 00
	TESObjectREFR*						terminalRef;						// 08
	UInt32								terminalPageFormID;					// 10
	UInt16								itemID;								// 1C
	UInt16								unk1E;								// 1E
};

extern RVA <BSTEventDispatcher<TerminalMenuItemRunEvent>*> TerminalMenuItemRunEvent_Dispatcher_address;

void TerminalMenuItemRunEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TerminalMenuItemRunEvent, TerminalMenuItemRunEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTerminalMenuItemRunEventRegs;

class f4seeeTerminalMenuItemRunEventSink : public BSTEventSink<TerminalMenuItemRunEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TerminalMenuItemRunEvent * evn, void * dispatcher) override;
};

extern f4seeeTerminalMenuItemRunEventSink g_f4seeeTerminalMenuItemRunEventSink;

// xx6 FragmentEventHandler@GameScript@@ 8h 
struct TESPackageEvent
{
	Actor*					actor;			// 00
	//...
};

extern RVA <BSTEventDispatcher<TESPackageEvent>*> TESPackageEvent_Dispatcher_address;

void TESPackageEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESPackageEvent, TESPackageEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESPackageEventRegs;

class f4seeeTESPackageEventSink : public BSTEventSink<TESPackageEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESPackageEvent * evn, void * dispatcher) override;
};

extern f4seeeTESPackageEventSink g_f4seeeTESPackageEventSink;

// xx7 FragmentEventHandler@GameScript@@ 10h 
struct TESPerkEntryRunEvent
{

};

extern RVA <BSTEventDispatcher<TESPerkEntryRunEvent>*> TESPerkEntryRunEvent_Dispatcher_address;

void TESPerkEntryRunEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESPerkEntryRunEvent, TESPerkEntryRunEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESPerkEntryRunEventRegs;

class f4seeeTESPerkEntryRunEventSink : public BSTEventSink<TESPerkEntryRunEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESPerkEntryRunEvent * evn, void * dispatcher) override;
};

extern f4seeeTESPerkEntryRunEventSink g_f4seeeTESPerkEntryRunEventSink;


class StageItemFinishedCallback;

// xx8 FragmentEventHandler@GameScript@@ 18h 
struct TESQuestStageEvent
{
	StageItemFinishedCallback*		unk00;				// 00
	UInt32							questFormID;		// 08
	UInt32							stage;				// 0C
};

extern RVA <BSTEventDispatcher<TESQuestStageEvent>*> TESQuestStageEvent_Dispatcher_address;

void TESQuestStageEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESQuestStageEvent, TESQuestStageEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESQuestStageEventRegs;

class f4seeeTESQuestStageEventSink : public BSTEventSink<TESQuestStageEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESQuestStageEvent * evn, void * dispatcher) override;
};

extern f4seeeTESQuestStageEventSink g_f4seeeTESQuestStageEventSink;

// xx9 FragmentEventHandler@GameScript@@ 20h 
struct TESSceneActionEvent
{
	UInt32						sceneFormID;		// 00
	UInt32						actionIndex;		// 04
	UInt32						questFormID;		// 08
	UInt32						referenceAliasID;		// 0C ????
};

extern RVA <BSTEventDispatcher<TESSceneActionEvent>*> TESSceneActionEvent_Dispatcher_address;

void TESSceneActionEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESSceneActionEvent, TESSceneActionEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESSceneActionEventRegs;

class f4seeeTESSceneActionEventSink : public BSTEventSink<TESSceneActionEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESSceneActionEvent * evn, void * dispatcher) override;
};

extern f4seeeTESSceneActionEventSink g_f4seeeTESSceneActionEventSink;

// unk1
struct ActorItemEquipped
{
	struct Event
	{

	};
};

extern RVA <BSTEventDispatcher<ActorItemEquipped::Event>*> ActorItemEquipped__Event_Dispatcher_address;

void ActorItemEquipped__Event_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(ActorItemEquipped::Event, ActorItemEquipped__Event_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeActorItemEquipped__EventRegs;

class f4seeeActorItemEquipped__EventSink : public BSTEventSink<ActorItemEquipped::Event>
{
public:
	virtual	EventResult	ReceiveEvent(ActorItemEquipped::Event * evn, void * dispatcher) override;
};

extern f4seeeActorItemEquipped__EventSink g_f4seeeActorItemEquipped__EventSink;

// inv1 InventoryEventHandler@GameScript@@ 0h 
struct HolotapeChatterEvent
{

};

extern RVA <BSTEventDispatcher<HolotapeChatterEvent>*> HolotapeChatterEvent_Dispatcher_address;

void HolotapeChatterEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(HolotapeChatterEvent, HolotapeChatterEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeHolotapeChatterEventRegs;

class f4seeeHolotapeChatterEventSink : public BSTEventSink<HolotapeChatterEvent>
{
public:
	virtual	EventResult	ReceiveEvent(HolotapeChatterEvent * evn, void * dispatcher) override;
};

extern f4seeeHolotapeChatterEventSink g_f4seeeHolotapeChatterEventSink;

// inv2 InventoryEventHandler@GameScript@@ 8h 
struct HolotapePlayEvent
{

};

extern RVA <BSTEventDispatcher<HolotapePlayEvent>*> HolotapePlayEvent_Dispatcher_address;

void HolotapePlayEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(HolotapePlayEvent, HolotapePlayEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeHolotapePlayEventRegs;

class f4seeeHolotapePlayEventSink : public BSTEventSink<HolotapePlayEvent>
{
public:
	virtual	EventResult	ReceiveEvent(HolotapePlayEvent * evn, void * dispatcher) override;
};

extern f4seeeHolotapePlayEventSink g_f4seeeHolotapePlayEventSink;

// inv3 InventoryEventHandler@GameScript@@ 10h 
struct TESContainerChangedEvent
{
	UInt32          sourceContainerFormID;              // 00
	UInt32          targetContainerFormID;                // 04
	UInt32          itemFormID;                            // 08
	UInt32          count;                                // 0C
														  //... etc
};

extern RVA <BSTEventDispatcher<TESContainerChangedEvent>*> TESContainerChangedEvent_Dispatcher_address;

void TESContainerChangedEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESContainerChangedEvent, TESContainerChangedEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESContainerChangedEventRegs;

class f4seeeTESContainerChangedEventSink : public BSTEventSink<TESContainerChangedEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher) override;
};

extern f4seeeTESContainerChangedEventSink g_f4seeeTESContainerChangedEventSink;

// inv4 InventoryEventHandler@GameScript@@ 18h 
struct TESEquipEvent
{
	Actor*				ref;			// 00
	UInt32				baseFormID;		// 08
	UInt32				unk0C;			// 0C
	UInt8				unk10;			// 10
	UInt8				unk11;			// 11
	UInt8				status;			// 12	1-equipped, 0-unequipped
	//etc...
};

extern RVA <BSTEventDispatcher<TESEquipEvent>*> TESEquipEvent_Dispatcher_address;

void TESEquipEvent_Dispatcher_Init();

DECLARE_EVENT_DISPATCHER_EX(TESEquipEvent, TESEquipEvent_Dispatcher_address);

extern RegistrationSetHolder<NullParameters>							g_f4seeeTESEquipEventRegs;

class f4seeeTESEquipEventSink : public BSTEventSink<TESEquipEvent>
{
public:
	virtual	EventResult	ReceiveEvent(TESEquipEvent * evn, void * dispatcher) override;
};

extern f4seeeTESEquipEventSink g_f4seeeTESEquipEventSink;




struct PipboyValueChangedEvent
{

};

void InitEvents();