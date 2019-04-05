#pragma once
#include "Shared2.h"
#include "GameMenus.h"

template <class T>
class PipboyPrimitiveThrottledValue : public PipboyPrimitiveValue<T>
{
public:

	void* unk20;
	void* unk28;
	T value1;
	void* unk38;
	void* unk40;
	void* unk48;
	void* unk50;
	void* unk58;
	void* unk60;
	void* unk68;
};
STATIC_ASSERT(sizeof(PipboyPrimitiveThrottledValue<bool>) == 0x70);

class PipboyObject : public PipboyValue
{
public:
	struct PipboyTableItem
	{
		BSFixedString	key;
		PipboyValue		*value;

		bool operator==(const BSFixedString & a_name) const { return key == a_name; }
		operator BSFixedString() const { return key; }

		static inline UInt32 GetHash(BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data, 0);
			return hash;
		}

		void Dump()
		{
			_MESSAGE("%s", key.c_str());
		}
	};

	virtual ~PipboyObject();

	tHashSet<PipboyTableItem, BSFixedString>	table;	// 18
	tHashSet<UInt32>	table2;	// 48	contain PipboyValue::unk08 values of this object members
	tArray<void*>	unk78;
	UInt8			unk90;

	MEMBER_FN_PREFIX(PipboyObject);
	DEFINE_MEMBER_FN(Construct, PipboyObject*, 0x0, PipboyValue* parent);
	DEFINE_MEMBER_FN(SetMember, void, 0x0, BSFixedString*, PipboyValue*);
	DEFINE_MEMBER_FN(SetMember_BSFixedStringCS, void, 0x0, BSFixedString*, BSFixedString*); // create PipboyPrimitiveValue<BSFixedStringCS> and set as object member
	DEFINE_MEMBER_FN(SetMember_int, void, 0x0, BSFixedString*, SInt32*); // create PipboyPrimitiveValue<int> and set as object member
	DEFINE_MEMBER_FN(SetMember_uint, void, 0x0, BSFixedString*, UInt32*); // create PipboyPrimitiveValue<uint> and set as object member
	DEFINE_MEMBER_FN(SetMember_float, void, 0x0, BSFixedString*, float); // create PipboyPrimitiveValue<float> and set as object member
	DEFINE_MEMBER_FN(SetMember_bool, void, 0x0, BSFixedString*, UInt8*); // create PipboyPrimitiveValue<bool> and set as object member
};
STATIC_ASSERT(sizeof(PipboyObject) == 0x98);

class PipboyArray : public PipboyValue
{
public:

	tArray<PipboyValue*>				value;		// 18
	tHashSet<UInt32>	table;	// 30	contain PipboyValue::unk08 values of this object members
	tArray<void*>	unk60;
	UInt8	unk78; // init'd as 1

	MEMBER_FN_PREFIX(PipboyArray);
	DEFINE_MEMBER_FN(Construct, PipboyArray*, 0x0, PipboyValue* parent);
	DEFINE_MEMBER_FN(PushBack, void, 0x0, PipboyValue*);
	DEFINE_MEMBER_FN(Insert, void, 0x0, PipboyValue*, UInt32);
	DEFINE_MEMBER_FN(PushBack_Object, PipboyObject*, 0x0);
	
	// create object and push into array
};
STATIC_ASSERT(sizeof(PipboyArray) == 0x80);

void tracePipboyPrimitiveValueInt(PipboyPrimitiveValue<SInt32>* val);

void tracePipboyPrimitiveValueUInt(PipboyPrimitiveValue<UInt32>* val);

void tracePipboyPrimitiveValueFloat(PipboyPrimitiveValue<float>* val);

void tracePipboyPrimitiveValueBool(PipboyPrimitiveValue<bool>* val);

void tracePipboyPrimitiveValueBSFixedStringCS(PipboyPrimitiveValue<BSFixedString>* val);

void tracePipboyArray(PipboyArray* arr);
void tracePipboyObject(PipboyObject* obj);
void tracePipboyObjectLight(PipboyObject* obj);
void tracePipboyValue(PipboyValue* pv);

//98
class PipboyDataGroup
{
public:
	virtual ~PipboyDataGroup();

	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();

	BSTEventDispatcher<PipboyValueChangedEvent>			pipboyValueChangedEventDispatcher; // 08
	CRITICAL_SECTION									lpcs;			// 60
	void*												unk88;	// point to pipboydatamanager+0xD18 hashSet
	PipboyObject*										object; // 0x90
};
STATIC_ASSERT(sizeof(PipboyDataGroup) == 0x98);

class PipboyStatsData : public PipboyDataGroup
{
public:
	void*			unk98[20];
};
STATIC_ASSERT(sizeof(PipboyStatsData) == 0x138);

class PipboySpecialData : public PipboyDataGroup
{
public:
	void*			unk98[2];
};
STATIC_ASSERT(sizeof(PipboySpecialData) == 0xA8);

class PipboyPerksData : public PipboyDataGroup
{
public:
	void*			unk98[8];
};
STATIC_ASSERT(sizeof(PipboyPerksData) == 0xD8);



class PipboyInventoryData: public PipboyDataGroup
{
public:
	BSTEventSink<BGSInventoryListEvent::Event>					es1; // 98
	BSTEventSink<ActorEquipManagerEvent::Event>					es2; // A0
	BSTEventSink<ActorValueEvents::ActorValueChangedEvent>		es3; // A8
	BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>		es4; // B0
	BSTEventSink<PerkValueEvents::PerkValueChangedEvent>		es5; // B8
	BSTEventSink<InventoryInterface::FavoriteChangedEvent>		es6; // C0
	BSTEventSink<HolotapeStateChanged::Event>					es7; // C8
	BSTEventSink<BGSInventoryItemEvent::Event>					es8; // D0
	BSTEventSink<FavoriteMgr_Events::ComponentFavoriteEvent>	es9; // D8
	BSTEventSink<PlayerDifficultySettingChanged::Event>			es10; // E0
	PipboyObject*												inventoryObject; // E8

	// 10
	struct HSF0Entry
	{
		UInt32 formid; // ?
		void** unk08;

		void Dump()
		{
			_MESSAGE("formid:  %08X", formid);
			DumpClass(unk08, 10);
			DumpClass(*(void***)*unk08,10);
		}
	};
	
	tHashSet<HSF0Entry, UInt32>							hsF0; // something related to sorting?

	// 10
	struct HS120Entry
	{
		BGSComponent* component;
		PipboyObject* object;

		operator BGSComponent *() const { return component; }

		static inline UInt32 GetHash(BGSComponent ** key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)*key, 0);
			return hash;
		}
		void Dump()
		{
			tracePipboyObject(object);
		}
	};

	tHashSet<HS120Entry, BGSComponent*>					hs120;
	tArray<PipboyObject*>								inventoryObjects;				// 150
	tHashSet<UInt32>									hs168;	// contain FormTypes for update?
};
STATIC_ASSERT(sizeof(PipboyInventoryData) == 0x198);

class PipboyQuestData : public PipboyDataGroup
{
public:
	void*			unk98[10];
};
STATIC_ASSERT(sizeof(PipboyQuestData) == 0xE8);

class PipboyWorkshopData : public PipboyDataGroup
{
public:
	BSTEventSink<ActorValueEvents::ActorValueChangedEvent>		es1;
	BSTEventSink<Workshop::WorkshopModeEvent>					es2;
	PipboyArray*												unkPA_A8;
	tHashSet<UInt32, UInt32>									unkHS_B0;
	tHashSet<UInt32, UInt32>									unkHS_E0;
	tHashSet<UInt32, UInt32>									unkHS_110;
};
STATIC_ASSERT(sizeof(PipboyWorkshopData) == 0x140);

class PipboyLogData : public PipboyDataGroup
{
public:
	void*			unk98[8];
};
STATIC_ASSERT(sizeof(PipboyLogData) == 0xD8);

// 0x238
class PipboyMapData : public PipboyDataGroup
{
public:
	BSTEventSink<TravelMarkerStateChange::Event>			es1;	// 98
	BSTEventSink<PlayerUpdateEvent>							es2;	// A0
	BSTEventSink<BGSActorCellEvent>							es3;	// A8
	BSTEventSink<TESQuestEvent::Event>						es4;	// B0
	BSTEventSink<PlayerCharacterQuestEvent::Event>			es5;	// B8
	BSTEventSink<CustomMarkerUpdate::Event>					es6;	// C0
	BSTEventSink<LocationMarkerArrayUpdate::Event>			es7;	// C8
	BSTEventSink<LocalMapCameraUpdate::Event>				es8;	// D0
	BSTEventSink<TESLocationClearedEvent>					es9;	// D8
	BSTEventSink<ActorValueEvents::ActorValueChangedEvent>	es10;	// E0
	PipboyObject*											mapDataObject;	// always same as 0x90
	/*
	object with fields:
	CurrCell (string)
	CurrWorldspace (string)
	World (object)
		Player (object) 
			Y
			Rotation
			X
		Custom (object)
			Height
			Y (float)
			Visible (bool)
			X (float)
		PowerArmor (object)
			Height
			Y (float)
			Visible (bool)
			X (float)
		Quests (array of objects)
			Height
			Y
			OnDoor (bool)
			Name
			Shared
			QuestId (array of uints)
			X
		Locations (array of objects)
			Y (float)
			Discovered (bool)
			LocationMarkerFormId (uint)
			X (float)
			ClearedStatus (bool)
			Name (string)
			LocationFormId (uint)
			Visible (bool)
			type (uint)
		Extents (object)
			SWX (float)
			NEY (float)
			NWX (float)
			NEX (float)
			NWY (float)
			SWY (float)
		WorldMapTexture (string)
		Local (object)
			Player (object)
				Y
				Rotation
				X
			Custom (object)
				Height
				Y (float)
				Visible (bool)
				X (float)
			PowerArmor (object)
				Height
				Y (float)
				Visible (bool)
				X (float)
			Doors (array of objects)
				Y (float)
				Name
				Visible (bool)
				X (float)
			Quests (array of objects)
				Height
				Y
				OnDoor (bool)
				Name
				Shared
				QuestId (array of uints)
				X
			Extents (object)
				SWX (float)
				NEY (float)
				NWX (float)
				NEX (float)
				NWY (float)
				SWY (float)
	*/
	struct MarkerInfo
	{
		TESFullName*    name;    // 00
		PipboyObject*    obj;    // 08

		/*
		object with fields:

		Discovered (bool)
		type (uint)
		X (float)
		Y (float)
		Name (string)
		LocationFormId (uint)
		LocationMarkerFormId (uint)
		Visible (bool)
		ClearedStatus (bool)

		WorkshopOwned (bool) optional
		WorkshopPopulation (uint) optional
		WorkshopHappinessPct (float) optional

		*/

		bool operator==(const BSFixedString a_key) const { return name->name.data == a_key.data; }
		static inline UInt32 GetHash(const BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data->Get<char>(), 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("fullname: %s", name->name.c_str());
			tracePipboyObject(obj);
		}
	};
	tHashSet<MarkerInfo, TESFullName*>		markersInfo;

	struct marker
	{
		UInt32    arrayIndex;    // 00
		UInt32    handle;    // 04

		bool operator==(const UInt32 a_key) const { return arrayIndex == a_key; }
		static inline UInt32 GetHash(UInt32 * key)
		{
			UInt32 hash;
			CalculateCRC32_32(&hash, *key, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\thandle: %08X", handle);
			_MESSAGE("\t\tarrayIndex: %08X", arrayIndex);
		}
	};
	tHashSet<marker, UInt32>		markers;
	tArray<PipboyObject*>			unkarr1;
	tArray<UInt32>					unkarr2;	// array of handles?
	struct unkstr2
	{
		UInt32				handle;	// 00
		UInt32				pad04;	// 04
		PipboyObject*		obj;    // 08

		void Dump(void)
		{
			_MESSAGE("\t\thandle: %08X", handle);
			tracePipboyValue(obj);
		}
	};
	tHashSet<unkstr2, UInt32>			unkhs1;
	tHashSet<unkstr2, UInt32>			unkhs2;	// looks like just copy of unkhs1
	NiPoint3						playerPos[2];
	PipboyObject*					unkPos1; // object with fields X (float) Y (float) and Rotation (float)
	PipboyObject*					unkPos2; // object with fields X (float) Y (float) and Rotation (float)
	PipboyObject*					unkMarker1; // probably custom marker. object with fields X (float) Y (float) Visible (bool) and Height (uchar)
	PipboyObject*					unkMarker2; // probably custom marker. object with fields X (float) Y (float) Visible (bool) and Height (uchar)
	PipboyObject*					unkMarker3; // probably PA marker. object with fields X (float) Y (float) Visible (bool) and Height (uchar)
	PipboyObject*					unkMarker4; // probably PA marker. object with fields X (float) Y (float) Visible (bool) and Height (uchar)
	PipboyObject*					unkExtents1; // object with fields SWX(float) NEY(float) NWX(float) NEX(float) NWY(float) SWY(float)
	PipboyObject*					unkExtents2; // object with fields SWX(float) NEY(float) NWX(float) NEX(float) NWY(float) SWY(float)

};
STATIC_ASSERT(sizeof(PipboyMapData) == 0x238);

class PipboyRadioData : public PipboyDataGroup
{
public:
	BSTEventSink<RadioManager::PipboyFrequencyDetectionEvent>		es1;
	BSTEventSink<RadioManager::PipboyRadioTuningEvent>				es2;
	PipboyArray*													radioDataObject;	// always same as 0x90
	/*
	array of radiostations objects with fields:
	active (bool)
	frequency (float)
	text (string)
	inRange (bool)
	*/
};
STATIC_ASSERT(sizeof(PipboyRadioData) == 0xB0);

class PipboyPlayerInfoData : public PipboyDataGroup
{
public:
	BSTEventSink<ActorValueEvents::ActorValueChangedEvent>			es1;
	BSTEventSink<BGSInventoryListEvent::Event>						es2;
	BSTEventSink<ActorEquipManagerEvent::Event>						es3;
	BSTEventSink<LevelIncrease::Event>								es4;
	BSTEventSink<PerkPointIncreaseEvent>							es5;
	BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>			es6;
	BSTEventSink<HourPassed::Event>									es7;
	BSTEventSink<SPECIALMenuEvent::NameChangedEvent>				es8;
	BSTEventSink<PlayerUpdateEvent>									es9;
	BSTEventSink<BGSInventoryItemEvent::Event>						es10;
	BSTEventSink<PlayerActiveEffectChanged::Event>					es11;
	BSTEventSink<PlayerCharacterQuestEvent::Event>					es12;
	BSTEventSink<PlayerDifficultySettingChanged::Event>				es13;
	PipboyObject*													playerInfoDataObject;	// always same as 0x90
	/*
	object with fields:
	CurrWeight (float)
	DateYear (uint)
	PerkPoints (uint)
	Caps (sint)
	MaxWeight (float)
	CurrHP
	MaxAP
	CurrAP
	MaxHP
	SlotResists (array of arrays of objects) 
			Value (float)
			type (uint)
	CurrentHPGain (float)
	TotalDamages (array of objects)
		Value (float)
		type (uint)
	TotalResists (array of objects)
		Value (float)
		type (uint)
	TimeHour (float)
	DateDay
	DateMonth (uint)
	XPLevel (sint)
	PlayerName (string)
	XPProgressPct (float)
	*/

};
STATIC_ASSERT(sizeof(PipboyPlayerInfoData) == 0x108);

class PipboyStatusData : public PipboyDataGroup
{
public:
	BSTEventSink<PlayerLifeStateChanged::Event>			es1;
	BSTEventSink<PlayerInDialogueChanged::Event>		es2;
	BSTEventSink<MenuOpenCloseEvent>					es3;
	BSTEventSink<BGSInventoryListEvent::Event>			es4;
	BSTEventSink<LoadingStatusChanged::Event>			es5;
	BSTEventSink<VATSEvents::ModeChange>				es6;
	BSTEventSink<UserEventEnabledEvent>					es7;
	PipboyObject*										statusDataObject;	// always same as 0x90
	/*
	object with fields:
	IsInAnimation (bool)
	IsPipboyNotEquipped (bool)
	IsInVats (bool)
	IsPlayerPipboyLocked (bool)
	MinigameFormIds (array of uints)
	IsInAutoVanity (bool)
	IsPlayerMovementLocked (bool)
	EffectColor (array of float RGB)
	IsDataUnavailable (bool)
	IsMenuOpen (bool)
	IsPlayerDead (bool)
	IsInVatsPlayback (bool)
	IsPlayerInDialogue (bool)
	IsLoading (bool)
	*/
	PipboyArray*										unkD8;	// probably effectColor
};
STATIC_ASSERT(sizeof(PipboyStatusData) == 0xE0);

struct PipboyDataManager {
	UInt64								unk00;								// 00
	PipboyObject						mainObject;							// 08
	PipboyStatsData						statsData;							// A0
	PipboySpecialData					specialData;						// 1D8
	PipboyPerksData						perksData;							// 280
	PipboyInventoryData					inventoryData;						// 358
	PipboyQuestData						questData;							// 4F0
	PipboyWorkshopData					workshopData;						// 5D8
	PipboyLogData						logData;							// 718
	PipboyMapData						mapData;							// 7F0
	PipboyRadioData						radioData;							// A28
	PipboyPlayerInfoData				playerInfoData;						// AD8
	PipboyStatusData					statusData;							// BE0
	PipboyStatsData	*					statsDataPointer;					// CC0
	PipboySpecialData *					specialDataPointer;					// CC8
	PipboyPerksData	*					perksDataPointer;					// CD0
	PipboyInventoryData *				inventoryDataPointer;				// CD8
	PipboyQuestData	*					questDataPointer;					// CE0
	PipboyWorkshopData *				workshopDataPointer;				// CE8
	PipboyLogData *						logDataPointer;						// CF0
	PipboyMapData *						mapDataPointer;						// CF8
	PipboyRadioData	*					radioDataPointer;					// D00
	PipboyPlayerInfoData *				playerInfoDataPointer;				// D08
	PipboyStatusData *					statusDataPointer;					// D10
	tHashSet<uintptr_t>					hsD18;								// D18
};
STATIC_ASSERT(sizeof(PipboyDataManager) == 0xD48);

extern RelocPtr <PipboyDataManager*> g_PipboyDataManager;

PipboyObject* CreatePipboyObject(PipboyValue* parent);
PipboyArray* CreatePipboyArray(PipboyValue* parent);

void SharedClasses_PipboyInit();