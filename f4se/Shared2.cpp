#include "Shared2.h"

IDebugLog	gLog;

void logMessage(std::string aString)
{
	_MESSAGE((aString).c_str());
}

void errorMessage(std::string aString)
{
	logMessage("[ERROR] " + aString);
}

bool to_bool(std::string const& s) {
	return s != "0";
}

RelocPtr <InventoryInterface*> g_inventoryInterface(0x0);
RelocPtr <ActorEquipManager*> g_actorEquipManager(0x0);

void Shared2_Init()
{
	RELOC_GLOBAL_VAL(g_inventoryInterface, "48 8B FA 48 8B D9 74 ? 48 8B D1", 11, 3, 7);
	RELOC_GLOBAL_VAL(g_actorEquipManager, "48 8B 0D ? ? ? ? 4C 89 7C 24 50 44 88 7C 24 48 C6 44 24 40 01 44 88 7C 24 38 44 88 7C 24 30 89 44 24 28", 0, 3, 7);
};

RelocPtr <void*> g_holotapeStateChangedEventDispatcherAddress(0x0);
RelocPtr <void*> g_bGSInventoryItemEventDispatcherAddress(0x0);
RelocPtr <void*> g_playerDifficultySettingChangedDispatcherAddress(0x0);

void Shared2_InitEvents()
{
	RELOC_GLOBAL_VAL(g_holotapeStateChangedEventDispatcherAddress, "48 83 C1 60 E8 ? ? ? ? 48 8D 8F C8 00 00 00", 24, 1, 5, { {9,1,5} });
	RELOC_GLOBAL_VAL(g_bGSInventoryItemEventDispatcherAddress, "48 83 C1 60 E8 ? ? ? ? 48 8D 8F C8 00 00 00", 44, 1, 5, { { 9,1,5 } });
	RELOC_GLOBAL_VAL(g_playerDifficultySettingChangedDispatcherAddress, "48 83 C1 60 E8 ? ? ? ? 48 8D 8F C8 00 00 00", 64, 1, 5, { { 9,1,5 } });
};

void InitReloc() {
	logMessage("InitReloc");
	
	
	RELOC_MEMBER_FN(BSFixedString, ctor, "E8 ? ? ? ? 49 8B CF 48 8B D0 E8 ? ? ? ? 48 8D 8D ? ? ? ? 8B D8", 0, 1, 5);
	RELOC_MEMBER_FN(BSFixedString, Set, "E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 83 FB 02", 0, 1, 5);
	RELOC_MEMBER_FN(BSFixedString, Release, "E8 ? ? ? ? 48 8B 0E E8 ? ? ? ? 48 C7 06 ? ? ? ?", 0, 1, 5);

	RELOC_MEMBER_FN(Heap, Allocate, "E8 ? ? ? ? 48 85 C0 74 08 48 8B C8 E8 ? ? ? ? 49 8B 0E", 0, 1, 5);
	RELOC_MEMBER_FN(Heap, Free, "E8 ? ? ? ? EB 1E 41 8D 46 FF 48 8B D3 83 E0 01", 0, 1, 5);

	RELOC_MEMBER_FN(GFxValue::ObjectInterface, SetMember, "25 ? ? ? ? 4C 8D 4D F0 4C 8D 05 ? ? ? ? 3C 0A 0F 94 C0", 0x19, 1, 5);
	RELOC_MEMBER_FN(GFxValue::ObjectInterface, ReleaseManaged_Internal, "E8 ? ? ? ? 48 8D 15 ? ? ? ? 45 33 C0 49 8B CE 41 C6 86 ? ? ? ? ?", 0, 1, 5);
	RELOC_MEMBER_FN(GFxValue::ObjectInterface, Invoke, "E8 ? ? ? ? 49 8B CC E8 ? ? ? ? 49 8B 54 24 ?", 0, 1, 5);
	RELOC_MEMBER_FN(GFxValue::ObjectInterface, AddManaged_Internal, "8B 42 08 25 ? ? ? ? 83 F8 06 74 2E");
	RELOC_MEMBER_FN(GFxValue::ObjectInterface, PushBack, "40 53 48 83 EC 40 48 8B 41 08 4D 8B C8");

	RELOC_GLOBAL_VAL(CalculateCRC32_64, "E8 ? ? ? ? 4C 8B 83 ? ? ? ? 4D 85 C0 74 51 8B 53 0C 8B 4C 24 50", 0, 1, 5);
	RELOC_GLOBAL_VAL(WorldToScreen_Internal, "E8 ? ? ? ? F3 0F 10 17 F3 0F 10 6F ?", 0, 1, 5);
	RELOC_GLOBAL_VAL(LookupREFRByHandle, "E8 ? ? ? ? 48 8B 5D 67 48 85 DB 0F 84 ? ? ? ?", 0, 1, 5);

	RELOC_GLOBAL_VAL(g_player, "48 8B 05 ? ? ? ? 48 85 C0 74 0C F0 FF 40 28", 0, 3, 7);
	RELOC_GLOBAL_VAL(g_mainHeap, "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 55 AF", 0, 3, 7);
	RELOC_GLOBAL_VAL(LookupREFRByHandle, "E8 ? ? ? ? 48 8B 5D 67 48 85 DB 0F 84 ? ? ? ?", 0, 1, 5);
	
	
}