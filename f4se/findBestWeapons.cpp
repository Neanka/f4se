#include "findBestWeapons.h"


bool HasKeyword(TESForm* form, BGSKeyword* keyword) {
	IKeywordFormBase* keywordFormBase = DYNAMIC_CAST(form, TESForm, IKeywordFormBase);
	if (keywordFormBase) {
		auto HasKeyword_Internal = Utils::GetVirtualFunction<_IKeywordFormBase_HasKeyword>(keywordFormBase, 1);
		if (HasKeyword_Internal(keywordFormBase, keyword, 0)) {
			return true;
		}
	}
	return false;
}

bool InFaction(Actor* actor, TESFaction* faction) {
	auto Actor_GetInFaction = Utils::GetVirtualFunction<_Actor_GetInFaction>(actor, 266);
	if (Actor_GetInFaction(actor, faction)) {
		return true;
	}
	return false;
}

namespace FindBestWeapons
{
	BGSKeyword * TeammateDontUseAmmoKeyword;
	TESFaction * CurrentCompanionFaction;

	TESAmmo * CompanionAmmoFlamerFuel;
	TESAmmo * CompanionAmmo45Caliber;
	TESAmmo * CompanionAmmo10mm;
	TESAmmo * CompanionAmmoFusionCell;
	TESAmmo * CompanionAmmoShotgunShell;
	TESAmmo * CompanionAmmo308Caliber;

	UInt32	equippedWeaptype = kType_unarmed;

	WeapForUI	rangedWeapForUI = { {}, "", 0.0, false };
	WeapForUI	meleeWeapForUI = { {}, "", 0.0, false };

	void FillConsts()
	{
		TeammateDontUseAmmoKeyword = DYNAMIC_CAST(LookupFormByID(TeammateDontUseAmmoKeywordFormID), TESForm, BGSKeyword);
		CurrentCompanionFaction = DYNAMIC_CAST(LookupFormByID(CurrentCompanionFactionFormID), TESForm, TESFaction);
		CompanionAmmoFlamerFuel = DYNAMIC_CAST(LookupFormByID(CompanionAmmoFlamerFuelFormID), TESForm, TESAmmo);
		CompanionAmmo45Caliber = DYNAMIC_CAST(LookupFormByID(CompanionAmmo45CaliberFormID), TESForm, TESAmmo);
		CompanionAmmo10mm = DYNAMIC_CAST(LookupFormByID(CompanionAmmo10mmFormID), TESForm, TESAmmo);
		CompanionAmmoFusionCell = DYNAMIC_CAST(LookupFormByID(CompanionAmmoFusionCellFormID), TESForm, TESAmmo);
		CompanionAmmoShotgunShell = DYNAMIC_CAST(LookupFormByID(CompanionAmmoShotgunShellFormID), TESForm, TESAmmo);
		CompanionAmmo308Caliber = DYNAMIC_CAST(LookupFormByID(CompanionAmmo308CaliberFormID), TESForm, TESAmmo);
	}

	inline float CheckProjectileExplosiveDamage(BGSProjectile* pj)
	{
		//DumpClass(pj, 0x188 / 8);
		BGSExplosion* exp = Utils::GetOffset<BGSExplosion*>(pj, 0xE8);
		if (exp)
		{
			//DumpClass(exp, 0x148 / 8);
			_DMESSAGE("explosive damage %f", Utils::GetOffset<float>(exp, 0x120));
			return Utils::GetOffset<float>(exp, 0x120);
		}
		return 0.0;
	}

	inline float CalcMeleeDPS_regular(TESObjectWEAP::InstanceData* id)
	{
		UInt32 damage = GetTotalDamage(id);
		float speed = id->speed;
		float attackSeconds = id->unkC0;

		float dps = damage / attackSeconds;
		return dps;
	}

	inline float CalcMeleeDPS_auto(TESObjectWEAP::InstanceData* id)
	{
		UInt32 damage = GetTotalDamage(id);
		float speed = id->speed;
		float attackSeconds = id->unkC0;
		float singleAttackTime = attackSeconds / 5;

		float dps = damage / singleAttackTime * speed;
		return dps;
	}

	inline UInt32 GetTotalDamage(TESObjectWEAP::InstanceData* id)
	{
		UInt32 damage = id->baseDamage;
		if (id->damageTypes)
		{
			for (size_t i = 0; i < (*(id->damageTypes)).count; i++)
			{
				damage += (*(id->damageTypes))[i].value;
			}
		}

		if (id->firingData->projectileOverride)
		{
			damage += CheckProjectileExplosiveDamage(id->firingData->projectileOverride);
		}
		else if (id->ammo)
		{
			damage += CheckProjectileExplosiveDamage(Utils::GetOffset<BGSProjectile*>(id->ammo, 0x160));
		}

		_DMESSAGE("total damage = %i", damage);
		return damage;
	}


	inline float CalcRangedDPS_regular(TESObjectWEAP::InstanceData* id)
	{
		UInt16 capacity = id->ammoCapacity;
		UInt32 damage = GetTotalDamage(id);
		float speed = id->speed;
		float attackDelay = id->attackDelay;

		float attackSeconds = id->unkC0;
		float reloadSeconds = id->firingData->unk18;
		float reloadSpeed = id->reloadSpeed;
		UInt8 numProjectiles = id->firingData->numProjectiles;

		if (capacity == 0)
		{
			_DMESSAGE("Never Ending weapon");
			capacity = 1;
			reloadSeconds = 0;
		}

		UInt32 ddfc = capacity * damage;
		float ttfc = capacity * attackDelay / speed + reloadSeconds / reloadSpeed;

		float dps = ddfc / ttfc * numProjectiles;
		return dps;
	}

	inline float CalcRangedDPS_bolt(TESObjectWEAP::InstanceData* id)
	{
		UInt16 capacity = id->ammoCapacity;
		UInt32 damage = GetTotalDamage(id);
		float attackSeconds = id->unkC0;
		float boltSeconds = id->firingData->unk1C;
		float speed = id->speed;

		float reloadSeconds = id->firingData->unk18;
		float reloadSpeed = id->reloadSpeed;
		UInt8 numProjectiles = id->firingData->numProjectiles;

		UInt32 ddfc = capacity * damage;
		float ttfc = (capacity - 1) * boltSeconds / speed + reloadSeconds / reloadSpeed;

		float dps = ddfc / ttfc * numProjectiles;
		return dps;
	}

	inline float CalcRangedDPS_auto(TESObjectWEAP::InstanceData* id)
	{
		UInt16 capacity = id->ammoCapacity;
		UInt32 damage = GetTotalDamage(id);
		float attackSeconds = id->unkC0;
		float singleAttackTime = attackSeconds / 20;
		float speed = id->speed;

		float reloadSeconds = id->firingData->unk18;
		float reloadSpeed = id->reloadSpeed;
		UInt8 numProjectiles = id->firingData->numProjectiles;

		if (capacity == 0)
		{
			_DMESSAGE("Never Ending weapon");
			capacity = 1;
			reloadSeconds = 0;
		}

		UInt32 ddfc = capacity * damage;
		float ttfc = capacity * singleAttackTime / speed + reloadSeconds / reloadSpeed;
		if (id->flags & kWeaponFlagsEx_ChargingAttack)
		{
			ttfc += 1;
		}

		float dps = ddfc / ttfc * numProjectiles;
		return dps;
	}

	inline float CalcRangedDPS_chargingReload(TESObjectWEAP::InstanceData* id)
	{
		UInt16 capacity = id->ammoCapacity;
		UInt32 damage = GetTotalDamage(id);
		float attackSeconds = id->unkC0;
		float speed = id->speed;

		float reloadSeconds = id->firingData->unk18;
		float reloadSpeed = id->reloadSpeed;
		UInt8 numProjectiles = id->firingData->numProjectiles;

		UInt32 ddfc = capacity * damage;
		float ttfc = attackSeconds / speed + capacity * reloadSeconds / reloadSpeed;

		float dps = ddfc / ttfc * numProjectiles;
		return dps;
	}


	inline bool IsCurrentCompanion(Actor* actor)
	{
		return InFaction(actor, CurrentCompanionFaction);
	}

	inline bool IsCompanionUseAmmo(Actor* actor)
	{
		return HasKeyword(actor, TeammateDontUseAmmoKeyword);
	}

	inline bool IsCompanionAmmo(TESAmmo* ammo)
	{

	}

	TESObjectREFR* GetCommandTarget()
	{
		TESObjectREFR* ref = NULL;

		UInt32 * handle = commandTargetCompanionRef;

		if (*handle != 0 && *handle != (*g_invalidRefHandle)) {
			LookupREFRByHandle(handle, &ref);
		}

		return ref;
	};



	void FindBestWeapons(TESObjectREFR* ref, bool checkammo)
	{
		equippedWeaptype = kType_unarmed;
		rangedWeapForUI.weapToEquip.instance = nullptr;
		rangedWeapForUI.weapToEquip.weap = nullptr;
		rangedWeapForUI.name = "";
		rangedWeapForUI.dps = 0.0;
		rangedWeapForUI.equipped = false;
		meleeWeapForUI.weapToEquip.instance = nullptr;
		meleeWeapForUI.weapToEquip.weap = nullptr;
		meleeWeapForUI.name = "";
		meleeWeapForUI.dps = 0.0;
		meleeWeapForUI.equipped = false;

		float bestRangedDps = 0.0;
		float currentRangedDps = 0.0;
		const char* currentWeapName = "";
		float bestMeleeDps = 0.0;
		float currentMeleeDps = 0.0;

		if (!ref)
			return;
		_DMESSAGE("Starting FindBestWeapons() for %s", ref->baseForm->GetFullName());
		ref->inventoryList->inventoryLock.Lock();

		for (size_t i = 0; i < ref->inventoryList->items.count; i++)
		{
			TESForm* form = ref->inventoryList->items[i].form;
			BGSInventoryItem::Stack* stack = ref->inventoryList->items[i].stack;
			if (form->formType == kFormType_WEAP)
			{
				_DMESSAGE("WEAP found --------------------------------------------------------------------");
				TESObjectWEAP* weap = (TESObjectWEAP*)form;

				stack->Visit([&](BGSInventoryItem::Stack * stackx)
				{
					_DMESSAGE("stack count %i flags %i equipped %s", stackx->count, stackx->flags, (stackx->flags & 7) ? "true" : "false");
					ExtraDataList * stackDataList = stackx->extraData;
					TESObjectWEAP::InstanceData* weapData;
					currentWeapName = weap->GetFullName();
					weapData = &weap->weapData;
					if (stackDataList) {
						ExtraInstanceData * eid = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
						ExtraTextDisplayData * etdd = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_TextDisplayData), BSExtraData, ExtraTextDisplayData);
						if (etdd)
						{
							currentWeapName = etdd->name.c_str();
						}
						if (eid)
						{
							weapData = (TESObjectWEAP::InstanceData*)eid->instanceData;
						}
					}
					_DMESSAGE("weap full name: %s", currentWeapName);
					_DMESSAGE("base damage %i", weapData->baseDamage);
					_DMESSAGE("capacity %i", weapData->ammoCapacity);
					switch (weapData->unk137)
					{
					case kWeaponAnimationType_Hand_To_Hand_Melee:
					case kWeaponAnimationType_One_Hand_Sword:
					case kWeaponAnimationType_Two_Hand_Sword:

						if (weapData->flags & kWeaponFlagsEx_Automatic)
						{
							_DMESSAGE("automatic melee weapon");
							currentMeleeDps = CalcMeleeDPS_auto(weapData);
						}
						else
						{
							_DMESSAGE("regular melee weapon");
							currentMeleeDps = CalcMeleeDPS_regular(weapData);
						}
						_DMESSAGE("current DPS - %f", currentMeleeDps);
						if (currentMeleeDps > bestMeleeDps)
						{
							bestMeleeDps = currentMeleeDps;
							meleeWeapForUI.weapToEquip.instance = weapData;
							meleeWeapForUI.weapToEquip.weap = weap;
							meleeWeapForUI.name = currentWeapName;
							meleeWeapForUI.dps = currentMeleeDps;
							if (stackx->flags & 7)
							{
								meleeWeapForUI.equipped = true;
								equippedWeaptype = kType_melee;
							}
						}
						break;
					case kWeaponAnimationType_Gun:
						if (weapData->flags & kWeaponFlagsEx_BoltAction)
						{
							_DMESSAGE("bolt action gun");
							currentRangedDps = CalcRangedDPS_bolt(weapData);
						}
						else if (weapData->flags & kWeaponFlagsEx_Automatic)
						{
							_DMESSAGE("automatic gun");
							currentRangedDps = CalcRangedDPS_auto(weapData);
						}
						else if (weapData->flags & kWeaponFlagsEx_ChargingReload)
						{
							_DMESSAGE("charging reload gun");
							currentRangedDps = CalcRangedDPS_chargingReload(weapData);
						}
						else
						{
							_DMESSAGE("regular gun");
							currentRangedDps = CalcRangedDPS_regular(weapData);
						}
						_DMESSAGE("current DPS - %f", currentRangedDps);
						if (currentRangedDps > bestRangedDps)
						{
							bestRangedDps = currentRangedDps;
							rangedWeapForUI.weapToEquip.instance = weapData;
							rangedWeapForUI.weapToEquip.weap = weap;
							rangedWeapForUI.name = currentWeapName;
							rangedWeapForUI.dps = currentRangedDps;
							if (stackx->flags & 7)
							{
								rangedWeapForUI.equipped = true;
								equippedWeaptype = kType_ranged;
							}
						}
						
						break;
					case kWeaponAnimationType_Grenade:

						break;
					case WeaponAnimationType::kWeaponAnimationType_Mine:

						break;
					default:
						break;
					}

					//DumpClass(weapData, 0x138 / 8);
					//DumpClass(weapData->firingData, 6);
					return true;
				});
			}
		}
		ref->inventoryList->inventoryLock.Release();
		_DMESSAGE("best ranged weapon is %s with %f DPS", rangedWeapForUI.name, rangedWeapForUI.dps);
		_DMESSAGE("best melee weapon is %s with %f DPS", meleeWeapForUI.name, meleeWeapForUI.dps);
	}

	void EquipWeapon(WeapToEquip weap, Actor* actor)
	{
		EquipItem_int(*unk_itemManager, actor, &weap, 0, 1, nullptr, 1, false, 1, 0, false);
	}

	void UnEquipWeapon(WeapToEquip weap, Actor* actor)
	{
		UnEquipItem_int(*unk_itemManager, actor, &weap, 1, nullptr, -1, 1, true, 1, 0, nullptr);
	}

	void UnEquipCurrentWeapon(Actor* actor)
	{
		WeapToEquip weapforequip = {};
		actor->inventoryList->inventoryLock.Lock();

		for (size_t i = 0; i < actor->inventoryList->items.count; i++)
		{
			TESForm* form = actor->inventoryList->items[i].form;
			BGSInventoryItem::Stack* stack = actor->inventoryList->items[i].stack;
			if (form->formType == kFormType_WEAP)
			{
				TESObjectWEAP* weap = (TESObjectWEAP*)form;

				stack->Visit([&](BGSInventoryItem::Stack * stackx)
				{
					if (stackx->flags & 7)
					{
						_DMESSAGE("found equipped weapon. trying to unequip");
						weapforequip.weap = weap;
						ExtraDataList * stackDataList = stackx->extraData;
						if (stackDataList) {
							ExtraInstanceData * eid = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
							if (eid)
							{
								weapforequip.instance = (TESObjectWEAP::InstanceData*)eid->instanceData;
							}
							else
							{
								weapforequip.instance = nullptr;
							}
						}
						UnEquipItem_int(*unk_itemManager, actor, &weapforequip, 1, nullptr, -1, 1, true, 1, 0, nullptr);
					}
					return true;
				});
			}
		}
		actor->inventoryList->inventoryLock.Release();
	}
}