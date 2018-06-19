#include "main.h"

std::string mName = "ESH";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEMessagingInterface		*g_messaging = NULL;
F4SEPapyrusInterface		*g_papyrus = NULL;
F4SEScaleformInterface		*g_scaleform = NULL;

std::vector<WeapStruct> expArray1;
std::vector<WeapStruct> expArray2;

struct InitialSettings
{
	std::string		form;
	int				pos;
	int				list;
};

std::vector<InitialSettings> initsets = {};

int iEquipNext = 1;

WeapToEquip equippedExplosive;
std::pair<UInt32, SInt32> equippedExplosiveListPosition;

#define ReadSetting(key)	\
	tempvalue = GetPrivateProfileInt("Lists", #key, -1, "./Data/MCM/Settings/ESH.ini"); \
	if (tempvalue>-1)\
	{\
		key = tempvalue;\
	}\
	_MESSAGE("%s=%i", #key, key);

#define ReadSettingMain(key)	\
	tempvalue = GetPrivateProfileInt("Main", #key, -1, "./Data/MCM/Settings/ESH.ini"); \
	if (tempvalue>-1)\
	{\
		key = tempvalue;\
	}\
	_MESSAGE("%s=%i", #key, key);

void ReadINIs(std::vector<WIN32_FIND_DATA>* arr)
{
	char* modSettingsDirectory = "Data\\MCM\\Settings\\ESH*.ini";

	HANDLE hFind;
	WIN32_FIND_DATA data;
	hFind = FindFirstFile(modSettingsDirectory, &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			arr->push_back(data);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
}

void ReadSettings()
{
	initsets.clear();
	int tempvalue;

	ReadSettingMain(iEquipNext);

	std::vector<WIN32_FIND_DATA> modSettingFiles;
	ReadINIs(&modSettingFiles);
	for each (auto xx in modSettingFiles)
	{
		std::string fileName = xx.cFileName;
		const char* filePath = "./Data/MCM/Settings/";
		std::string fullPath = filePath + fileName;
		_MESSAGE("%s", fullPath.c_str());
		LPTSTR lpszReturnBuffer;
		lpszReturnBuffer = new TCHAR[8192];
		char* pNextSection = NULL;
		GetPrivateProfileSectionNames(lpszReturnBuffer, 8192, fullPath.c_str());
		pNextSection = lpszReturnBuffer;
		InitialSettings newInitSet = {};
		if (*pNextSection != 0x00)
		{
			newInitSet.form = pNextSection;
			newInitSet.pos = GetPrivateProfileInt(pNextSection, "iPos", 0, fullPath.c_str());
			newInitSet.list = GetPrivateProfileInt(pNextSection, "iList", 0, fullPath.c_str());
			initsets.push_back(newInitSet);
		}

		while (*pNextSection != 0x00)
		{
			pNextSection = pNextSection + strlen(pNextSection) + 1;
			if (*pNextSection != 0x00)
			{
				newInitSet.form = pNextSection;
				newInitSet.pos = GetPrivateProfileInt(pNextSection, "iPos", 0, fullPath.c_str());
				newInitSet.list = GetPrivateProfileInt(pNextSection, "iList", 0, fullPath.c_str());
				initsets.push_back(newInitSet);
			}
		}
		_MESSAGE("num sections %i", initsets.size());
	}

	for each(auto xx in initsets)
	{
		_MESSAGE("%s - %i - %i", xx.form.c_str(), xx.list, xx.pos);
	}
}

#include <algorithm>

void filllists()
{
	expArray1.clear();
	expArray2.clear();
	for each(auto xx in initsets)
	{
		TESObjectWEAP* weap = DYNAMIC_CAST(GetFormFromIdentifier(xx.form), TESForm, TESObjectWEAP);
		if (weap)
		{
			if (xx.list == 1)
			{
				expArray1.push_back(WeapStruct(weap,xx.pos));
			}
			else if (xx.list == 2)
			{
				expArray2.push_back(WeapStruct(weap, xx.pos));
			}
		}
		else _MESSAGE("%s is not a weapon form", xx.form.c_str());
	}

	_MESSAGE("first list length: %i", expArray1.size());
	std::sort(expArray1.begin(), expArray1.end());

	_MESSAGE("second list length: %i", expArray2.size());
	std::sort(expArray2.begin(), expArray2.end());
}

void FindWeaponToEquip(UInt32 list, SInt32 startIdx)
{
	int i = 0;// counter
	int j;	// size
	if (list == 1)
	{
		j = expArray1.size();
	}
	else
	{
		j = expArray2.size();
	}
	int k = startIdx;// checked index
	while (i<j)
	{
		k += 1;
		if (k>(j-1))
		{
			k -= j;
		}
		if (list == 1 && GetItemCount((*g_player), expArray1[k].weap) > 0 && expArray1[k].weap != equippedExplosive.weap)
		{
			_MESSAGE("nextitem found at list 1 slot %i", k);
			WeapToEquip weap;
			weap.weap = expArray1[k].weap;
			weap.instance = nullptr;
			EquipItem_int(*unk_itemManager, (*g_player), &weap, 0, 1, nullptr, 1, false, 1, 0, false);
			return;
		}
		else if (list == 2 && GetItemCount((*g_player), expArray2[k].weap) > 0 && expArray2[k].weap != equippedExplosive.weap)
		{
			_MESSAGE("nextitem found at list 2 slot %i", k);
			WeapToEquip weap;
			weap.weap = expArray2[k].weap;
			weap.instance = nullptr;
			EquipItem_int(*unk_itemManager, (*g_player), &weap, 0, 1, nullptr, 1, false, 1, 0, false);
			return;
		}
		i += 1;
	}
}

EventResult	TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher)
{
	_DMESSAGE("ESH TESLoadGameEvent recieved");
	REGISTER_EVENT(TESEquipEvent, g_ESH_TESEquipEventSink);
	REGISTER_EVENT(TESContainerChangedEvent, g_ESH_TESContainerChangedEventSink);
	checkEquippedExplosive();
	return kEvent_Continue;
}

void checkEquippedExplosiveListPosition()
{
	for (size_t i = 0; i < expArray1.size(); i++)
	{
		if (expArray1[i].weap == equippedExplosive.weap)
		{
			equippedExplosiveListPosition.first = 1;
			equippedExplosiveListPosition.second = i;
			_MESSAGE("equipped explosive found in first list at %i pos", i);
			return;
		}
	}
	for (size_t i = 0; i < expArray2.size(); i++)
	{
		if (expArray2[i].weap == equippedExplosive.weap)
		{
			equippedExplosiveListPosition.first = 2;
			equippedExplosiveListPosition.second = i;
			_MESSAGE("equipped explosive found in second list at %i pos", i);
			return;
		}
	}
}

void checkEquippedExplosive()
{
	Actor* playerref = *g_player;
	playerref->inventoryList->inventoryLock.Lock();

	equippedExplosive.weap = nullptr;
	equippedExplosive.instance = nullptr;
	equippedExplosiveListPosition.first = 0;
	equippedExplosiveListPosition.second = 0;

	for (size_t i = 0; i < playerref->inventoryList->items.count; i++)
	{
		TESForm* form = playerref->inventoryList->items[i].form;
		BGSInventoryItem::Stack* stack = playerref->inventoryList->items[i].stack;
		if (form->formType == kFormType_WEAP)
		{
			TESObjectWEAP* weap = (TESObjectWEAP*)form;

			stack->Visit([&](BGSInventoryItem::Stack * stackx)
			{
				if (stackx->flags & 7)
				{
					ExtraDataList * stackDataList = stackx->extraData;
					TESObjectWEAP::InstanceData* weapData = &weap->weapData;
					if (stackDataList) {
						ExtraInstanceData * eid = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
						if (eid)
						{
							weapData = (TESObjectWEAP::InstanceData*)eid->instanceData;
						}
					}
					if (weapData->unk137 == kWeaponAnimationType_Grenade || weapData->unk137 == kWeaponAnimationType_Mine)
					{
						_DMESSAGE("found equipped explosive");
						equippedExplosive.weap = weap;
						equippedExplosive.instance = weapData;
						checkEquippedExplosiveListPosition();
					}
				}
				return true;
			});
		}
	}

	playerref->inventoryList->inventoryLock.Release();
}

ESH_TESEquipEventSink g_ESH_TESEquipEventSink;

EventResult	ESH_TESEquipEventSink::ReceiveEvent(TESEquipEvent * evn, void * dispatcher)
{
	_DMESSAGE("ESH TESEquipEvent recieved: ");
	if (evn->status && LookupFormByID(evn->baseFormID)->formType == kFormType_WEAP)
	{
		checkEquippedExplosive();
	}
	return kEvent_Continue;
}

ESH_TESContainerChangedEventSink g_ESH_TESContainerChangedEventSink;

EventResult	ESH_TESContainerChangedEventSink::ReceiveEvent(TESContainerChangedEvent * evn, void * dispatcher)
{
	_DMESSAGE("ESH TESContainerChangedEvent recieved: ");
	if (evn->sourceContainerFormID == 0x14 && evn->targetContainerFormID == 0 && evn->itemFormID == equippedExplosive.weap->formID && GetItemCount(*g_player, LookupFormByID(evn->itemFormID)) == evn->count)
	{
		_MESSAGE("last item removed");
		if (iEquipNext)
		{
			int lastList = equippedExplosiveListPosition.first;
			int lastIdx = equippedExplosiveListPosition.second;
			equippedExplosiveListPosition.first = 0;
			equippedExplosiveListPosition.second = 0;
			FindWeaponToEquip(lastList, lastIdx);
			checkEquippedExplosive();
		}
	}

	return kEvent_Continue;
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		filllists();
		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
		break;

	}
}

#include "f4se/PapyrusNativeFunctions.h"

void Papyrus_Switch(StaticFunctionTag*, SInt32 listNum)
{
	_MESSAGE("Papyrus_Switch");
	switch (listNum)
	{
	case 1:
		_MESSAGE("switch 1");
		if (equippedExplosiveListPosition.first != 1)
		{
			FindWeaponToEquip(1, -1);
		}
		else
		{
			FindWeaponToEquip(1, equippedExplosiveListPosition.second);
		}
		break;
	case 2:
		_MESSAGE("switch 2");
		if (equippedExplosiveListPosition.first != 2)
		{
			FindWeaponToEquip(2, -1);
		}
		else
		{
			FindWeaponToEquip(2, equippedExplosiveListPosition.second);
		}
		break;
	default:
		break;
	}
	return;
}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, SInt32>("Switch", "ESH:ESH", Papyrus_Switch, vm));
	return true;
}

class Scaleform_ChangeSetting : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		switch (args->args[0].GetUInt())
		{
		case 9000:
			iEquipNext = args->args[1].GetUInt();
			break;
		default:
			break;
		}
	}
};

class Scaleform_UpdateLists : public GFxFunctionHandler
{
public:


	virtual void	Invoke(Args * args) {
		ReadSettings();
		filllists();
		checkEquippedExplosive();
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{
	RegisterFunction<Scaleform_ChangeSetting>(f4se_root, view->movieRoot, "ChangeSetting");
	RegisterFunction<Scaleform_UpdateLists>(f4se_root, view->movieRoot, "UpdateLists");
	return true;
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\"+ mName +".log").c_str());

		logMessage("query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		mName.c_str();
		info->version =		mVer;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		// Check game version
		if (f4se->runtimeVersion != CURRENT_RUNTIME_VERSION) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.89 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.89). \n" + mName + " will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		// get the papyrus interface and query its version
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus)
		{
			_MESSAGE("couldn't get papyrus interface");
			return false;
		}
		else {
			_MESSAGE("got papyrus interface");
		}
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}
		else {
			_MESSAGE("got scaleform interface");
		}
		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			_MESSAGE("couldn't get messaging interface");
			return false;
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		if (g_scaleform)
		{
			g_scaleform->Register("ESH", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}
		InitAddresses();
		TESEquipEvent_Dispatcher_Init();						// inv4
		TESContainerChangedEvent_Dispatcher_Init();				// inv3
		InitCWAddresses();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		ReadSettings();
		return true;
	}

};
