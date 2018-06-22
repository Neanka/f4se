#include "Shared.h"

IDebugLog	gLog;

SInt8 CheckModDropClientService()
{
	UInt32 err;

	auto schSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_CONNECT);

	if (NULL == schSCManager)
	{
		err = GetLastError();
		_DMESSAGE("OpenSCManager failed (%d)", err);
		return -1;
	}

	auto schService = OpenService(
		schSCManager,
		"ModDropClient",
		SERVICE_QUERY_CONFIG);

	if (schService == NULL)
	{
		err = GetLastError();
		switch (err)
		{
		case ERROR_SERVICE_DOES_NOT_EXIST:
			_DMESSAGE("ModDropClient service not installed");
			CloseServiceHandle(schSCManager);
			return 1;
		default:
			_DMESSAGE("OpenService failed (%d)", err);
			CloseServiceHandle(schSCManager);
			return -1;
		}
	}
	_DMESSAGE("ModDropClient service found");
	CloseServiceHandle(schSCManager);
	CloseServiceHandle(schService);
	return 0;
}

void CheckArchiveInvalidation(std::string mName)
{
	Setting	* setting = GetINISetting("bInvalidateOlderFiles:Archive");
	if (!setting->data.u8)
	{
		_WARNING("WARNING: Loose files disabled.");
		MessageBox(NULL, (LPCSTR)("Check if loose files enabled. \n" + mName + " will NOT works properly.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
		ShellExecute(0, 0, (LPCSTR)"https://www.nexusmods.com/fallout4/mods/4421/?", 0, 0, SW_SHOW);
	}
}


namespace Utils {
	bool ReadMemory(uintptr_t addr, void* data, size_t len) {
		UInt32 oldProtect;
		if (VirtualProtect((void *)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect)) {
			memcpy(data, (void*)addr, len);
			if (VirtualProtect((void *)addr, len, oldProtect, &oldProtect))
				return true;
		}
		return false;
	}
}

std::string _GetConfigOptionString(std::string file, const char * section, const char * key)
{

	file = "./Data/PRKF/" + file;
	std::string	result;
	char	resultBuf[256];
	resultBuf[0] = 0;
	UInt32	resultLen = GetPrivateProfileString(section, key, NULL, resultBuf, sizeof(resultBuf), file.c_str());
	result = resultBuf;
	return result;
}

UInt32 _GetConfigOptionInt(std::string file, const char * section, const char * key)
{

	file = "./Data/PRKF/" + file;
	UInt32 result;
	result = GetPrivateProfileInt(section, key, 0, file.c_str());
	return result;
}

std::string PBT_GetConfigOptionString(std::string file, const char * section, std::string key)
{

	file = "./Data/PBT/" + file;
	std::string	result;
	char	resultBuf[256];
	resultBuf[0] = 0;
	UInt32	resultLen = GetPrivateProfileString(section, key.c_str(), NULL, resultBuf, sizeof(resultBuf), file.c_str());
	result = resultBuf;
	return result;
}

UInt32 PBT_GetConfigOptionInt(std::string file, const char * section, const char * key)
{

	file = "./Data/PBT/" + file;
	UInt32 result;
	result = GetPrivateProfileInt(section, key, 0, file.c_str());
	return result;
}

RVA <_ExecuteCommand> ExecuteCommand;
RVA <_HasPerk> HasPerk;
RVA <_AddPerk> AddPerk;
RVA <_GetLevel> GetLevel;
RVA <_GetItemCount> GetItemCount;
RVA <uintptr_t> g_main;
RVA <_UI_AddMessage> UI_AddMessage;
RVA <void*> g_UIManager;
RVA <PipboyDataManager*> g_PipboyDataManager;
RVA <_SetPerkPoints_int> SetPerkPoints_int;
RVA <_SetPlayerName> SetPlayerName_int;
RVA <_PlaySound> PlaySound_int;
RVA <_PlaySound2> PlaySound2_int;
RVA <_LevelupMenuProcessMessage> LevelupMenuProcessMessage;
RVA <_LevelupMenuPlayPerkSound> LevelupMenuPlayPerkSound;
RVA <_LevelupMenuStopPerkSound> LevelupMenuStopPerkSound;

const char* ObScriptCommand_SexChange_sig = "40 55 53 41 56 48 8B EC 48 81 EC 80 00 00 00";

RVA <_changesex_FillNPCArray> changesex_FillNPCArray;
RVA <_changesex_CopyDataFromTemplateNPC> changesex_CopyDataFromTemplateNPC;
RVA <_changesex_UNKF02> changesex_UNKF02;
RVA <_changesex_UNKF03> changesex_UNKF03;
RVA <_changesex_UNKF04> changesex_UNKF04;
RVA <_changesex_FreeMemory> changesex_FreeMemory;
RVA <_changesex_UNKF06> changesex_UNKF06;
RVA <_changesex_UNKF07> changesex_UNKF07;
RVA <_changesex_UNKF08> changesex_UNKF08;

RVA <_GetRandomPercent> GetRandomPercent;
RVA <_GetRandomPercent2> GetRandomPercent2;

// CW
RVA <_MultiActivateMenuProcessMessage> MultiActivateMenuProcessMessage;
RVA <MultiActivateManager*> g_multiActivateManager;
RVA <UInt32*> commandTargetCompanionRef;
RVA <_CompanionListenerUnk03> CompanionListenerUnk03;

RVA <_EquipItem_int> EquipItem_int;
RVA <_UnEquipItem_int> UnEquipItem_int;


RVA <void*> unk_itemManager;




void InitExeAddress()
{
	ExecuteCommand = RVA <_ExecuteCommand>(
		"ExecuteCommand", {
			{ RUNTIME_VERSION_1_10_89, 0x0125B340 },
			{ RUNTIME_VERSION_1_10_82, 0x0125B2E0 },
			{ RUNTIME_VERSION_1_10_75, 0x0125B2E0 },
		{ RUNTIME_VERSION_1_10_64, 0x0125B320 },
		{ RUNTIME_VERSION_1_10_50, 0x0125AF00 },
		{ RUNTIME_VERSION_1_10_40, 0x0125AE40 },
		{ RUNTIME_VERSION_1_10_26, 0x012594F0 },
		{ RUNTIME_VERSION_1_10_20, 0x01259430 },
		{ RUNTIME_VERSION_1_9_4,   0x012416F0 },
		}, "40 53 55 56 57 41 54 48 81 EC 40 08 00 00");
}

void InitTIMAddress()
{
	SetPlayerName_int = RVA <_SetPlayerName>(
		"SetPlayerName_int", {
			{ RUNTIME_VERSION_1_10_89, 0x00BB9000 },
			{ RUNTIME_VERSION_1_10_82, 0x00BB8FA0 },
			{ RUNTIME_VERSION_1_10_75, 0x00BB8FA0 },
		{ RUNTIME_VERSION_1_10_64, 0x00BB8FE0 },
		{ RUNTIME_VERSION_1_10_50, 0x00BB8BC0 },
		{ RUNTIME_VERSION_1_10_40, 0x00BB8BC0 },
		{ RUNTIME_VERSION_1_10_26, 0x0BB7270 },
		}, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 48 8B 0D ? ? ? ?");
}


void InitAddresses()
{
	HasPerk = RVA <_HasPerk>(
		"HasPerk", {
			{ RUNTIME_VERSION_1_10_89, 0x00DA64A0 },
			{ RUNTIME_VERSION_1_10_82, 0x00DA6440 },
			{ RUNTIME_VERSION_1_10_75, 0x00DA6440 },
		{ RUNTIME_VERSION_1_10_64, 0x00DA6480 },
		{ RUNTIME_VERSION_1_10_50, 0x00DA6060 },
		{ RUNTIME_VERSION_1_10_40, 0x00DA5FA0 },
		{ RUNTIME_VERSION_1_10_26, 0x0DA4650 },
		{ RUNTIME_VERSION_1_10_20, 0x0DA45C0 },
		{ RUNTIME_VERSION_1_9_4,   0x0D8C810 },
		}, "48 83 EC 28 48 8B 81 00 03 00 00 48 85 C0 74 ? 4C 8B C2");
	AddPerk = RVA <_AddPerk>(
		"AddPerk", {
			{ RUNTIME_VERSION_1_10_89, 0x00DA60A0 },
			{ RUNTIME_VERSION_1_10_82, 0x00DA6040 },
			{ RUNTIME_VERSION_1_10_75, 0x00DA6040 },
		{ RUNTIME_VERSION_1_10_64, 0x00DA6080 },
		{ RUNTIME_VERSION_1_10_50, 0x00DA5C60 },
		{ RUNTIME_VERSION_1_10_40, 0x00DA5BA0 },
		{ RUNTIME_VERSION_1_10_26, 0x0DA4250 },
		{ RUNTIME_VERSION_1_10_20, 0x0DA41C0 },
		{ RUNTIME_VERSION_1_9_4,   0x0D8C410 },
		}, "48 89 5C 24 08 48 89 6C 24 10 56 57 41 56 48 83 EC 40 48 8D 99 34 04 00 00");
	GetLevel = RVA <_GetLevel>(
		"GetLevel", {
			{ RUNTIME_VERSION_1_10_89, 0x00D79D30 },
			{ RUNTIME_VERSION_1_10_82, 0x00D79CD0 },
			{ RUNTIME_VERSION_1_10_75, 0x00D79CD0 },
		{ RUNTIME_VERSION_1_10_64, 0x00D79D10 },
		{ RUNTIME_VERSION_1_10_50, 0x00D798F0 },
		{ RUNTIME_VERSION_1_10_40, 0x00D79830 },
		{ RUNTIME_VERSION_1_10_26, 0x0D77EE0 },
		{ RUNTIME_VERSION_1_10_20, 0x0D77E50 },
		{ RUNTIME_VERSION_1_9_4,   0x0D600A0 },
		}, "48 8B 89 E0 00 00 00 48 83 C1 68 E9 ? ? ? ?");
	GetItemCount = RVA <_GetItemCount>(
		"GetItemCount", {
			{ RUNTIME_VERSION_1_10_89, 0x013FB5A0 },
			{ RUNTIME_VERSION_1_10_82, 0x013FB540 },
			{ RUNTIME_VERSION_1_10_75, 0x013FB540 },
		{ RUNTIME_VERSION_1_10_64, 0x013FB580 },
		{ RUNTIME_VERSION_1_10_50, 0x013FB160 },
		{ RUNTIME_VERSION_1_10_40, 0x013FB0A0 },
		{ RUNTIME_VERSION_1_10_26, 0x13F9740 },
		{ RUNTIME_VERSION_1_10_20, 0x13F9680 },
		{ RUNTIME_VERSION_1_9_4,   0x13DDAF0 },
		}, "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 49 8B F9 41 0F B6 E8");
	g_main = RVA <uintptr_t>(
		"g_main", {
			{ RUNTIME_VERSION_1_10_89, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_82, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_75, 0x05ADD2C8 },
		{ RUNTIME_VERSION_1_10_64, 0x05ADD2C8 },
		{ RUNTIME_VERSION_1_10_50, 0x05ADC2C8 },
		{ RUNTIME_VERSION_1_10_40, 0x05ADE288 },
		{ RUNTIME_VERSION_1_10_26, 0x5AC25E8 },
		{ RUNTIME_VERSION_1_10_20, 0x5AC25E8 },
		{ RUNTIME_VERSION_1_9_4,   0x5A2F648 },
		}, "48 8B 05 ? ? ? ? 80 78 25 00 0F 85 ? ? ? ? 49 8B", 0, 3, 7);
	/*g_globalEvents = RVA <BSTGlobalEvent*>(
	"g_globalEvents", {
	{ RUNTIME_VERSION_1_10_64, 0x05907C98 },
	{ RUNTIME_VERSION_1_10_50, 0x05906C98 },
	{ RUNTIME_VERSION_1_10_40, 0x05908C98 },
	{ RUNTIME_VERSION_1_10_26, 0x58ED018 },
	}, "48 8B 15 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C2 10", 0, 3, 7);*/ // added in 1 10 75 into f4se
	GetRandomPercent = RVA <_GetRandomPercent>(
		"GetRandomPercent", {
			{ RUNTIME_VERSION_1_10_89, 0x01B12B20 },
			{ RUNTIME_VERSION_1_10_82, 0x01B12AC0 },
			{ RUNTIME_VERSION_1_10_75, 0x01B12AC0 },
		{ RUNTIME_VERSION_1_10_64, 0x01B12B00 },
		{ RUNTIME_VERSION_1_10_50, 0x01B126E0 },
		{ RUNTIME_VERSION_1_10_40, 0x01B12620 },
		}, "40 53 48 83 EC 20 8B D9 83 F9 01");
	GetRandomPercent2 = RVA <_GetRandomPercent2>(
		"GetRandomPercent2", {
			{ RUNTIME_VERSION_1_10_89, 0x01B12BC0 },
			{ RUNTIME_VERSION_1_10_82, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_75, 0x01B12B60 },
		{ RUNTIME_VERSION_1_10_64, 0x01B12BA0 },
		{ RUNTIME_VERSION_1_10_50, 0x01B12780 },
		{ RUNTIME_VERSION_1_10_40, 0x01B126C0 },
		}, "48 89 5C 24 08 57 48 83 EC 20 8B DA 8B F9");
	SetPerkPoints_int = RVA <_SetPerkPoints_int>(
		"SetPerkPoints_int", {
			{ RUNTIME_VERSION_1_10_89, 0x00EB8A40 },
			{ RUNTIME_VERSION_1_10_82, 0x00EB89E0 },
			{ RUNTIME_VERSION_1_10_75, 0x00EB89E0 },
		{ RUNTIME_VERSION_1_10_64, 0x00EB8A20 },
		{ RUNTIME_VERSION_1_10_50, 0x0EB8600 },
		}, "48 83 EC 28 88 91 F1 0C 00 00");
	PlaySound_int = RVA <_PlaySound>(
		"PlaySound_int", {
			{ RUNTIME_VERSION_1_10_89, 0x012BE150 },
			{ RUNTIME_VERSION_1_10_82, 0x012BE0F0 },
			{ RUNTIME_VERSION_1_10_75, 0x012BE0F0 },
		{ RUNTIME_VERSION_1_10_64, 0x012BE130 },
		{ RUNTIME_VERSION_1_10_50, 0x012BDD10 },
		}, "48 83 EC 38 E8 ? ? ? ? 48 85 C0 74 ? 48 89 5C 24 30");
	PlaySound2_int = RVA <_PlaySound2>(
		"PlaySound2_int", {
			{ RUNTIME_VERSION_1_10_89, 0x012BE1C0 },
			{ RUNTIME_VERSION_1_10_82, 0x012BE160 },
			{ RUNTIME_VERSION_1_10_75, 0x012BE160 },
		{ RUNTIME_VERSION_1_10_64, 0x012BE1A0 },
		{ RUNTIME_VERSION_1_10_50, 0x012BDD80 },
		}, "48 89 5C 24 08 57 48 83 EC 50 48 8B D9 E8 ? ? ? ?");
	LevelupMenuProcessMessage = RVA <_LevelupMenuProcessMessage>(
		"LevelupMenuProcessMessage", {
			{ RUNTIME_VERSION_1_10_89, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_82, 0x00B38360 },
			{ RUNTIME_VERSION_1_10_75, 0x00B38360 },
		{ RUNTIME_VERSION_1_10_64, 0x00B38360 },
		{ RUNTIME_VERSION_1_10_50, 0x0B38360 },
		}, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B F1 8B 4A 10");
	LevelupMenuPlayPerkSound = RVA <_LevelupMenuPlayPerkSound>(
		"LevelupMenuPlayPerkSound", {
			{ RUNTIME_VERSION_1_10_89, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_82, 0x00B39750 },
			{ RUNTIME_VERSION_1_10_75, 0x00B39750 },
		{ RUNTIME_VERSION_1_10_64, 0x00B39750 },
		{ RUNTIME_VERSION_1_10_50, 0x0B39750 },
		}, "48 89 5C 24 08 57 48 83 EC 30 48 8B F9 8B CA 33 DB E8 ? ? ? ? 48 85 C0 74 ? 80 78 1A 5F 75 ? 48 8B 98 88 00 00 00 48 81 C7 80 01 00 00");
	LevelupMenuStopPerkSound = RVA <_LevelupMenuStopPerkSound>(
		"LevelupMenuStopPerkSound", {
			{ RUNTIME_VERSION_1_10_89, 0x01AC7FB0 },
			{ RUNTIME_VERSION_1_10_82, 0x01AC7F50 },
			{ RUNTIME_VERSION_1_10_75, 0x01AC7F50 },
		{ RUNTIME_VERSION_1_10_64, 0x01AC7F90 },
		{ RUNTIME_VERSION_1_10_50, 0x01AC7B70 },
		}, "40 53 48 83 EC 20 8B 19 83 FB FF 74 ? C6 41 05 02");
	g_PipboyDataManager = RVA <PipboyDataManager*>(
		"g_PipboyDataManager", {
			{ RUNTIME_VERSION_1_10_89, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_82, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_75, 0x05909B70 },
		{ RUNTIME_VERSION_1_10_64, 0x05909B70 },
		{ RUNTIME_VERSION_1_10_50, 0x05908B70 },

		}, "48 8B 0D ? ? ? ? 48 8D 44 24 48 48 8D 54 24 20 48 89 44 24 20 48 8D 44 24 50 48 81 C1 E8 08 00 00 ", 0, 3, 7);


	//RelocPtr <PipboyDataManager*> g_PipboyDataManager(0x05908B70);
}

void InitUIManager()
{
	UI_AddMessage = RVA <_UI_AddMessage>(
		"UI_AddMessage", {
			{ RUNTIME_VERSION_1_10_89, 0x0204CA30 },
			{ RUNTIME_VERSION_1_10_82, 0x0204C9D0 },
			{ RUNTIME_VERSION_1_10_75, 0x0204C960 },
		{ RUNTIME_VERSION_1_10_64, 0x0204C9A0 },
		{ RUNTIME_VERSION_1_10_50, 0x0204C580 },
		{ RUNTIME_VERSION_1_10_40, 0x204CB10 },
		{ RUNTIME_VERSION_1_10_26, 0x204B1B0 },
		{ RUNTIME_VERSION_1_10_20, 0x204B0F0 },
		{ RUNTIME_VERSION_1_9_4,   0x2024830 },
		}, "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 83 EC 20 44 8B 0D ? ? ? ? 65 48 8B 04 25 58 00 00 00 48 8B E9 4A 8B 34 C8 B9 C0 09 00 00");
	g_UIManager = RVA <void*>(
		"g_UIManager", {
			{ RUNTIME_VERSION_1_10_89, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_82, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_75, 0x05909B48 },
		{ RUNTIME_VERSION_1_10_64, 0x05909B48 },
		{ RUNTIME_VERSION_1_10_50, 0x05908B48 },
		{ RUNTIME_VERSION_1_10_40, 0x0590AB48 },
		{ RUNTIME_VERSION_1_10_26, 0x58EEEC8 },
		{ RUNTIME_VERSION_1_10_20, 0x58EEEC8 },
		{ RUNTIME_VERSION_1_9_4,   0x585BD48 },
		}, "48 8B 3D ? ? ? ? E8 ? ? ? ? 41 B8 01 00 00 00 48 8B CF 48 8B D0", 0, 3, 7);
}

void InitCWAddresses()
{
	MultiActivateMenuProcessMessage = RVA <_MultiActivateMenuProcessMessage>(
		"MultiActivateMenuProcessMessage", {
			{ RUNTIME_VERSION_1_10_89, 0x00B7B860 },
			{ RUNTIME_VERSION_1_10_82, 0x00B7B800 },
			{ RUNTIME_VERSION_1_10_75, 0x00B7B800 },
			{ RUNTIME_VERSION_1_10_50, 0x0B7B420 },
		}, "48 83 EC 28 44 8B 42 10 41 FF C8 41 83 F8 01");
	g_multiActivateManager = RVA <MultiActivateManager*>(
		"g_multiActivateManager", {
			{ RUNTIME_VERSION_1_10_89, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_82, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_75, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_50, 0x05A9DB50 },
		}, "48 8B 0D ? ? ? ? 48 8D 95 80 03 00 00", 0, 3, 7);
	commandTargetCompanionRef = RVA <UInt32*>(
		"commandTargetCompanionRef", {
			{ RUNTIME_VERSION_1_10_89, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_82, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_75, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_50, 0x05A9909C },
		}, "48 89 7C 24 38 48 C7 44 24 20 00 00 00 00 4C 89 74 24 30", -7, 3, 7);
	CompanionListenerUnk03 = RVA <_CompanionListenerUnk03>(
		"CompanionListenerUnk03", {
			{ RUNTIME_VERSION_1_10_89, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_82, 0x009FFA60 },
			{ RUNTIME_VERSION_1_10_75, 0x009FFA60 },
			{ RUNTIME_VERSION_1_10_50, 0x09FFA60 },
		}, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 50 8B FA");
	EquipItem_int = RVA <_EquipItem_int>(
		"EquipItem_int", {
			{ RUNTIME_VERSION_1_10_89, 0x00E1BB70 },
			{ RUNTIME_VERSION_1_10_82, 0x00E1BB10 },
			{ RUNTIME_VERSION_1_10_75, 0x00E1BB10 },
			{ RUNTIME_VERSION_1_10_50, 0x00E1B730 },
		}, "4C 8B DC 49 89 53 10 55 56 41 54 41 57");
	UnEquipItem_int = RVA <_UnEquipItem_int>(
		"UnEquipItem_int", {
			{ RUNTIME_VERSION_1_10_89, 0x00E1BF50 },
			{ RUNTIME_VERSION_1_10_82, 0x00E1BEF0 },
			{ RUNTIME_VERSION_1_10_75, 0x00E1BEF0 },
			{ RUNTIME_VERSION_1_10_50, 0x00E1BB10 },
		}, "48 8B C4 48 89 58 18 55 57 41 56 48 83 EC 70");
	unk_itemManager = RVA <void*>(
		"unk_itemManager", {
			{ RUNTIME_VERSION_1_10_89, 0x05A10618 },
			{ RUNTIME_VERSION_1_10_82, 0x05A0F618 },
			{ RUNTIME_VERSION_1_10_75, 0x05A0F618 },
			{ RUNTIME_VERSION_1_10_50, 0x05A0F618 },
		}, "48 8B 0D ? ? ? ? 4C 89 7C 24 50 44 88 7C 24 48 C6 44 24 40 01 44 88 7C 24 38 44 88 7C 24 30 89 44 24 28", 0, 3, 7);


}


void InitSexChangeAddresses()
{
	//ObScriptCommand_SexChange_sig, 0x15A, 1, 5
	//48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 30 49 8B E8
	changesex_FillNPCArray = RVA <_changesex_FillNPCArray>({
		{ RUNTIME_VERSION_1_10_40, 0x05BA370 },
		{ RUNTIME_VERSION_1_10_26, 0x05BA310 },
		}, ObScriptCommand_SexChange_sig, 0x15A, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x16C, 1, 5
	//40 53 41 56 48 83 EC 28 48 89 7C 24 50
	changesex_CopyDataFromTemplateNPC = RVA <_changesex_CopyDataFromTemplateNPC>({
		{ RUNTIME_VERSION_1_10_40, 0x05B1170 },
		{ RUNTIME_VERSION_1_10_26, 0x05B1150 },
		}, ObScriptCommand_SexChange_sig, 0x16C, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x176, 1, 5
	//48 89 5C 24 08 57 48 83 EC 20 48 8B B9 D0 02 00 00
	changesex_UNKF02 = RVA <_changesex_UNKF02>({
		{ RUNTIME_VERSION_1_10_40, 0x5B9640 },
		{ RUNTIME_VERSION_1_10_26, 0x5B95E0 },
		}, ObScriptCommand_SexChange_sig, 0x176, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x197, 1, 5
	//48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 30 48 8B 99 D0 02 00 00
	changesex_UNKF03 = RVA <_changesex_UNKF03>({
		{ RUNTIME_VERSION_1_10_40, 0x05B8ED0 },
		{ RUNTIME_VERSION_1_10_26, 0x05B8E70 },
		}, ObScriptCommand_SexChange_sig, 0x197, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x1A3, 1, 5
	//40 53 48 83 EC 30 44 8B 42 18
	changesex_UNKF04 = RVA <_changesex_UNKF04>({
		{ RUNTIME_VERSION_1_10_40, 0x05B9960 },
		{ RUNTIME_VERSION_1_10_26, 0x05B9900 },
		}, ObScriptCommand_SexChange_sig, 0x1A3, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x1B2, 1, 5
	//40 53 48 83 EC 20 48 8B 51 08 48 8B D9 48 85 D2 74 ? 48 8B 09 E8 ? ? ? ?
	changesex_FreeMemory = RVA <_changesex_FreeMemory>({
		{ RUNTIME_VERSION_1_10_40, 0x1B10E50 },
		{ RUNTIME_VERSION_1_10_26, 0x1B0F4F0 },
		}, ObScriptCommand_SexChange_sig, 0x1B2, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x1C7, 1, 5
	//40 56 48 83 EC 20 48 8B B1 E0 02 00 00
	changesex_UNKF06 = RVA <_changesex_UNKF06>({
		{ RUNTIME_VERSION_1_10_40, 0x5B4CC0 },
		{ RUNTIME_VERSION_1_10_26, 0x5B4CA0 },
		}, ObScriptCommand_SexChange_sig, 0x1C7, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x1D1, 1, 5
	//48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 20 8B 41 10 0F B6 F2
	changesex_UNKF07 = RVA <_changesex_UNKF07>({
		{ RUNTIME_VERSION_1_10_40, 0x5BD9D0 },
		{ RUNTIME_VERSION_1_10_26, 0x5BD970 },
		}, ObScriptCommand_SexChange_sig, 0x1D1, 1, 5);
	//ObScriptCommand_SexChange_sig, 0x1DB, 1, 5
	//48 89 5C 24 20 88 54 24 10 57
	changesex_UNKF08 = RVA <_changesex_UNKF08>({
		{ RUNTIME_VERSION_1_10_40, 0x5BA160 },
		{ RUNTIME_VERSION_1_10_26, 0x5BA100 },
		}, ObScriptCommand_SexChange_sig, 0x1DB, 1, 5);
}

bool changesex(Actor* actor, SInt8 sexToSet, bool customFace)
{
	TESNPC * npc = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
	if (!npc) return false;
	UInt8 currentSex = CALL_MEMBER_FN(npc, GetSex)();
	if (currentSex == sexToSet) return false;
	bool isFemale = 0;

	//NiNode * niNode = actor->GetObjectRootNode();
	//if (v15)
	//	(*(void(__fastcall **)(__int64))(*(_QWORD *)v15 + 0x20i64))(v15);

	if ((sexToSet == -1 && currentSex == 0) || sexToSet == 1) isFemale = 1;
	TESActorBaseData* basedata = DYNAMIC_CAST(actor->baseForm, TESForm, TESActorBaseData);
	CALL_MEMBER_FN(basedata, SetSex)(1, isFemale, 1);
	if (actor == (*g_player) && customFace)
	{
		TESRace * race = npc->race.race;
		UInt8 sex = CALL_MEMBER_FN(npc, GetSex)();
		TemplateData td = {};
		changesex_FillNPCArray(race, sex, &td);
		changesex_CopyDataFromTemplateNPC(npc, td.templateNPCs[0], 1);
		if (&td.templateNPCs) changesex_FreeMemory(&td);
	}
	else
	{
		HeadPartsData headPartsData = {};
		DumpClass(&headPartsData, 10);
		changesex_UNKF02(npc);
		DumpClass(&headPartsData, 10);
		changesex_UNKF03(npc, &headPartsData);
		DumpClass(&headPartsData, 10);
		changesex_UNKF04(npc, &headPartsData);
		DumpClass(&headPartsData, 10);
		if (&headPartsData.headParts) changesex_FreeMemory(&headPartsData);
	}
	changesex_UNKF06(npc);
	changesex_UNKF07(npc, 0);
	changesex_UNKF08(npc, 0);
	auto middleProcess = actor->middleProcess;
	if (middleProcess) middleProcess->unk08->unk496 |= 0x20;
	CALL_MEMBER_FN((Actor*)actor, QueueUpdate)(0, 0, 1, 0); // bool bDoFaceGen, UInt32 unk2, bool DoQueue, UInt32 flags
	return true;
}

UInt8 GetPerkPoints()
{
	UInt8 ppts = Utils::GetOffset<UInt8>(*g_player, 0xCF1);
	_DMESSAGE("NUM PERK POINTS: %i", ppts);
	return ppts;
}

UInt16 GetSkillsPoints()
{
	UInt16 spts = Utils::GetOffset<UInt16>(*g_player, 0xCF4);
	_DMESSAGE("NUM SKILLS POINTS: %i", spts);
	return spts;
}

UInt8 GetPRKFStarted()
{
	UInt8 result = Utils::GetOffset<UInt8>(*g_player, 0xCF7);
	_DMESSAGE("PRKF STARTED: %i", result);
	return result;
}

void SetPRKFStarted(UInt8 started)
{
	UInt8* status = Utils::GetOffsetPtr<UInt8>(*g_player, 0xCF7);
	*status = started;
}

void ModSkillsPoints(UInt16 count)
{

}

void ModPerkPoints(SInt8 count)
{
	UInt8 result = GetPerkPoints();
	if (count < -result)
	{
		result = 0;
	}
	else
	{
		result = result + count;
		if (result > 255) result = 255;
	}
	SetPerkPoints_int(*g_player, result);
}

void MenuOpenClose_int(BSFixedString asMenuName, bool abOpen) {
	int aiOpen = (abOpen) ? 1 : 3;
	UI_AddMessage(*g_UIManager, &asMenuName, aiOpen);
}

void UI_AddMessage_int(BSFixedString asMenuName, int state) {
	UI_AddMessage(*g_UIManager, &asMenuName, state);
}

void pauseGame(bool pause) {
	*((unsigned char*)(*g_main + 0x2A)) = pause;
}

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char * dispatcherName)
{
	for (int i = 0; i < globalEvents->eventSources.count; i++) {
		const char* name = GetObjectClassName(globalEvents->eventSources[i]) + 15;    // ?$EventSource@V
		if (strstr(name, dispatcherName) == name) {
			return &globalEvents->eventSources[i]->eventDispatcher;
		}
	}
	return nullptr;
}

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

TESForm * GetFormFromIdentifier(const std::string & identifier)
{
	auto delimiter = identifier.find('|');
	if (delimiter != std::string::npos) {
		std::string modName = identifier.substr(0, delimiter);
		std::string modForm = identifier.substr(delimiter + 1);

		const ModInfo* mod = (*g_dataHandler)->LookupModByName(modName.c_str());
		if (mod && mod->modIndex != -1) {
			UInt32 formID = std::stoul(modForm, nullptr, 16) & 0xFFFFFF;
			UInt32 flags = Utils::GetOffset<UInt32>(mod, 0x334);
			if (flags & (1 << 9)) {
				// ESL
				formID &= 0xFFF;
				formID |= 0xFE << 24;
				formID |= Utils::GetOffset<UInt16>(mod, 0x372) << 12;	// ESL load order
			}
			else {
				formID |= (mod->modIndex) << 24;
			}
			return LookupFormByID(formID);
		}
	}
	return nullptr;
}

RelocPtr <FavoritesManagerEx*> g_favoritesManagerEx(0x05A97CE0);

void tracePipboyPrimitiveValueInt(PipboyPrimitiveValue<SInt32>* val)
{
	_MESSAGE("type:     int\t\tvalue: %16i\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueUInt(PipboyPrimitiveValue<UInt32>* val)
{
	_MESSAGE("type:    uint\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueFloat(PipboyPrimitiveValue<float>* val)
{
	_MESSAGE("type:   float\t\tvalue: %16f\t\thex: 0x%016I64X", val->value, val->value);
};

void tracePipboyPrimitiveValueBool(PipboyPrimitiveValue<bool>* val)
{
	_MESSAGE("type:    bool\t\tvalue: %16s", val->value ? "true" : "false");
};

void tracePipboyPrimitiveValueBSFixedStringCS(PipboyPrimitiveValue<BSFixedString>* val)
{
	_MESSAGE("type:  string\t\tvalue: %16s", val->value.c_str());
};


void tracePipboyValue(PipboyValue* pv)
{
	UInt64 vtbladdress = *reinterpret_cast<UInt64*>((uintptr_t)pv) - RelocationManager::s_baseAddr;
	switch (vtbladdress)
	{
	case 0x2D545C0:	// BSFixedStringCS
		tracePipboyPrimitiveValueBSFixedStringCS((PipboyPrimitiveValue<BSFixedString>*)pv);
		break;
	case 0x2D54668:	// uint
		tracePipboyPrimitiveValueUInt((PipboyPrimitiveValue<UInt32>*)pv);
		break;
	case 0x2D545F8:	// bool
		tracePipboyPrimitiveValueBool((PipboyPrimitiveValue<bool>*)pv);
		break;
	case 0x2D54630:	// int
		tracePipboyPrimitiveValueInt((PipboyPrimitiveValue<SInt32>*)pv);
		break;
	case 0x2D546A0:	// float
		tracePipboyPrimitiveValueFloat((PipboyPrimitiveValue<float>*)pv);
		break;
	case 0x2D53FE8:	// PipboyArray
		tracePipboyArray((PipboyArray*)pv);
		break;
	case 0x2D55B78:	// PipboyObject
		tracePipboyObj((PipboyObject*)pv);
		break;
	default:
		break;
	}
};

void tracePipboyArray(PipboyArray* arr)
{
	_MESSAGE("type:  array\t\titem count:%i", arr->value.count);
	//DumpClass(arr->value.entries, arr->value.count);
	gLog.Indent();
	for (size_t i = 0; i < arr->value.count; i++)
	{
		tracePipboyValue(arr->value[i]);
	};
	gLog.Outdent();
};

void tracePipboyObj(PipboyObject* obj)
{
	_MESSAGE("type:  object");
	gLog.Indent();
	obj->table.ForEach([](PipboyObject::PipboyTableItem* ti) {
		_MESSAGE("key: %s", ti->key.c_str());
		tracePipboyValue(ti->value);
		return true;
	}
	);
	gLog.Outdent();
};


RelocPtr <void*> g_itemMenuDataMgr(0x0590DA00);
RelocAddr <_getInventoryItemByHandleID> getInventoryItemByHandleID(0x001A3650);

BGSInventoryItem* getInventoryItemByIndex(UInt32 index)
{
	BSFixedString str = BSFixedString("HandleID");
	PipboyObject::PipboyTableItem *ti = (*g_PipboyDataManager)->inventoryObjects[index]->table.Find(&str);
	if (ti)
	{
		UInt32 val = ((PipboyPrimitiveValue<UInt32>*)(ti->value))->value;
		_MESSAGE("handleID: %u", val);

		BGSInventoryItem* bg = getInventoryItemByHandleID(*g_itemMenuDataMgr, &val);
		if (bg)
		{
			return bg;
		}
		else
		{
			return nullptr;
		}

	}
	return nullptr;
}

BGSInventoryItem* getInventoryItemByHandleID_int(UInt32 handleID)
{
	BGSInventoryItem* bg = getInventoryItemByHandleID(*g_itemMenuDataMgr, &handleID);
	if (bg)
	{
		return bg;
	}
	else
	{
		return nullptr;
	}

}

uintptr_t HasPerkVisitor::Accept(Entry* pEntry) //bool, don't use bool,VS2015 compiler seems has a bug.
{
	if (pEntry != nullptr && pEntry->perk != nullptr)
	{
		result.push_back(Entry{ pEntry->perk, pEntry->rank });
	}
	return 1;
}