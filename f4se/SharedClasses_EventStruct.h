#pragma once

#include "f4seee\f4seeeEvents.h"

class NiNode;
struct ViewCasterUpdateEvent
{
	UInt32            handle;                    // 00
	UInt32            pad08;                    // 04
	UInt64            unk0C;                    // 08 - fade node
	NiNode*            niNode;                    // 10
	UInt64            unk18[(0x40 - 0x18) / 8];    // 18
	TESObjectREFR*    refr;                    // 40
											   //...
};
STATIC_ASSERT(offsetof(ViewCasterUpdateEvent, refr) == 0x40);

class TESObjectWEAP;
struct PlayerAmmoCountEvent
{
	UInt32            ammoCount;        // 00
	UInt32            totalAmmoCount;    // 04
	UInt64            unk08;            // 08
	TESObjectWEAP*    weapon;            // 10
										 //...
};
STATIC_ASSERT(offsetof(PlayerAmmoCountEvent, weapon) == 0x10);

struct PlayerWeaponReloadEvent
{

};

struct PlayerSetWeaponStateEvent
{

};

struct PlayerCrosshairModeEvent
{
	UInt32				mode;			// 00 
};

struct TravelMarkerStateChange
{
	struct Event
	{

	};
};

struct BGSActorCellEvent
{

};

struct TESQuestEvent
{
	struct Event
	{

	};
};

struct PlayerCharacterQuestEvent
{
	struct Event
	{

	};
};

struct CustomMarkerUpdate
{
	struct Event
	{

	};
};

struct LocationMarkerArrayUpdate
{
	struct Event
	{

	};
};

struct LocalMapCameraUpdate
{
	struct Event
	{

	};
};

struct TESLocationClearedEvent
{

};

struct ActorValueEvents
{
	struct ActorValueChangedEvent
	{

	};
};
	
struct RadioManager
{
	struct PipboyFrequencyDetectionEvent
	{

	};
	struct PipboyRadioTuningEvent
	{

	};
};

struct ActorEquipManagerEvent
{
	struct Event
	{

	};
};


struct PerkPointIncreaseEvent
{

};

struct PerkValueEvents
{
	struct PerkEntryUpdatedEvent
	{

	};
	struct PerkValueChangedEvent
	{

	};
};

struct HolotapeStateChanged
{
	struct Event
	{

	};
};

struct HourPassed
{
	struct Event
	{

	};
};

struct SPECIALMenuEvent
{
	struct NameChangedEvent
	{

	};
};

struct PlayerUpdateEvent
{

};

struct BGSInventoryItemEvent
{
	// 8
	struct Event
	{
		UInt32		ownerRefHandle;
		UInt32		itemHandleID;
	};
};

struct FavoriteMgr_Events
{
	// 10
	struct ComponentFavoriteEvent
	{
		BGSComponent*		component;
		UInt8				taggedForSearch;
	};
};

struct PlayerActiveEffectChanged
{
	struct Event
	{

	};
};

struct PlayerDifficultySettingChanged
{
	struct Event
	{
		UInt32	from;
		UInt32	to;
	};
};

struct PlayerLifeStateChanged
{
	struct Event
	{

	};
};

struct PlayerInDialogueChanged
{
	struct Event
	{

	};
};

struct LoadingStatusChanged
{
	struct Event
	{

	};
};

struct VATSEvents
{
	struct ModeChange
	{

	};
};
