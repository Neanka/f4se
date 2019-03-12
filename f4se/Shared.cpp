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

namespace HookUtil
{

	template<class Ty>
	static inline Ty SafeWrite_Impl(uintptr_t addr, Ty data)
	{
		DWORD	oldProtect = 0;
		Ty		oldVal = 0;

		if (VirtualProtect((void *)addr, sizeof(Ty), PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			Ty *p = (Ty*)addr;
			oldVal = *p;
			*p = data;
			VirtualProtect((void *)addr, sizeof(Ty), oldProtect, &oldProtect);
		}

		return oldVal;
	}

	uintptr_t SafeWrite64(uintptr_t addr, uintptr_t data)
	{
		return SafeWrite_Impl(addr, data);
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

RVA <_LevelupMenuProcessMessage> LevelupMenuProcessMessage;
RVA <_LevelupMenuPlayPerkSound> LevelupMenuPlayPerkSound;
RVA <_LevelupMenuStopPerkSound> LevelupMenuStopPerkSound;
RVA <_GetSoundByName> GetSoundByName;


RVA <_LevelupMenuPlaySound_funk1> LevelupMenuPlaySound_funk1;
RVA <_LevelupMenuPlaySound_funk2> LevelupMenuPlaySound_funk2;
RVA <void*> LevelupMenuPlaySound_var1;

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

// WSM

RVA <WorkshopEntry*> g_rootWorkshopEntry; // (0x59198D0);
RVA <UInt16> g_workshopDepth; //(0x591865C)

RVA <_GetSelectedWorkshopEntry> GetSelectedWorkshopEntry; // (0x01F8C20);

RVA <_WM_Up> WM_Up; // (0x0BF1B40);

RVA <_OnWorkshopMenuButtonEvent> OnWorkshopMenuButtonEvent; // (0x00BEFD60);

RVA <_WorkshopMenuProcessMessage> WorkshopMenuProcessMessage; // (0x00BEF4C0);

RVA <uintptr_t> wsm_firstAddress; // 0xBF1B90
RVA <uintptr_t> wsm_secondAddress; // 0xBF1B7F

void InitWSMAddresses()
{
	g_rootWorkshopEntry = RVA <WorkshopEntry*>(
		"g_rootWorkshopEntry", {
			{ RUNTIME_VERSION_1_10_114, 0x059198E0 },
			{ RUNTIME_VERSION_1_10_111, 0x059198E0 },
			{ RUNTIME_VERSION_1_10_106, 0x059198E0 },
		}, WSM_SIG, 4, 3, 7);
	// put into plugin load: g_rootWorkshopEntry.SetEffective(g_rootWorkshopEntry.GetUIntPtr()-0x10);
	g_workshopDepth = RVA <UInt16>(
		"g_workshopDepth", {
			{ RUNTIME_VERSION_1_10_114, 0x0591865C },
			{ RUNTIME_VERSION_1_10_111, 0x0591865C },
			{ RUNTIME_VERSION_1_10_106, 0x0591865C },
		}, WSM_SIG, 18, 4, 8);
	GetSelectedWorkshopEntry = RVA <_GetSelectedWorkshopEntry>(
		"GetSelectedWorkshopEntry", {
			{ RUNTIME_VERSION_1_10_114, 0x001F8C20 },
			{ RUNTIME_VERSION_1_10_111, 0x001F8C20 },
			{ RUNTIME_VERSION_1_10_106, 0x001F8C20 },
		}, "48 89 5C 24 08 45 33 C9 4C 8B C2");
	OnWorkshopMenuButtonEvent = RVA <_OnWorkshopMenuButtonEvent>(
		"OnWorkshopMenuButtonEvent", {
			{ RUNTIME_VERSION_1_10_114, 0x00BEFD60 },
			{ RUNTIME_VERSION_1_10_111, 0x00BEFD60 },
			{ RUNTIME_VERSION_1_10_106, 0x00BEFD60 },
		}, "48 8B C4 55 41 56 41 57 48 8D A8 28 FF FF FF");
	WorkshopMenuProcessMessage = RVA <_WorkshopMenuProcessMessage>(
		"WorkshopMenuProcessMessage", {
			{ RUNTIME_VERSION_1_10_114, 0x00BEF4C0 },
			{ RUNTIME_VERSION_1_10_111, 0x00BEF4C0 },
			{ RUNTIME_VERSION_1_10_106, 0x00BEF4C0 },
		}, "48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 70 FF FF FF");
	wsm_firstAddress = RVA <uintptr_t>(
		"wsm_firstAddress", {
			{ RUNTIME_VERSION_1_10_114, 0x00BF1B90 },
			{ RUNTIME_VERSION_1_10_111, 0x00BF1B90 },
			{ RUNTIME_VERSION_1_10_106, 0x00BF1B90 },
		}, WSM_SIG1, 30);
	wsm_secondAddress = RVA <uintptr_t>(
		"wsm_secondAddress", {
			{ RUNTIME_VERSION_1_10_114, 0x00BF1B7F },
			{ RUNTIME_VERSION_1_10_111, 0x00BF1B7F },
			{ RUNTIME_VERSION_1_10_106, 0x00BF1B7F },
		}, WSM_SIG1, 13);
}

void InitExeAddress()
{
	ExecuteCommand = RVA <_ExecuteCommand>(
		"ExecuteCommand", {
			{ RUNTIME_VERSION_1_10_120, 0x0125B380 },
			{ RUNTIME_VERSION_1_10_114, 0x0125B380 },
			{ RUNTIME_VERSION_1_10_111, 0x0125B380 },
			{ RUNTIME_VERSION_1_10_106, 0x0125B380 },
			{ RUNTIME_VERSION_1_10_98, 0x0125B380 },
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
			{ RUNTIME_VERSION_1_10_120, 0x00BB9040 },
			{ RUNTIME_VERSION_1_10_114, 0x00BB9040 },
			{ RUNTIME_VERSION_1_10_106, 0x00BB9040 },
			{ RUNTIME_VERSION_1_10_98, 0x00BB9040 },
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
			{ RUNTIME_VERSION_1_10_120, 0x00DA64E0 },
			{ RUNTIME_VERSION_1_10_114, 0x00DA64E0 },
			{ RUNTIME_VERSION_1_10_111, 0x00DA64E0 },
			{ RUNTIME_VERSION_1_10_106, 0x00DA64E0 },
			{ RUNTIME_VERSION_1_10_98, 0x00DA64E0 },
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
			{ RUNTIME_VERSION_1_10_120, 0x00DA60E0 },
			{ RUNTIME_VERSION_1_10_114, 0x00DA60E0 },
			{ RUNTIME_VERSION_1_10_111, 0x00DA60E0 },
			{ RUNTIME_VERSION_1_10_106, 0x00DA60E0 },
			{ RUNTIME_VERSION_1_10_98, 0x00DA60E0 },
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
			{ RUNTIME_VERSION_1_10_120, 0x00D79D70 },
			{ RUNTIME_VERSION_1_10_114, 0x00D79D70 },
			{ RUNTIME_VERSION_1_10_111, 0x00D79D70 },
			{ RUNTIME_VERSION_1_10_106, 0x00D79D70 },
			{ RUNTIME_VERSION_1_10_98, 0x00D79D70 },
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
			{ RUNTIME_VERSION_1_10_120, 0x013FB5E0 },
			{ RUNTIME_VERSION_1_10_114, 0x013FB5E0 },
			{ RUNTIME_VERSION_1_10_111, 0x013FB5E0 },
			{ RUNTIME_VERSION_1_10_106, 0x013FB5E0 },
			{ RUNTIME_VERSION_1_10_98, 0x013FB5E0 },
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
			{ RUNTIME_VERSION_1_10_120, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_114, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_111, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_106, 0x05ADD2C8 },
			{ RUNTIME_VERSION_1_10_98, 0x05ADD2C8 },
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
			{ RUNTIME_VERSION_1_10_120, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_114, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_111, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_106, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_98, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_89, 0x01B12B20 },
			{ RUNTIME_VERSION_1_10_82, 0x01B12AC0 },
			{ RUNTIME_VERSION_1_10_75, 0x01B12AC0 },
			{ RUNTIME_VERSION_1_10_64, 0x01B12B00 },
			{ RUNTIME_VERSION_1_10_50, 0x01B126E0 },
			{ RUNTIME_VERSION_1_10_40, 0x01B12620 },
		}, "40 53 48 83 EC 20 8B D9 83 F9 01");
	GetRandomPercent2 = RVA <_GetRandomPercent2>(
		"GetRandomPercent2", {
			{ RUNTIME_VERSION_1_10_120, 0x01B12C00 },
			{ RUNTIME_VERSION_1_10_114, 0x01B12C00 },
			{ RUNTIME_VERSION_1_10_111, 0x01B12C00 },
			{ RUNTIME_VERSION_1_10_106, 0x01B12C00 },
			{ RUNTIME_VERSION_1_10_98, 0x01B12C00 },
			{ RUNTIME_VERSION_1_10_89, 0x01B12BC0 },
			{ RUNTIME_VERSION_1_10_82, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_75, 0x01B12B60 },
			{ RUNTIME_VERSION_1_10_64, 0x01B12BA0 },
			{ RUNTIME_VERSION_1_10_50, 0x01B12780 },
			{ RUNTIME_VERSION_1_10_40, 0x01B126C0 },
		}, "48 89 5C 24 08 57 48 83 EC 20 8B DA 8B F9");
	SetPerkPoints_int = RVA <_SetPerkPoints_int>(
		"SetPerkPoints_int", {
			{ RUNTIME_VERSION_1_10_120, 0x00EB8A80 },
			{ RUNTIME_VERSION_1_10_114, 0x00EB8A80 },
			{ RUNTIME_VERSION_1_10_111, 0x00EB8A80 },
			{ RUNTIME_VERSION_1_10_106, 0x00EB8A80 },
			{ RUNTIME_VERSION_1_10_98, 0x00EB8A80 },
			{ RUNTIME_VERSION_1_10_89, 0x00EB8A40 },
			{ RUNTIME_VERSION_1_10_82, 0x00EB89E0 },
			{ RUNTIME_VERSION_1_10_75, 0x00EB89E0 },
			{ RUNTIME_VERSION_1_10_64, 0x00EB8A20 },
			{ RUNTIME_VERSION_1_10_50, 0x0EB8600 },
		}, "48 83 EC 28 88 91 F1 0C 00 00");
	LevelupMenuProcessMessage = RVA <_LevelupMenuProcessMessage>(
		"LevelupMenuProcessMessage", {
			{ RUNTIME_VERSION_1_10_120, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_114, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_111, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_106, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_98, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_89, 0x00B383C0 },
			{ RUNTIME_VERSION_1_10_82, 0x00B38360 },
			{ RUNTIME_VERSION_1_10_75, 0x00B38360 },
			{ RUNTIME_VERSION_1_10_64, 0x00B38360 },
			{ RUNTIME_VERSION_1_10_50, 0x0B38360 },
		}, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B F1 8B 4A 10");
	LevelupMenuPlayPerkSound = RVA <_LevelupMenuPlayPerkSound>(
		"LevelupMenuPlayPerkSound", {
			{ RUNTIME_VERSION_1_10_120, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_114, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_111, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_106, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_98, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_89, 0x00B397B0 },
			{ RUNTIME_VERSION_1_10_82, 0x00B39750 },
			{ RUNTIME_VERSION_1_10_75, 0x00B39750 },
			{ RUNTIME_VERSION_1_10_64, 0x00B39750 },
			{ RUNTIME_VERSION_1_10_50, 0x0B39750 },
		}, "48 89 5C 24 08 57 48 83 EC 30 48 8B F9 8B CA 33 DB E8 ? ? ? ? 48 85 C0 74 ? 80 78 1A 5F 75 ? 48 8B 98 88 00 00 00 48 81 C7 80 01 00 00");
	LevelupMenuStopPerkSound = RVA <_LevelupMenuStopPerkSound>(
		"LevelupMenuStopPerkSound", {
			{ RUNTIME_VERSION_1_10_120, 0x01AC7FF0 },
			{ RUNTIME_VERSION_1_10_114, 0x01AC7FF0 },
			{ RUNTIME_VERSION_1_10_111, 0x01AC7FF0 },
			{ RUNTIME_VERSION_1_10_106, 0x01AC7FF0 },
			{ RUNTIME_VERSION_1_10_98, 0x01AC7FF0 },
			{ RUNTIME_VERSION_1_10_89, 0x01AC7FB0 },
			{ RUNTIME_VERSION_1_10_82, 0x01AC7F50 },
			{ RUNTIME_VERSION_1_10_75, 0x01AC7F50 },
			{ RUNTIME_VERSION_1_10_64, 0x01AC7F90 },
			{ RUNTIME_VERSION_1_10_50, 0x01AC7B70 },
		}, "40 53 48 83 EC 20 8B 19 83 FB FF 74 ? C6 41 05 02");
	g_PipboyDataManager = RVA <PipboyDataManager*>(
		"g_PipboyDataManager", {
			{ RUNTIME_VERSION_1_10_120, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_114, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_111, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_106, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_98, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_89, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_82, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_75, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_64, 0x05909B70 },
			{ RUNTIME_VERSION_1_10_50, 0x05908B70 },

		}, "48 8B 0D ? ? ? ? 48 8D 44 24 48 48 8D 54 24 20 48 89 44 24 20 48 8D 44 24 50 48 81 C1 E8 08 00 00 ", 0, 3, 7);
	GetSoundByName = RVA <_GetSoundByName>(
		"_GetSoundByName", {
			{ RUNTIME_VERSION_1_10_120, 0x0082F5E0 },
			{ RUNTIME_VERSION_1_10_114, 0x0082F5E0 },
			{ RUNTIME_VERSION_1_10_111, 0x0082F5E0 },
			{ RUNTIME_VERSION_1_10_106, 0x0082F5E0 },
		}, "E8 ? ? ? ? 48 85 C0 74 ? C7 44 24 68 FF FF FF FF", 0, 1, 5);
	LevelupMenuPlaySound_funk1 = RVA <_LevelupMenuPlaySound_funk1>(
		"_LevelupMenuPlaySound_funk1", {
			{ RUNTIME_VERSION_1_10_120, 0x01ACA4B0 },
			{ RUNTIME_VERSION_1_10_114, 0x01ACA4B0 },
			{ RUNTIME_VERSION_1_10_111, 0x01ACA4B0 },
			{ RUNTIME_VERSION_1_10_106, 0x01ACA4B0 },
		}, "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 81 EC A0 00 00 00 44 8B 0D ? ? ? ?");
	LevelupMenuPlaySound_funk2 = RVA <_LevelupMenuPlaySound_funk2>(
		"_LevelupMenuPlaySound_funk2", {
			{ RUNTIME_VERSION_1_10_120, 0x01AC7F20 },
			{ RUNTIME_VERSION_1_10_114, 0x01AC7F20 },
			{ RUNTIME_VERSION_1_10_111, 0x01AC7F20 },
			{ RUNTIME_VERSION_1_10_106, 0x01AC7F20 },
		}, "40 53 48 83 EC 20 8B 19 83 FB FF 74 ? C6 41 05 01");
	LevelupMenuPlaySound_var1 = RVA <void*>(
		"LevelupMenuPlaySound_var1", {
			{ RUNTIME_VERSION_1_10_120, 0x05B46208 },
			{ RUNTIME_VERSION_1_10_114, 0x05B46208 },
			{ RUNTIME_VERSION_1_10_111, 0x05B46208 },
			{ RUNTIME_VERSION_1_10_106, 0x05B46208 },
		}, "48 8B 1D ? ? ? ? 48 8D 4C 24 40 45 33 C0", 0, 3, 7);
	//RelocPtr <PipboyDataManager*> g_PipboyDataManager(0x05908B70);
}

void InitUIManager()
{
	UI_AddMessage = RVA <_UI_AddMessage>(
		"UI_AddMessage", {
			{ RUNTIME_VERSION_1_10_120, 0x0204CA70 },
			{ RUNTIME_VERSION_1_10_114, 0x0204CA70 },
			{ RUNTIME_VERSION_1_10_111, 0x0204CA70 },
			{ RUNTIME_VERSION_1_10_106, 0x0204CA70 },
			{ RUNTIME_VERSION_1_10_98, 0x0204CA70 },
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
			{ RUNTIME_VERSION_1_10_120, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_114, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_111, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_106, 0x05909B48 },
			{ RUNTIME_VERSION_1_10_98, 0x05909B48 },
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
			{ RUNTIME_VERSION_1_10_120, 0x00B7B8A0 },
			{ RUNTIME_VERSION_1_10_114, 0x00B7B8A0 },
			{ RUNTIME_VERSION_1_10_111, 0x00B7B8A0 },
			{ RUNTIME_VERSION_1_10_106, 0x00B7B8A0 },
			{ RUNTIME_VERSION_1_10_98, 0x00B7B8A0 },
			{ RUNTIME_VERSION_1_10_89, 0x00B7B860 },
			{ RUNTIME_VERSION_1_10_82, 0x00B7B800 },
			{ RUNTIME_VERSION_1_10_75, 0x00B7B800 },
			{ RUNTIME_VERSION_1_10_50, 0x0B7B420 },
		}, "48 83 EC 28 44 8B 42 10 41 FF C8 41 83 F8 01");
	g_multiActivateManager = RVA <MultiActivateManager*>(
		"g_multiActivateManager", {
			{ RUNTIME_VERSION_1_10_120, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_114, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_111, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_106, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_98, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_89, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_82, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_75, 0x05A9EB50 },
			{ RUNTIME_VERSION_1_10_50, 0x05A9DB50 },
		}, "48 8B 0D ? ? ? ? 48 8D 95 80 03 00 00", 0, 3, 7);
	commandTargetCompanionRef = RVA <UInt32*>(
		"commandTargetCompanionRef", {
			{ RUNTIME_VERSION_1_10_120, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_114, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_111, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_106, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_98, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_89, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_82, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_75, 0x05A9909C },
			{ RUNTIME_VERSION_1_10_50, 0x05A9909C },
		}, "48 89 7C 24 38 48 C7 44 24 20 00 00 00 00 4C 89 74 24 30", -7, 3, 7);
	CompanionListenerUnk03 = RVA <_CompanionListenerUnk03>(
		"CompanionListenerUnk03", {
			{ RUNTIME_VERSION_1_10_120, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_114, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_111, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_106, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_98, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_89, 0x009FFAC0 },
			{ RUNTIME_VERSION_1_10_82, 0x009FFA60 },
			{ RUNTIME_VERSION_1_10_75, 0x009FFA60 },
			{ RUNTIME_VERSION_1_10_50, 0x09FFA60 },
		}, "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 50 8B FA");
	EquipItem_int = RVA <_EquipItem_int>(
		"EquipItem_int", {
			{ RUNTIME_VERSION_1_10_120, 0x00E1BBB0 },
			{ RUNTIME_VERSION_1_10_114, 0x00E1BBB0 },
			{ RUNTIME_VERSION_1_10_111, 0x00E1BBB0 },
			{ RUNTIME_VERSION_1_10_106, 0x00E1BBB0 },
			{ RUNTIME_VERSION_1_10_98, 0x00E1BBB0 },
			{ RUNTIME_VERSION_1_10_89, 0x00E1BB70 },
			{ RUNTIME_VERSION_1_10_82, 0x00E1BB10 },
			{ RUNTIME_VERSION_1_10_75, 0x00E1BB10 },
			{ RUNTIME_VERSION_1_10_50, 0x00E1B730 },
		}, "4C 8B DC 49 89 53 10 55 56 41 54 41 57");
	UnEquipItem_int = RVA <_UnEquipItem_int>(
		"UnEquipItem_int", {
			{ RUNTIME_VERSION_1_10_120, 0x00E1BF90 },
			{ RUNTIME_VERSION_1_10_114, 0x00E1BF90 },
			{ RUNTIME_VERSION_1_10_111, 0x00E1BF90 },
			{ RUNTIME_VERSION_1_10_106, 0x00E1BF90 },
			{ RUNTIME_VERSION_1_10_98, 0x00E1BF90 },
			{ RUNTIME_VERSION_1_10_89, 0x00E1BF50 },
			{ RUNTIME_VERSION_1_10_82, 0x00E1BEF0 },
			{ RUNTIME_VERSION_1_10_75, 0x00E1BEF0 },
			{ RUNTIME_VERSION_1_10_50, 0x00E1BB10 },
		}, "48 8B C4 48 89 58 18 55 57 41 56 48 83 EC 70");
	unk_itemManager = RVA <void*>(
		"unk_itemManager", {
			{ RUNTIME_VERSION_1_10_120, 0x05A10618 },
			{ RUNTIME_VERSION_1_10_114, 0x05A10618 },
			{ RUNTIME_VERSION_1_10_111, 0x05A10618 },
			{ RUNTIME_VERSION_1_10_106, 0x05A10618 },
			{ RUNTIME_VERSION_1_10_98, 0x05A10618 },
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

void tracePipboyPrimitiveValueUChar(PipboyPrimitiveValue<UInt8>* val)
{
	_MESSAGE("type:    uchar\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
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

void tracePipboyPrimitiveThrottledValueFloat(PipboyPrimitiveThrottledValue<float>* val)
{
	_MESSAGE("type:   float\t\tvalue: %16f\t\thex: 0x%016I64X", val->value, val->value);
	//DumpClass(val, 0x70 / 8);
};

void tracePipboyPrimitiveThrottledValueBool(PipboyPrimitiveThrottledValue<bool>* val)
{
	_MESSAGE("type:    bool\t\tvalue: %16s", val->value ? "true" : "false");
	//DumpClass(val, 0x70/8);
};

void tracePipboyPrimitiveThrottledValueUChar(PipboyPrimitiveThrottledValue<UInt8>* val)
{
	_MESSAGE("type:    uchar\t\tvalue: %16u\t\thex: 0x%016I64X", val->value, val->value);
	//DumpClass(val, 0x70 / 8);
};

void tracePipboyValue(PipboyValue* pv)
{

	UInt64 vtbladdress = *reinterpret_cast<UInt64*>((uintptr_t)pv) - RelocationManager::s_baseAddr;
	//_MESSAGE("%s 0x%016I64X", GetObjectClassName(pv), vtbladdress);
	switch (vtbladdress)
	{
	case 0x2D545B0:	// BSFixedStringCS
		tracePipboyPrimitiveValueBSFixedStringCS((PipboyPrimitiveValue<BSFixedString>*)pv);
		break;
	case 0x2D54658:	// uint
		tracePipboyPrimitiveValueUInt((PipboyPrimitiveValue<UInt32>*)pv);
		break;
	case 0x2D55620:	// uchar
		tracePipboyPrimitiveValueUChar((PipboyPrimitiveValue<UInt8>*)pv);
		break;
	case 0x2D55988:	// Throttled uchar
		tracePipboyPrimitiveThrottledValueUChar((PipboyPrimitiveThrottledValue<UInt8>*)pv);
		break;
	case 0x2D545E8:	// bool
		tracePipboyPrimitiveValueBool((PipboyPrimitiveValue<bool>*)pv);
		break;
	case 0x2D559D0:	// Throttled bool
		tracePipboyPrimitiveThrottledValueBool((PipboyPrimitiveThrottledValue<bool>*)pv);
		break;
	case 0x2D54620:	// int
		tracePipboyPrimitiveValueInt((PipboyPrimitiveValue<SInt32>*)pv);
		break;
	case 0x2D54690:	// float
		tracePipboyPrimitiveValueFloat((PipboyPrimitiveValue<float>*)pv);
		break;
	case 0x2D55940:	// Throttled float
		tracePipboyPrimitiveThrottledValueFloat((PipboyPrimitiveThrottledValue<float>*)pv);
		break;
	case 0x2D53FD8:	// PipboyArray
		tracePipboyArray((PipboyArray*)pv);
		break;
	case 0x2D55B68:	// PipboyObject
		tracePipboyObject((PipboyObject*)pv);
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

void tracePipboyObject(PipboyObject* obj)
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


RelocPtr <ItemMenuDataManager*> g_itemMenuDataMgr(0x0590DA00);
RelocAddr <_getInventoryItemByHandleID> getInventoryItemByHandleID(0x001A3650);

BGSInventoryItem* getInventoryItemByIndex(UInt32 index)
{
	BSFixedString str = BSFixedString("HandleID");
	PipboyObject::PipboyTableItem *ti = (*g_PipboyDataManager)->inventoryData.inventoryObjects[index]->table.Find(&str);
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

class traceGFxValue_VisitMembers : public GFxValue::ObjectInterface::ObjVisitor
{
public:
	virtual void Visit(const char * member, GFxValue * value) override
	{
		_MESSAGE("member name: \t\t%s", member);
		traceGFxValue(value);
	}
};

void traceGFxValueInt(GFxValue* fxv)
{
	_MESSAGE("type:     int\t\tvalue: %16i\t\thex: 0x%016I64X", fxv->GetInt(), fxv->GetInt());
}

void traceGFxValueUInt(GFxValue* fxv)
{
	_MESSAGE("type:     uint\t\tvalue: %16u\t\thex: 0x%016I64X", fxv->GetUInt(), fxv->GetUInt());
}

void traceGFxValueFloat(GFxValue* fxv)
{
	_MESSAGE("type:   float\t\tvalue: %16f\t\thex: 0x%016I64X", fxv->GetNumber(), fxv->GetNumber());
};

void traceGFxValueBool(GFxValue* fxv)
{
	_MESSAGE("type:    bool\t\tvalue: %16s", fxv->GetBool() ? "true" : "false");
};

void traceGFxValueString(GFxValue* fxv)
{
	_MESSAGE("type:  string\t\tvalue: %16s", fxv->GetString());
};

void traceGFxValueArray(GFxValue* fxv)
{
	_MESSAGE("type:  array\t\titem count:%i", fxv->GetArraySize());

	gLog.Indent();
	for (size_t i = 0; i < fxv->GetArraySize(); i++)
	{
		GFxValue item;
		fxv->GetElement(i, &item);
		traceGFxValue(&item);
	};
	gLog.Outdent();
}

void traceGFxValueObject(GFxValue* fxv)
{
	_MESSAGE("type:  object");
	gLog.Indent();
	traceGFxValue_VisitMembers dm;
	fxv->VisitMembers(&dm);
	gLog.Outdent();
}



void traceGFxValue(GFxValue* fxv)
{
	int type = fxv->type & 0x8F;

	switch (type)
	{
	case GFxValue::kType_Undefined:
		_MESSAGE("type:  kType_Undefined");
		break;
	case GFxValue::kType_Null:
		_MESSAGE("type:  kType_Null");
		break;
	case GFxValue::kType_Bool:
		traceGFxValueBool(fxv);
		break;
	case GFxValue::kType_Int:
		traceGFxValueInt(fxv);
		break;
	case GFxValue::kType_UInt:
		traceGFxValueUInt(fxv);
		break;
	case GFxValue::kType_Number:
		traceGFxValueFloat(fxv);
		break;
	case GFxValue::kType_String:
		traceGFxValueString(fxv);
		break;
	case GFxValue::kType_Unknown7:
		_MESSAGE("type:  kType_Unknown7");
		break;
	case GFxValue::kType_Object:
		traceGFxValueObject(fxv);
		break;
	case GFxValue::kType_Array:
		traceGFxValueArray(fxv);
		break;
	case GFxValue::kType_DisplayObject:
		traceGFxValueObject(fxv);
		break;
	case GFxValue::kType_Function:
		_MESSAGE("type:  kType_Function");
		break;
	default:
		break;
	}
};

RelocAddr <uintptr_t> s_ExtraPoisonVtbl(0x02C7C468);

ExtraPoison* ExtraPoison::Create(AlchemyItem* poison)
{
	ExtraPoison* pPoison = (ExtraPoison*)BSExtraData::Create(sizeof(ExtraPoison), s_ExtraPoisonVtbl.GetUIntPtr());
	pPoison->type = kExtraData_Poison;
	pPoison->poison = poison;
	return pPoison;
}

void DumpClassX(void * theClassPtr, UInt64 nIntsToDump)
{
	UInt64* basePtr = (UInt64*)theClassPtr;

	_MESSAGE("DumpClassX");

	gLog.Indent();

	if (!theClassPtr) return;
	for (UInt64 ix = 0; ix < nIntsToDump; ix++) {
		UInt64* curPtr = basePtr + ix;
		const char* curPtrName = NULL;
		UInt64 otherPtr = 0;
		float otherFloat1 = 0.0;
		float otherFloat2 = 0.0;
		const char* otherPtrName = NULL;
		if (curPtr) {
			curPtrName = GetObjectClassName((void*)curPtr);

			__try
			{
				otherPtr = *curPtr;
				UInt32 lowerFloat = otherPtr & 0xFFFFFFFF;
				UInt32 upperFloat = (otherPtr >> 32) & 0xFFFFFFFF;
				otherFloat1 = *(float*)&lowerFloat;
				otherFloat2 = *(float*)&upperFloat;
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				//
			}

			if (otherPtr) {
				otherPtrName = GetObjectClassName((void*)otherPtr);
			}
		}

		_MESSAGE("%3d +%03X ptr: 0x%016I64X: %32s *ptr: 0x%016I64x | %f, %f: %32s", ix, ix * 8, curPtr - RelocationManager::s_baseAddr, curPtrName, otherPtr, otherFloat2, otherFloat1, otherPtrName);
	}

	gLog.Outdent();
}


RelocAddr<_CalcInstanceData>			CalcInstanceData(0x2F7A30);


bool GetScriptVariableValue(VMIdentifier* id, const char* varName, VMValue * outVal)
{
	if (id->m_typeInfo->memberData.unk00 == 3)
	{
		for (UInt32 i = 0; i < id->m_typeInfo->memberData.numMembers; ++i)
		{
			if (!_stricmp(id->m_typeInfo->properties->defs[i].propertyName.c_str(), varName))
			{
				return (*g_gameVM)->m_virtualMachine->GetPropertyValueByIndex(&id, i, outVal);
			}
		}
	}
	return false;
}


void traceVMValueType(UInt64 val)
{
	switch (val)
	{
	case VMValue::kType_None:
		_MESSAGE("VMValue type: kType_None");
		break;
	case VMValue::kType_Identifier:
		_MESSAGE("VMValue type: kType_Identifier");
		break;
	case VMValue::kType_String:
		_MESSAGE("VMValue type: kType_String");
		break;
	case VMValue::kType_Int:
		_MESSAGE("VMValue type: kType_Int");
		break;
	case VMValue::kType_Float:
		_MESSAGE("VMValue type: kType_Float");
		break;
	case VMValue::kType_Bool:
		_MESSAGE("VMValue type: kType_Bool");
		break;
	case VMValue::kType_Variable:
		_MESSAGE("VMValue type: kType_Variable");
		break;
	case VMValue::kType_Struct:
		_MESSAGE("VMValue type: kType_Variable");
		break;
	case VMValue::kType_IdentifierArray:
		_MESSAGE("VMValue type: kType_IdentifierArray");
		break;
	case VMValue::kType_StringArray:
		_MESSAGE("VMValue type: kType_StringArray");
		break;
	case VMValue::kType_IntArray:
		_MESSAGE("VMValue type: kType_IntArray");
		break;
	case VMValue::kType_FloatArray:
		_MESSAGE("VMValue type: kType_FloatArray");
		break;
	case VMValue::kType_BoolArray:
		_MESSAGE("VMValue type: kType_BoolArray");
		break;
	case VMValue::kType_VariableArray:
		_MESSAGE("VMValue type: kType_VariableArray");
		break;
	case VMValue::kType_StructArray:
		_MESSAGE("VMValue type: kType_StructArray");
		break;
	default:
		break;
	}
}

void traceVMValue(VMValue* val)
{
	if (val->IsComplexArrayType())
	{
		_MESSAGE("VMValue IsComplexArrayType");
	}
	else if (val->IsComplexType())
	{
		_MESSAGE("VMValue IsComplexType");
		traceVMValueType(val->type.id->GetType());
		//DumpClass(val->data.p, 10);
		//DumpClass(val->type.id, 0x20 / 8);
	}
	else
	{
		traceVMValueType(val->type.value);
	}
}