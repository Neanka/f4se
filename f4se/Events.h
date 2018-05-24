#pragma once

#include "Shared.h"

enum HitEventFlags {
	kFlag_Unk0 = (1 << 0),     // Either Unk0 or Unk1 - blocked
	kFlag_Unk1 = (1 << 1),
	kFlag_CriticalHit = (1 << 3),
	kFlag_SneakAttack = (1 << 11),
	kFlag_Unk15 = (1 << 15),    // Either Unk15 or Unk16 - bash
	kFlag_Unk16 = (1 << 16),
	kFlag_PowerAttack = (1 << 17),
};
struct TESHitEvent_x
{
	NiPoint3        position;                   // 00
	UInt32          unk0C[(0x40 - 0x0C) / 4];       // 0C
	UInt32          attackerHandle;             // 40
	UInt32          targetHandle;               // 44
	UInt64          unk48;                      // 48
	void*           attackData;                 // 50 - BGSAttackData*
	TESForm*        source;                     // 58 - e.g. TESObjectWEAP*
	void*           sourceInstanceData;         // 60
	UInt64          unk68[(0x80 - 0x68) / 8];       // 68
	TESAmmo*        ammo;                       // 80
	UInt64          unk88;                      // 88
	float           effectiveDamage;            // 90 - effectiveDamage = baseDamage + damage bonus (body part multiplier)
	float           incomingDamage;             // 94
	float           baseDamage;                 // 98 - baseDamage = incomingDamage - negatedDamage
	float           unk9C;                      // 9C
	float           unkA0;                      // A0
	float           negatedDamage;              // A4
	UInt64          unkA8;                      // A8
	float           attackDamageMultiplier;     // B0 - Sneak attack muliplier
	UInt32          unkB4[(0xC4 - 0xB4) / 4];       // B4
	UInt32          flags;                      // C4
	UInt64          unkC8[(0xE0 - 0xC8) / 8];       // C8
	TESObjectREFR*  target;                     // E0 - If null, use handle
	TESObjectREFR*  attacker;                   // E8 - If null, use handle
	UInt64          unkF0;                      // F0
	UInt32          sourceFormID;               // F8 - May be null
	UInt32          projectileFormID;           // FC - May be null
	bool            unk100;                     // 100
	char            pad101[7];                  // 101
};
STATIC_ASSERT(offsetof(TESHitEvent_x, unk100) == 0x100);

DECLARE_EVENT_DISPATCHER(TESHitEvent_x, 0x004444D0);

struct HUDEnemyHealthDisplayEvent
{
	BSFixedString   name;               // 00
	float           healthPercent;      // 08
	float           shadedPercent;      // 0C
	bool            isEnemy;            // 10
	bool            showLegendaryIcon;  // 11
	bool            showSkullIcon;      // 12
	char            unk13;              // 13
	UInt32          unk14;              // 14 - in VATS
	bool            show;               // 18
	char            pad19[7];           // 19
};
STATIC_ASSERT(offsetof(HUDEnemyHealthDisplayEvent, pad19) == 0x19);

struct TESEquipEvent
{
	TESObjectREFR*	ref;		// 00
	UInt32			FormID;		// 08
	UINT32			unk0C;		// 0C
	char            pad10[4];	// 10
	bool			equip;		// 14
	//...
};

//1.10.26 0x004426D0
//1.10.40 0x004426F0
DECLARE_EVENT_DISPATCHER(TESEquipEvent, 0x004426F0);



struct WorkshopNPCTransferEvent
{
	TESObjectREFR*	NPCref;			// 00
	BGSLocation*	targetloc;		// 08
	BGSKeyword*		keyword;		// 10 WorkshopAssignCaravan / WorkshopAssignHome
};

DECLARE_EVENT_DISPATCHER(WorkshopNPCTransferEvent, 0x00444430);



struct HolotapePlayEvent
{

};

DECLARE_EVENT_DISPATCHER(HolotapePlayEvent, 0x00441A50);

struct BGSOnPlayerFireWeaponEvent
{

};

DECLARE_EVENT_DISPATCHER(BGSOnPlayerFireWeaponEvent, 0x004414B0);



struct TESContainerChangedEvent
{
	UInt32          sourceContainerFormID;              // 00
	UInt32          targetContainerFormID;				// 04
	UInt32          itemFormID;							// 08
	UInt32          count;								// 0C
	UInt64			unk10;								// 10
	void*			unk18;								// 18
	//... etc
};

//1.10.26 0x00442310
//1.10.40 0x00442330
DECLARE_EVENT_DISPATCHER(TESContainerChangedEvent, 0x00442330);

struct PlayerWeaponReloadEvent {


};

struct AnimationDataSetupEvent {


};

struct AnimationDataCleanupEvent {


};