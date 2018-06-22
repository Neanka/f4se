#pragma once

#define CURRENT_RUNTIME_VERSION RUNTIME_VERSION_1_10_89
#define SUPPORTED_RUNTIME_VERSION_STRING "1.10.89"

#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"
#include "f4se/GameData.h"
#include <shlobj.h>
#include <string>

#include "f4se/GameForms.h"
#include "f4se/GameReferences.h"

#include "RVA.h"

#include "GameMenus.h"
#include "f4seee\f4seeeEvents.h"
#include "f4se\GameRTTI.h"

template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
	static const char* digits = "0123456789ABCDEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i<hex_len; ++i, j -= 4)
		rc[i] = digits[(w >> j) & 0x0f];
	return rc;
}

//#include "Globals.h"
extern IDebugLog	gLog;

struct PRKFIsTaggedMessage
{
	enum
	{
		kMessage_PRKFIsTagged = 0x03000001
	};

	UInt32			formid			= 0;
	bool			tagged			= false;
};

struct PRKFReadyMessage
{
	enum
	{
		kMessage_PRKFReady = 0x03000003
	};
};

struct PRKFAddDataMessage
{
	enum
	{
		kMessage_PRKFAddData = 0x03000002
	};

	std::string		ININame					= "";
	UInt32			INIVersion				= 0;
	int				disableVanillaPerks		= 0;
	UInt32			overrideMaxSkillsValue	= 0;
	BGSListForm*	PerksList				= nullptr;
	BGSListForm*	SkillsList				= nullptr;
	UInt8			PPPerLevel				= 0;
	UInt8			SPPerLevel				= 0;
};

SInt8 CheckModDropClientService();

#include "f4se/GameSettings.h"
void CheckArchiveInvalidation(std::string mName);

namespace Utils {
	bool ReadMemory(uintptr_t addr, void* data, size_t len);

	template <typename T>
	T GetVirtualFunction(void* baseObject, int vtblIndex) {
		uintptr_t* vtbl = reinterpret_cast<uintptr_t**>(baseObject)[0];
		return reinterpret_cast<T>(vtbl[vtblIndex]);
	}

	template <typename T>
	T GetOffset(const void* baseObject, int offset) {
		return *reinterpret_cast<T*>((uintptr_t)baseObject + offset);
	}

	template<typename T>
	T* GetOffsetPtr(const void * baseObject, int offset)
	{
		return reinterpret_cast<T*>((uintptr_t)baseObject + offset);
	}

	template <typename T>
	T Hook(T hook, uintptr_t hookTarget, int offset, int instructionLength) {
		SInt32 rel32 = 0;
		ReadMemory(hookTarget + offset, &rel32, sizeof(UInt32));
		g_branchTrampoline.Write5Call(hookTarget, (uintptr_t)hook);
		return reinterpret_cast<T>(hookTarget + instructionLength + rel32); // return original address
	}
}


std::string _GetConfigOptionString(std::string file, const char * section, const char * key);

UInt32 _GetConfigOptionInt(std::string file, const char * section, const char * key);

std::string PBT_GetConfigOptionString(std::string file, const char * section, std::string key);

UInt32 PBT_GetConfigOptionInt(std::string file, const char * section, const char * key);

// reg2k
// 70
template <typename T>
class BSTEventSource
{
public:
	virtual ~BSTEventSource();

	// void ** _vtbl;    // 00
	UInt64                    unk08;                // 08
	BSTEventDispatcher<T>    eventDispatcher;    // 10
};
//STATIC_ASSERT(sizeof(BSTEventSource<void*>) == 0x70);
/*
class BSTGlobalEvent
{
public:
	virtual ~BSTGlobalEvent();

	// void ** _vtbl;    // 00
	UInt64    unk08;                                    // 08
	UInt64    unk10;                                    // 10
	tArray<BSTEventSource<void*>*> eventSources;    // 18

													//...
};*/

// r2k
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

typedef void(*_ExecuteCommand)(const char* str);
extern RVA <_ExecuteCommand> ExecuteCommand;
typedef UInt8(*_HasPerk)(Actor * actor, BGSPerk * perk);
extern RVA <_HasPerk> HasPerk;
typedef void(*_AddPerk)(Actor * actor, BGSPerk * perk, UInt8 rank);
extern RVA <_AddPerk> AddPerk;
typedef UInt16(*_GetLevel)(Actor * actor);
extern RVA <_GetLevel> GetLevel;
typedef UInt32(*_GetItemCount)(TESObjectREFR * refr, TESForm * form);
extern RVA <_GetItemCount> GetItemCount;
extern RVA <uintptr_t> g_main;
typedef void(*_UI_AddMessage)(void* menuManager, BSFixedString* menuName, unsigned int menuAction);	// 1 = open, 3 = close
extern RVA <_UI_AddMessage> UI_AddMessage;
extern RVA <void*> g_UIManager;
//RVA <BSTGlobalEvent*> g_globalEvents; // added in 1 10 75 into f4se

struct PipboyDataManager;
extern RVA <PipboyDataManager*> g_PipboyDataManager;



typedef void(*_SetPerkPoints_int)(PlayerCharacter * pc, UInt8 count);
extern RVA <_SetPerkPoints_int> SetPerkPoints_int;


typedef void(*_SetPlayerName)(void* unk1, const char* playerName);
extern RVA <_SetPlayerName> SetPlayerName_int;

typedef void(*_PlaySound)(const char* name);	// 0x012BDD10 // 48 83 EC 38 E8 ? ? ? ? 48 85 C0 74 ? 48 89 5C 24 30 
extern RVA <_PlaySound> PlaySound_int;

typedef void(*_PlaySound2)(const char* name);	// 0x012BDD80 // 48 89 5C 24 08 57 48 83 EC 50 48 8B D9 E8 ? ? ? ?
extern RVA <_PlaySound2> PlaySound2_int;

class LevelUpMenu : public GameMenuBase
{
public:
	BSTEventSink<PerkAdded::Event>			eventSink;							// E0
	UInt64									unkE8[(0x180 - 0xE8) / 8];			// E8
	SInt32									unk180;								// 180
};
STATIC_ASSERT(sizeof(LevelUpMenu) == 0x188);

typedef UInt32(*_LevelupMenuProcessMessage)(LevelUpMenu * menu, UIMessage * message); // 0x0B38360 // 48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B F1 8B 4A 10 
extern RVA <_LevelupMenuProcessMessage> LevelupMenuProcessMessage;


typedef UInt8(*_LevelupMenuPlayPerkSound)(LevelUpMenu * menu, int formid);
extern RVA <_LevelupMenuPlayPerkSound> LevelupMenuPlayPerkSound;	// 0x0B39750 // 48 89 5C 24 08 57 48 83 EC 30 48 8B F9 8B CA 33 DB E8 ? ? ? ? 48 85 C0 74 ? 80 78 1A 5F 75 ? 48 8B 98 88 00 00 00 48 81 C7 80 01 00 00 

typedef UInt8(*_LevelupMenuStopPerkSound)(SInt32 unk1);		// unk1 is LevelUpMenu+0x180
extern RVA <_LevelupMenuStopPerkSound> LevelupMenuStopPerkSound;	// 0x01AC7B70 // 40 53 48 83 EC 20 8B 19 83 FB FF 74 ? C6 41 05 02

//sexchange internal functions 

//ObScriptCommand_SexChange 
//1.10.40 0x004F73E0
//40 55 53 41 56 48 8B EC 48 81 EC 80 00 00 00 
extern const char* ObScriptCommand_SexChange_sig;

class ScrapHeap;

struct HeadPartsData
{
	ScrapHeap*				scrapHeap;		//00
	tArray<BGSHeadPart*>	headParts;		//08
};

struct TemplateData
{
	ScrapHeap*				scrapHeap;		// 00
	tArray<TESNPC*>			templateNPCs;	// 08
};

typedef void(*_changesex_FillNPCArray)(TESRace * race, SInt64 sex, TemplateData * td);
extern RVA <_changesex_FillNPCArray> changesex_FillNPCArray;
typedef void(*_changesex_CopyDataFromTemplateNPC)(TESNPC* npc, TESNPC* npc_template, bool makeTemplate);
extern RVA <_changesex_CopyDataFromTemplateNPC> changesex_CopyDataFromTemplateNPC;
typedef void(*_changesex_UNKF02)(TESNPC * baseform);
extern RVA <_changesex_UNKF02> changesex_UNKF02;
typedef void(*_changesex_UNKF03)(TESNPC * npc, HeadPartsData * unk1);
extern RVA <_changesex_UNKF03> changesex_UNKF03;
typedef void(*_changesex_UNKF04)(TESNPC * npc, HeadPartsData * unk1);
extern RVA <_changesex_UNKF04> changesex_UNKF04;
typedef void(*_changesex_FreeMemory)(void * var);
extern RVA <_changesex_FreeMemory> changesex_FreeMemory;
typedef void(*_changesex_UNKF06)(TESNPC * baseform);
extern RVA <_changesex_UNKF06> changesex_UNKF06;
typedef void(*_changesex_UNKF07)(TESNPC * baseform, int unk1);
extern RVA <_changesex_UNKF07> changesex_UNKF07;
typedef void(*_changesex_UNKF08)(TESNPC * baseform, int unk1);
extern RVA <_changesex_UNKF08> changesex_UNKF08;



typedef UInt32(*_GetRandomPercent)(UInt32 maxvalue);
extern RVA <_GetRandomPercent> GetRandomPercent;
typedef UInt32(*_GetRandomPercent2)(UInt32 minvalue, UInt32 maxvalue);
extern RVA <_GetRandomPercent2> GetRandomPercent2;

// CW

class MultiActivateMenu : public GameMenuBase
{

};

typedef UInt32(*_MultiActivateMenuProcessMessage)(MultiActivateMenu * menu, UIMessage * message);
extern RVA <_MultiActivateMenuProcessMessage> MultiActivateMenuProcessMessage;

class MultiActivateManager
{
public:
	virtual ~MultiActivateManager();

	// void ** _vtbl;    // 00
	void*		unk08; // 08
	void*		unk10; // 10
	void*		unk18; // 
	void*		unk20; // 
	void*		unk28; // 
	void*		unk30; // 
	void*		unk38; // 
	void*		unk40; // 
	void*		unk48; // 
	void*		unk50; // 
};

extern RVA <MultiActivateManager*> g_multiActivateManager;

extern RVA <UInt32*> commandTargetCompanionRef;

typedef UInt32(*_CompanionListenerUnk03)(void * companionListener, UInt32 optionID);
extern RVA <_CompanionListenerUnk03> CompanionListenerUnk03;

struct WeapToEquip
{
	TESObjectWEAP*						weap;
	TESObjectWEAP::InstanceData*		instance;
};

struct WeapForUI
{
	WeapToEquip		weapToEquip;
	const char*		name;
	float			dps;
	bool			equipped;
};

enum WeaponAnimationType
{
	kWeaponAnimationType_Hand_To_Hand_Melee,
	kWeaponAnimationType_One_Hand_Sword,
	kWeaponAnimationType_One_Hand_Dagger,
	kWeaponAnimationType_One_Hand_Axe,
	kWeaponAnimationType_One_Hand_Mace,
	kWeaponAnimationType_Two_Hand_Sword,
	kWeaponAnimationType_Two_Hand_Axe,
	kWeaponAnimationType_Bow,
	kWeaponAnimationType_Staff,
	kWeaponAnimationType_Gun,
	kWeaponAnimationType_Grenade,
	kWeaponAnimationType_Mine,
	kWeaponAnimationType_Spell,
	kWeaponAnimationType_Shield,
	kWeaponAnimationType_Torch
};

enum WeaponFlagsEx
{
	kWeaponFlagsEx_ChargingReload = 0x0000008,
	kWeaponFlagsEx_ChargingAttack = 0x00000200,
	kWeaponFlagsEx_Automatic = 0x00008000,
	kWeaponFlagsEx_CantDrop = 0x00020000,
	kWeaponFlagsEx_BoltAction = 0x00600000
};

typedef UInt32(*_EquipItem_int)(void* param1, void* param2, void* param3, SInt8 param4, SInt8 param5, void* param6, SInt8 param7, bool forceequip, SInt8 param9, SInt8 param10, bool preventunequip);
extern RVA <_EquipItem_int> EquipItem_int;

typedef UInt8(*_UnEquipItem_int)(void* unkmanager, void* actor, void* unkstruct, SInt8 param4, void* equipslot, SInt8 param6, SInt8 param7, bool abPreventEquip, SInt8 param9, SInt8 param10, void* param11);
// sub_140E1BEF0(qword_145A10618, v7, &v25, 1, v16, -1, 1, a5, 1, 0, 0i64);
extern RVA <_UnEquipItem_int> UnEquipItem_int;


extern RVA <void*> unk_itemManager;



void InitExeAddress();

void InitTIMAddress();

void InitAddresses();

void InitUIManager();

void InitCWAddresses();

void InitSexChangeAddresses();



//#include "f4se\NiNodes.h"
bool changesex(Actor* actor, SInt8 sexToSet = -1, bool customFace = false);

UInt8 GetPerkPoints();

UInt16 GetSkillsPoints();

UInt8 GetPRKFStarted();

void SetPRKFStarted(UInt8 started);

void ModSkillsPoints(UInt16 count);

void ModPerkPoints(SInt8 count);

void MenuOpenClose_int(BSFixedString asMenuName, bool abOpen);

void UI_AddMessage_int(BSFixedString asMenuName, int state);


void pauseGame(bool pause);

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char * dispatcherName);

void logMessage(std::string aString);

void errorMessage(std::string aString);

bool to_bool(std::string const& s);

// UNUSED TRASH

// 1.9.4	: 0DDD360
// 1.10.20	: 0DF5100
// 1.10.26	: 0DF5190
//48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 50 48 63 EA 
/*typedef void(*_ModAV_h)(Actor * actor, UInt32 unk1, ActorValueInfo * actorValueInfo, float value);
RelocAddr <_ModAV_h> ModAV_h(0x0DF5190);
_ModAV_h ModAV_h_Original;// = nullptr;

void ModAV_h_Hook(Actor * actor, UInt32 unk1, ActorValueInfo * actorValueInfo, float value)
{
	ModAV_h_Original(actor, unk1, actorValueInfo, value);
	if (actor == *g_player)
	{
		_MESSAGE("PLAYER VALUE CHANGED %f", value);

	}
	return;
}
*/

// 1.9.4	: 065D950
// 1.10.20	: 065FA60
// 1.10.26	: 065FA50
//48 8B C4 48 81 EC 88 00 00 00 0F 29 70 E8 0F 29 78 D8 44 0F 29 40 C8 F3 44 0F 10 05 10 F3 5F 02 
/*
typedef float (* _CalculateDR)(ActorValueInfo * avif, float damage, float damageResist);
RelocAddr <_CalculateDR> CalculateDR(0x065FA50);
_CalculateDR CalculateDR_Original = nullptr;

float CalculateDR_Hook(ActorValueInfo * avif, float damage, float damageResist){
	float result = CalculateDR_Original(avif, damage, damageResist);
	_MESSAGE(std::to_string(result).c_str());
	return result;
}

struct DamageSettings
{
	float fDamageFactor;
	float fDamageBase;
	float fArmorFactor;
	float fArmorBase;
	float fArmorDmgReductionExp;
	float fMinDamageReduction;
	float fMaxDamageReduction;
};

// 1.9.4	: 065FF80
// 1.10.20	: 0662090
// 1.10.26	: 0662080
//48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 40 32 F6 F6 81 6F 01 00 00 01
typedef bool (* _GetDamageResistSettings)(ActorValueInfo * avif, DamageSettings * ds);
RelocAddr <_GetDamageResistSettings> GetDamageResistSettings(0x0662080);

*/

struct formtoadd
{
	TESForm*				form;		//00
	UInt64				unk08;		//08
	UInt32				count; //10

};
struct additemstruct
{
	ScrapHeap*				scrapHeap;		//00
	formtoadd*				unk08;		//08
};


struct unkstruct
{
	TESForm*				form;			//00
	void*					unk08;			//08
	UInt32					count;			//10
	UInt32					unk1C;			//1C
	UInt32					unk20[16];		//20
};
STATIC_ASSERT(sizeof(unkstruct) == 0x58);

struct unkstruct1
{
	TESObjectREFR*				ref;			//00
	void*					unk08;			//08
};

const RelocAddr<uintptr_t>	type_info_vtbl = 0x30CDC08;

const RelocAddr<uintptr_t>  rdata_begin = 0x2C40000;
const RelocAddr<uintptr_t>  rdata_end = 0x3702000;

const RelocAddr<uintptr_t>  data_begin = 0x3702000;
const RelocAddr<uintptr_t>  data_end = 0x676D000;

const RelocAddr<uintptr_t>  text_begin = 0x1000;
const RelocAddr<uintptr_t>  text_end = 0x2C35000;

TESForm * GetFormFromIdentifier(const std::string & identifier);

/*
typedef int(*_aSETPP)(PlayerCharacter * param1, SInt8 param2);
RelocAddr <_aSETPP> aSETPP(0x0EB8600);
_aSETPP aSETPP_Original;

int aSETPP_Hook(PlayerCharacter * param1, SInt8 param2) {
	_MESSAGE("aSETPP_Hook  !!!!!!!!!!!!!!!!!!!");

	int result = aSETPP_Original(param1, param2);
	return result;
}
*/

#include "GameInput.h"
class QueuedFile;
class FavoritesManagerEx : public BSIntrusiveRefCounted
{
public:
	virtual ~FavoritesManagerEx();
	//UInt64		unk08;		// 08
	BSInputEventUser    inputEventUser;                // 10
	BSTEventSink<void>    inventoryEventSink;            // 20
	BSTEventSink<void>    favoriteChangedEventSink;    // 28

	UInt64    unk30;    // 30
	UInt64    unk38;    // 38
	tArray<BSTEventSink<void>> favoritesSinks;    // 40
	UInt64    unk58;    // 58
	UInt64    unk60;    // 60
	UInt64    unk68;    // 68
	UInt64    unk70;    // 70
	UInt64    unk78;    // 78
	UInt64    unk80;    // 80
	UInt64    unk88;    // 88

	enum Favorites
	{
		kNumFavorites = 12
	};

	TESForm    * favorites[kNumFavorites];    // 90
	QueuedFile * queuedFiles[kNumFavorites]; // F0
	tHashSet<uintptr_t> unk150;    // 150

	struct TaggedEntry
	{
		TESForm * form;    // 00
		UInt32    unk08;    // 08
		UInt32    unk0C;    // 0C

		operator TESForm *() const { return form; }

		static inline UInt32 GetHash(TESForm ** key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)*key, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tForm: %08X", form ? form->formID : 0);
			_MESSAGE("\t\tunk08: %08X", unk08);
		}
	};

	tHashSet<TaggedEntry, TESForm*>		taggedForms;			// 180

	UInt32								kindaFlags;				// 1B0
	UInt32								pad1B4;					// 1B4
	SInt32								unk1B8[kNumFavorites];	// 1B8
};
//STATIC_ASSERT(offsetof(FavoritesManagerEx, taggedForms) == 0x180);

extern RelocPtr <FavoritesManagerEx*> g_favoritesManagerEx;

struct PlayerCrosshairModeEvent
{
	UInt32				mode;			// 00 
};





class PipboyDataGroup
{
public:
	virtual ~PipboyDataGroup();

	BSTEventSource<PipboyValueChangedEvent>			pipboyValueChangedEventSource;		// 08
};
//STATIC_ASSERT(sizeof(PipboyDataGroup) == 0x78);


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


class PipboyMapData
{
public:
	virtual ~PipboyMapData();
	void*			unk00[35];
	//void*			unk148;
	tHashSet<marker, UInt32>		markers;
	void*			unk150[29];
};
STATIC_ASSERT(sizeof(PipboyMapData) == 0x238);

/* added in f4se 0.6.7
// 18 
class PipboyValue
{
public:

	virtual ~PipboyValue();
	virtual    void Unk01();    // Sets unk0C to 0
	virtual void Unk02();    // pure
	virtual void Unk03(void *arg1);
	virtual void Unk04();    // pure

	UInt32    unk08;    // 08 - init'd to incremental variable
	UInt8    unk0C;    // 0C - init'd to 1
	UInt8    unk0D;    // 0D - init'd to 1
	UInt16    pad0E;    // 0E
	PipboyValue    *unk10;    // 10
};

template <class T>
class PipboyPrimitiveValue : public PipboyValue
{
public:

	T    value;    // 18    
};
STATIC_ASSERT(offsetof(PipboyPrimitiveValue<bool>, value) == 0x18);


class PipboyObject : public PipboyValue
{
public:

	struct PipboyTableItem
	{
		BSFixedString    key;
		PipboyValue        *value;

		bool operator==(const BSFixedString & a_name) const { return key == a_name; }
		operator BSFixedString() const { return key; }

		static inline UInt32 GetHash(BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data, 0);
			return hash;
		}
		void	Dump(void)
		{
			_MESSAGE("\t\tkey: %s", key.c_str());
			DumpClass(value, 6);
		}
	};


	virtual ~PipboyObject();

	tHashSet<PipboyTableItem, BSFixedString>    table;    // 18
														  //...
};

STATIC_ASSERT(offsetof(PipboyObject, table) == 0x18);
*/


class PipboyArray : public PipboyValue
{
public:

	tArray<PipboyValue*>				value;		// 18
};
STATIC_ASSERT(sizeof(PipboyArray) == 0x30);


struct PipboyDataManager {
	UInt64								unk00[0x4A8 / 8];					// 00
	tArray<PipboyObject*>				inventoryObjects;				// 4A8
	UInt64								unk4C0[102];			// 4C0
	PipboyMapData						mapData;				// 7F0
};
STATIC_ASSERT(sizeof(PipboyDataManager) == 0xA28);

void tracePipboyPrimitiveValueInt(PipboyPrimitiveValue<SInt32>* val);

void tracePipboyPrimitiveValueUInt(PipboyPrimitiveValue<UInt32>* val);

void tracePipboyPrimitiveValueFloat(PipboyPrimitiveValue<float>* val);

void tracePipboyPrimitiveValueBool(PipboyPrimitiveValue<bool>* val);

void tracePipboyPrimitiveValueBSFixedStringCS(PipboyPrimitiveValue<BSFixedString>* val);

void tracePipboyArray(PipboyArray* arr);
void tracePipboyObj(PipboyObject* obj);
void tracePipboyValue(PipboyValue* pv);

extern RelocPtr <void*> g_itemMenuDataMgr;

typedef BGSInventoryItem*(*_getInventoryItemByHandleID)(void* param1, UInt32* handleid);
extern RelocAddr <_getInventoryItemByHandleID> getInventoryItemByHandleID;

BGSInventoryItem* getInventoryItemByIndex(UInt32 index);
BGSInventoryItem* getInventoryItemByHandleID_int(UInt32 handleID);

/*
class PipboyInventoryMenu;
typedef UInt64(*_PipboyMenu_SelectItem)(PipboyInventoryMenu* menu, SInt32 index);
RelocAddr <_PipboyMenu_SelectItem> PipboyMenu_SelectItem(0x0B90650);
_PipboyMenu_SelectItem PipboyMenu_SelectItem_Original;


UInt64 PipboyMenu_SelectItem_Hook(PipboyInventoryMenu* menu, SInt32 index) {
	_MESSAGE("SelectedIndex: %i", index);
	if (index > -1)
	{
		BGSInventoryItem* bg = getInventoryItemByIndex(index);
		if (bg)
		{
			if (bg->form->formType == kFormType_AMMO)
			{
				_MESSAGE("selected item is ammo: name: %s, count: %i\n", bg->form->GetFullName(), bg->stack->count);
				// here u code for switching ammo
				PlayUISound("UIPipBoyOKPress");
				return 0;
			}
			else
				return PipboyMenu_SelectItem_Original(menu, index);
		}
		else
			return PipboyMenu_SelectItem_Original(menu, index);
	}
	return PipboyMenu_SelectItem_Original(menu, index);
}

class PipboyMapMenu;
typedef UInt64(*_sub_1A3650)(PipboyMapMenu* param1, UInt32 arrayIndex, void* unk2);
RelocAddr <_sub_1A3650> sub_1A3650(0x0B85CC0);
_sub_1A3650 sub_1A3650_Original = nullptr;

UInt64 sub_1A3650_Hook(PipboyMapMenu* param1, UInt32 arrayIndex, void* unk2)
{
	_MESSAGE("B85CC0  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!================");
	DumpClass(param1, 1);
	//DumpClass(param2, 10);
	_MESSAGE("arrayIndex is: %u", arrayIndex);
	//UInt32* x;
	//x = 2;
	marker* us = (*g_PipboyDataManager)->mapData.markers.Find(&arrayIndex);
	if (us != nullptr)
	{
		TESObjectREFR* ref = nullptr;;
		LookupREFRByHandle(&us->handle, &ref);
		if (ref)
		{
			_MESSAGE("REF formID %016I64X", ref->formID);
		}
	}
	////DumpClass(param3, 10);
	//DumpClass(param4, 10);
	UInt64 res = 0;
	//res = sub_1A3650_Original(param1, param2, param3, param4);

	//_MESSAGE("param 4 %i", (UInt32)param4);
	//DumpClass(param3, 10);
	//DumpClass(param4, 10);

	//
	_MESSAGE("res %016I64X", res);
	return res;

}
*/

struct  justPointer
{
	justPointer*			unk00;
	justPointer*			unk08;
	justPointer*			unk10;
	justPointer*			unk18;
};
class BGSMessage : public TESForm
{
public:
	enum {
		kFlag_MessageBox = 1 << 0,
		kFlag_DelayInitialDisplay = 1 << 1
	};

	struct  MenuButton
	{
		BSFixedString			buttonText;
		Condition*				conditions;
	};

	struct  MenuButtons
	{
		MenuButton*				nthButton;
		MenuButtons*			next;
	};

	TESFullName					fullName;
	TESDescription				description;
	void*						unk48;						// 048 - always 0? probably unused Icon
	TESQuest*					ownerQuest;					// 050
	MenuButton*					firstMenuButton;			// 058
	MenuButtons*				menuButtons;				// 060
	BSFixedString				swfPath;					// 068
	BSFixedString				shortTitle;					// 070
	UInt32						flags;						// 078
	UInt32						displayTime;				// 07C
};
STATIC_ASSERT(sizeof(BGSMessage) == 0x80);

struct InvInterfaceStateChangeEvent
{

};

struct unkstr
{
	UInt32 HandleID;
	UInt32 pad0c;
	UInt32 unk08;
	UInt32 unk0c;
	UInt16 stackid; // ?
	UInt16 pad12[3];
	UInt32 unk18;
	UInt32 unk1c;
};
STATIC_ASSERT(sizeof(unkstr) == 0x20);

class ContainerMenuBase : public GameMenuBase
{
public:
	BSTEventSink<InvInterfaceStateChangeEvent>			eventSink1;						// E0
	BSTEventSink<MenuOpenCloseEvent>					eventSink2;						// E8
	UInt64												unkD0[(0x200 - 0xF0) / 8];		// F0
	tArray<unkstr>										playerItems;					// 200
	UInt64												unk218[(0x280 - 0x218) / 8];	// 218
	tArray<unkstr>										contItems;						// 280
};
STATIC_ASSERT(sizeof(ContainerMenuBase) == 0x298);

class ContainerMenu : public ContainerMenuBase
{

};

// E8
class TESCombatStyle : public TESForm
{
public:
	enum { kTypeID = kFormType_CSTY };

	struct General
	{
		float						offensiveMult;
		float						defensiveMult;
		float						groupOffenciveMult;

		struct EquipmentScoreMults
		{
			float					melee;
			float					magic;
			float					ranged;
			float					shout;
			float					unarmed;
			float					staff;
		};

		EquipmentScoreMults			equipmentScoreMults;

		struct AvoidThreats
		{
			float					avoidThreatChance;
			float					dodgeThreatChance;
			float					evadeThreatChance;
		};

		AvoidThreats				avoidThreats;
	};
	STATIC_ASSERT(sizeof(General) == 0x30);

	General				general;	// 20
};


class TESQuest_x;


class BGSBaseAlias
{
public:
	virtual ~BGSBaseAlias();

	BSFixedString			aliasName;	// 08
	TESQuest_x*				quest;
	UInt32					aliasID;
	UInt32					unk1C;
	void*			unk20;
};

// 48
class BGSRefAlias : public BGSBaseAlias
{
public:
	void*				unk28;
	void*				unk30;
	void*				unk38;
	Condition**			conditions;	// 40
};

// 50
class BGSRefCollectionAlias : public BGSRefAlias
{
public:
	void*				unk48;
};


/* added in f4se 0.6.7
// 20
class BGSStoryManagerTreeForm : public TESForm
{
public:
	void*			unk20;
};

// 2F0
class TESQuest_x : public BGSStoryManagerTreeForm
{
public:
	enum { kTypeID = kFormType_QUST };

	TESFullName						name;		// 028
	void*							unk38;
	void*							unk40;
	void*							unk48;
	void*							unk50;
	void*							unk58;
	void*							unk60;
	void*							unk68;
	tArray<BGSBaseAlias*>			aliases;	// 070
	void*							unk88;
	void*							unk90;
	void*							unk98;
	void*							unkA0;
	void*							unkA8;
	void*							unkB0;
	void*							unkB8;
	void*							unkC0;
	void*							unkC8;
	void*							unkD0;
	void*							unkD8;
	void*							unkE0;
	void*							unkE8;
	void*							unkF0;
	void*							unkF8;

	void*							unk100;
	void*							unk108;
	void*							unk110;
	void*							unk118;
	void*							unk120;
	void*							unk128;
	void*							unk130;
	void*							unk138;
	void*							unk140;
	void*							unk148;
	void*							unk150;
	void*							unk158;
	void*							unk160;
}; 
*/

// 38
class ExtraAliasInstanceArray : public BSExtraData
{
public:
	struct Entry
	{
		TESQuest*			quest;
		BGSRefAlias*		alias;
		void*				unk10;
	};
	tArray<Entry>		unk18;		// 18
	void*				unk30;		// 30
};

// 38
class ExtraKeywords : public BSExtraData
{
public:
	struct Entry
	{
		BGSKeyword*			keyword;
		UInt32				unk08;
		UInt32				unk10;
	};
	tArray<Entry>		unk18;		// 18
	void*				unk30;		// 30
};

// 08
class BGSEntryPointFunctionData
{
public:
	virtual ~BGSEntryPointFunctionData();
};

// 28
class BGSEntryPointFunctionDataAVAndValue : public BGSEntryPointFunctionData
{
public:
};

// 30
class BGSEntryPointFunctionDataActivateChoice : public BGSEntryPointFunctionData
{
public:
};

// 28
class BGSEntryPointFunctionDataBooleanGraphVariable : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSEntryPointFunctionDataLeveledList : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSEntryPointFunctionDataOneValue : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSEntryPointFunctionDataSpellItem : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSEntryPointFunctionDataText : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSEntryPointFunctionDataTwoValue : public BGSEntryPointFunctionData
{
public:
};

// 20
class BGSQuestPerkEntry : public BGSPerkEntry
{
public:
	TESQuest*		quest;		// 10
	UInt16			stage;		// 18
};

// 18
class BGSAbilityPerkEntry : public BGSPerkEntry
{
public:
};

// 30
class BGSEntryPointPerkEntry : public BGSPerkEntry
{
public:
	UInt8								unk10;		// 10
	UInt8								unk11;		// 11
	UInt8								unk12;		// 12
	UInt8								pad13[5];	// 13
	BGSEntryPointFunctionData*			function;	// 28
	void*								unk20;		// 20
	BGSPerk*							perk;		// 28
};
STATIC_ASSERT(offsetof(BGSEntryPointPerkEntry, perk) == 0x28);

class HasPerkVisitor
{
public:
	struct Entry
	{
		BGSPerk*	perk;
		UInt8		rank;
	};
	virtual uintptr_t Accept(Entry* pEntry);

	std::vector<Entry>				result;
};

/*

typedef UInt32(*_refenable)(TESObjectREFR * ref, bool unk1); // unk1 = 1
RelocAddr <_refenable> refenable(0x0040D970);
typedef UInt32(*_refdisable)(TESObjectREFR * ref, bool unk1); // unk1 = false
RelocAddr <_refdisable> refdisable(0x004E4300);
TESObjectREFR* ref = FindBestWeapons::GetCommandTarget();
if (ref)
{
if ((ref->flags >> 11) & 1)
{
refenable(ref, true);
}
else
{
refenable(ref, false);
}
}
*/