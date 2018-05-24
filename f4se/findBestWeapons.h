#pragma once

#include "Shared.h"


#define TeammateDontUseAmmoKeywordFormID 0x23F1CA
#define CurrentCompanionFactionFormID 0x23C01

#define CompanionAmmoFlamerFuelFormID 0x2491A7
#define CompanionAmmo45CaliberFormID 0x245D6B
#define CompanionAmmo10mmFormID 0x245D6A
#define CompanionAmmoFusionCellFormID 0x245D69
#define CompanionAmmoShotgunShellFormID 0x245D68
#define CompanionAmmo308CaliberFormID 0x245D53

typedef bool(*_IKeywordFormBase_HasKeyword)(IKeywordFormBase* keywordFormBase, BGSKeyword* keyword, UInt32 unk3); // unk3 = 0 in HasKeyword condition function
typedef bool(*_Actor_GetInFaction)(Actor* actor, TESFaction* faction);


bool HasKeyword(TESForm* form, BGSKeyword* keyword);
bool InFaction(Actor* actor, TESFaction* faction);

namespace FindBestWeapons
{
	enum EquippedWeaponType {
		kType_unarmed,
		kType_melee,
		kType_ranged
	};

	extern UInt32	equippedWeaptype;

	extern WeapForUI	rangedWeapForUI;
	extern WeapForUI	meleeWeapForUI;

	void FillConsts();
	inline float CheckProjectileExplosiveDamage(BGSProjectile * pj);
	bool IsCurrentCompanion(Actor * actor);
	bool IsCompanionUseAmmo(Actor * actor);
	bool IsCompanionAmmo(TESAmmo * ammo);
	TESObjectREFR * GetCommandTarget();
	UInt32 GetTotalDamage(TESObjectWEAP::InstanceData * id);
	void FindBestWeapons(TESObjectREFR * ref, bool checkammo);
	void EquipWeapon(WeapToEquip weap, Actor * actor);
	void UnEquipWeapon(WeapToEquip weap, Actor * actor);
	void UnEquipCurrentWeapon(Actor * actor);
}