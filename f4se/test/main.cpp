#include "main.h"

// off_142EDBFF0 GFxMovieRoot vftable

std::string mName = "test";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"
#include "gfxfunctions.h"

F4SEScaleformInterface		*g_scaleform = NULL;
F4SEPapyrusInterface		*g_papyrus = NULL;
F4SEMessagingInterface		*g_messaging = NULL;


typedef bool(*_IsWaiting)(Actor* actor);

RelocAddr <_IsWaiting> IsWaiting(0x00D72700);

// 0x0C0FDD0 pipboyitemcard update

// 590DA80  BGSInventoryItemEvent event dispatcher

typedef void(*_ContainerMenuInvoke)(ContainerMenuBase* menu, GFxFunctionHandler::Args* args);

RelocAddr <_ContainerMenuInvoke> ContainerMenuInvoke(0x00B0A280);
_ContainerMenuInvoke ContainerMenuInvoke_Original;

class PipboyMenu;
typedef void(*_PipboyMenuInvoke)(PipboyMenu* menu, GFxFunctionHandler::Args* args);

RelocAddr <_PipboyMenuInvoke> PipboyMenuInvoke(0x00B93F60);
_PipboyMenuInvoke PipboyMenuInvoke_Original;

BGSDamageType* ConditionDtype;
RelocAddr<void(*)(TESForm *&, InventoryItemStack &, SimpleCollector<DamageInfo>&)> CollectDamageInfo = 0xC0AB50; ///V1.10.106


typedef SInt32(*_CalcDiffRating)(float value1, float value2);
RelocAddr <_CalcDiffRating> CalcDiffRating(0x0C0B630);

struct InvItemStackStruct
{
public:
	BGSInventoryItem *	invItem;
	UInt16				stackID;
};

typedef void(*_PopulateItemCardInfoList)(GFxValue* itemCard, BGSInventoryItem * itemForCard, UInt16 itemForCardstackID, SimpleCollector<InvItemStackStruct>* itemsForCompare);
RelocAddr <_PopulateItemCardInfoList> PopulateItemCardInfoList(0x0AED710);
_PopulateItemCardInfoList PopulateItemCardInfoList_Original;

class Objectinterface_x
{
public:
	void*	unk00;
	GFxMovieView*	view;
	void*	unk10;
};

UInt32 GetMaxCND(TESObjectWEAP::InstanceData* weapData)
{
	if (!weapData) return 0;
	if (weapData->damageTypes)
	{
		for (size_t i = 0; i < (*(weapData->damageTypes)).count; i++)
		{
			BGSDamageType* dt = (*(weapData->damageTypes))[i].damageType;
			if (dt == ConditionDtype)
			{
				return (*(weapData->damageTypes))[i].value;
			}
		}
	}
	return 0;
}

BGSInventoryItem::Stack* GetStackByStackID(BGSInventoryItem * item, UInt16 stackID)
{
	BGSInventoryItem::Stack* stack = item->stack;
	if (!stack) return NULL;
	while (stackID != 0)
	{
		stack = stack->next;
		if (!stack) return NULL;
		stackID--;
	}
	return stack;
}

TBO_InstanceData* GetTBO_InstanceDataFromInventoryItem(BGSInventoryItem * item, UInt16 stackID) // 0x01A61F0
{
	BGSInventoryItem::Stack* stack = item->stack;
	if (!stack) return NULL;
	while (stackID != 0)
	{
		stack = stack->next;
		if (!stack) return NULL;
		stackID--;
	}
	if (stack)
	{
		ExtraInstanceData * eid = DYNAMIC_CAST(stack->extraData->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
		if (eid) return eid->instanceData;
	}
	return NULL;
}

float GetHealthFromInventoryItem(BGSInventoryItem * item, UInt16 stackID)
{
	BGSInventoryItem::Stack* stack = item->stack;
	if (!stack) return 0.0;
	while (stackID != 0)
	{
		stack = stack->next;
		if (!stack) return 0.0;
		stackID--;
	}
	if (stack)
	{
		ExtraHealth * eh = DYNAMIC_CAST(stack->extraData->GetByType(kExtraData_Health), BSExtraData, ExtraHealth);
		if (eh) return eh->health;
	}
	return 0.0;
}

void processItemCardInfoList(GFxValue* itemCard, BGSInventoryItem * itemForCard, UInt16 itemForCardstackID, SimpleCollector<InvItemStackStruct>* itemsForCompare)
{
	GFxMovieView* view = ((Objectinterface_x*)itemCard->objectInterface)->view;
	if (!view) return;
	GFxMovieRoot* root = view->movieRoot;
	if (!root) return;
	ObjectInstanceData objInst{ nullptr, nullptr };
	CalcInstanceData(objInst, itemForCard->form, GetTBO_InstanceDataFromInventoryItem(itemForCard, itemForCardstackID));

	if (itemForCard->form->formType == kFormType_WEAP)
	{
		TESObjectWEAP::InstanceData* weapData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(objInst.data, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
		if (!weapData) return;
		UInt32 MaxCNDValue = GetMaxCND(weapData);
		if (!MaxCNDValue) return; // check IsWeaponDegradable
	
		TESObjectWEAP::InstanceData* itemForCompare = nullptr;
		ObjectInstanceData compareInst{ nullptr, nullptr };
		InvItemStackStruct compareItem;
		// get weapon with same animation type from all equipped weapons
		for (size_t i = 0; i < itemsForCompare->itemsArray.count; i++)
		{
			if (itemsForCompare->itemsArray[i].invItem->form->formType == kFormType_WEAP)
			{
				CalcInstanceData(compareInst, itemsForCompare->itemsArray[i].invItem->form, GetTBO_InstanceDataFromInventoryItem(itemsForCompare->itemsArray[i].invItem, itemsForCompare->itemsArray[i].stackID));
				TESObjectWEAP::InstanceData* tempItemForCompare = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(compareInst.data, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
				if (tempItemForCompare->unk137 == weapData->unk137)
				{
					compareItem = itemsForCompare->itemsArray[i];
					itemForCompare = tempItemForCompare;
				}
			}
		}
		UInt32 MaxCNDCompareValue = GetMaxCND(itemForCompare);

		float cndValue = round(100 * GetHealthFromInventoryItem(itemForCard, itemForCardstackID));
		GFxValue cnd;
		root->CreateObject(&cnd);
		RegisterString(&cnd, root, "text", "CND");
		std::string health = std::to_string(int(cndValue)) + "%";
		RegisterString(&cnd, root, "value", health.c_str());
		if (MaxCNDCompareValue)
		{
			float cndCompareValue = round(100 * GetHealthFromInventoryItem(compareItem.invItem, compareItem.stackID));
			RegisterInt(&cnd, "difference", int(cndValue-cndCompareValue));
			RegisterInt(&cnd, "diffRating", CalcDiffRating(cndValue, cndCompareValue));
		}

		itemCard->PushBack(&cnd);

		GFxValue maxCnd;
		root->CreateObject(&maxCnd);
		RegisterString(&maxCnd, root, "text", "MAX CND");
		RegisterString(&maxCnd, root, "value", std::to_string(MaxCNDValue).c_str());
		if (MaxCNDCompareValue)
		{
			RegisterInt(&maxCnd, "difference", int(MaxCNDValue - MaxCNDCompareValue));
			RegisterInt(&maxCnd, "diffRating", CalcDiffRating(MaxCNDValue, MaxCNDCompareValue));
		}
		itemCard->PushBack(&maxCnd);
	}
	else if (itemForCard->form->formType == kFormType_ARMO)
	{

	}
	// etc..
}


void PopulateItemCardInfoList_Hook(GFxValue* itemCard, BGSInventoryItem * itemForCard, UInt16 itemForCardstackID, SimpleCollector<InvItemStackStruct>* itemsForCompare) {
	/*GFxMovieView* view = ((Objectinterface_x*)itemCard->objectInterface)->view;
	if (view)
	{
		IMenu* menu = (*g_ui)->GetMenuByMovie(view);
		ContainerMenuBase* containermenu = DYNAMIC_CAST(menu, IMenu, ContainerMenuBase);
		if (containermenu)
		{
			UInt32 handle = containermenu->targetHandle;
			// do some stuff here
		}
	}*/
	PopulateItemCardInfoList_Original(itemCard, itemForCard, itemForCardstackID, itemsForCompare);
	if ((itemCard->type & 0x8F) == 9)
	{
		processItemCardInfoList(itemCard, itemForCard, itemForCardstackID, itemsForCompare);
	}
	else
	{
		GFxValue ItemCardInfoList;
		itemCard->GetMember("ItemCardInfoList", &ItemCardInfoList);
		processItemCardInfoList(&ItemCardInfoList, itemForCard, itemForCardstackID, itemsForCompare);
	}
}

typedef void(*_ExamineMenu__Invoke)(ExamineMenu* menu, GFxFunctionHandler::Args * args);
RelocAddr <_ExamineMenu__Invoke> ExamineMenu__Invoke_HookTarget(0x2D46160);
_ExamineMenu__Invoke ExamineMenu__Invoke_Original;

typedef SInt32(*_GetInventoryListObjectSelectedIndex)(ExamineMenu* menu);
RelocAddr <_GetInventoryListObjectSelectedIndex> GetInventoryListObjectSelectedIndex(0x0B1B160);
_GetInventoryListObjectSelectedIndex GetInventoryListObjectSelectedIndex_Original;

void SetPlayerNameTest(const char* newName)
{
	typedef void(*_SetPlayerName_int)(TESForm* baseForm, const char* newName);
	RelocAddr <_SetPlayerName_int> SetPlayerName_int(0x00BB9040);
	TESForm* baseForm = (*g_player)->baseForm;
	SetPlayerName_int(baseForm, newName);
	baseForm->MarkChanged(0x20);
}

void ExamineMenu__Invoke_Hook(ExamineMenu* menu, GFxFunctionHandler::Args * args) {
	_MESSAGE("ExamineMenu__Invoke_Hook");
	if (args->optionID == 0)
	{
		DumpClass(menu, 0x810 / 8);
	}


	ExamineMenu__Invoke_Original(menu, args);

	if (args->optionID == 0x17)
	{
	//	DumpClass(menu, 0x810 / 8);
		GFxValue InfoObj;
		menu->ItemCardList_mc.GetMember("InfoObj", &InfoObj);

		//traceGFxValue(&InfoObj);
		_MESSAGE("GetInventoryListObjectSelectedIndex %i", GetInventoryListObjectSelectedIndex(menu));
		DumpClass(&menu->struct370.inventory.entries[GetInventoryListObjectSelectedIndex(menu)],4);

		if (menu->tempInventoryItem.stack)
		{
			ExtraDataList* edl = menu->tempInventoryItem.stack->extraData;
			if (edl)
			{
				BSExtraData* next = edl->m_data;
				while (next)
				{
					_MESSAGE("%s", GetObjectClassName(next));
					next = next->next;
				}
			}
		}
	}
	traceGFxValue(&menu->ItemCardList_mc);

}

typedef UInt8(*_ExamineMenu__DrawNextFrame)(ExamineMenu* menu, void** param2, void** param3);
RelocAddr <_ExamineMenu__DrawNextFrame> ExamineMenu__DrawNextFrame(0x0B17EC0);
_ExamineMenu__DrawNextFrame ExamineMenu__DrawNextFrame_Original;

UInt8 ExamineMenu__DrawNextFrame_Hook(ExamineMenu* menu, void** param2, void** param3) {
	UInt8 result = ExamineMenu__DrawNextFrame_Original(menu, param2, param3);
	GFxValue bIsDirty;
	menu->ItemCardList_mc.GetMember("bIsDirty", &bIsDirty);
	if ((bIsDirty.type & 0x8F) == GFxValue::kType_Bool)
	{
		if (bIsDirty.GetBool())
		{
			_MESSAGE("isdirty");
		}
	}
	return result;
}

void DumpWorkshopEntry(WorkshopEntry* entry)
{
	gLog.Indent();
	for (size_t i = 0; i < entry->entries.count; i++)
	{
		if (entry->entries[i]->recipe)
		{
			_MESSAGE("recipe: %s", entry->entries[i]->object->GetFullName());
		}
		else if (entry->entries[i]->entries.entries)
		{
			_MESSAGE("category: %s", entry->entries[i]->kwd ? entry->entries[i]->kwd->GetFullName() : "<none>");
			DumpWorkshopEntry(entry->entries[i]);
		}
	}
	gLog.Outdent();
}

WorkshopEntry* SetSelectedWorkshopEntryInRow(WorkshopEntry* entry, UInt32 index)
{
	WorkshopEntry* result = nullptr;
	for (size_t i = 0; i < entry->entries.count; i++)
	{
		if (i == index)
		{
			entry->entries[i]->selected = 1;
			result = entry->entries[i];
		}
		else
		{
			entry->entries[i]->selected = 0;
		}
	}
	if (result)
	{
		if (result->recipe)
		{
			_MESSAGE("select recipe: %s", result->object->GetFullName());
		}
		else if (result->entries.entries)
		{
			_MESSAGE("select category: %s", result->kwd ? result->kwd->GetFullName():"<none>");
		}
	}
	return result;
}

UInt16 SetSelectedWorkshopEntry(UInt32 row1index, UInt32 row2index, UInt32 row3index, UInt32 row4index)
{
	WorkshopEntry* tempEntry = nullptr;
	UInt16 topDepth = 0;
	_MESSAGE("set up 1st entry");
	tempEntry = SetSelectedWorkshopEntryInRow(g_rootWorkshopEntry, row1index);
	if (tempEntry->entries.entries)
	{
		topDepth = 1;
		_MESSAGE("set up 2nd entry");
		tempEntry = SetSelectedWorkshopEntryInRow(tempEntry, row2index);
		if (tempEntry->entries.entries)
		{
			topDepth = 2;
			_MESSAGE("set up 3rd entry");
			tempEntry = SetSelectedWorkshopEntryInRow(tempEntry, row3index);
			if (tempEntry->entries.entries)
			{
				topDepth = 3;
				_MESSAGE("set up 4th entry");
				tempEntry = SetSelectedWorkshopEntryInRow(tempEntry, row4index);
			}
		}
	}
	return topDepth;
}

WorkshopEntry* myReplacingFunction(UInt16 depth, UInt16 *resultIndex)
{
	_MESSAGE("myReplacingFunction called");
	*g_workshopDepth = SetSelectedWorkshopEntry(3, 2, 1, 3);
	return GetSelectedWorkshopEntry(*g_workshopDepth, resultIndex);
}







void PipboyMenuInvoke_Hook(PipboyMenu * menu, GFxFunctionHandler::Args * args) {


	if (args->optionID == 0xD && args->numArgs == 4 && args->args[0].GetType() == GFxValue::kType_Int \
		&& args->args[1].GetType() == GFxValue::kType_Array && args->args[2].GetType() == GFxValue::kType_Array)
	{
		SInt32 selectedIndex = args->args[0].GetInt();
		_MESSAGE("%i selected index", selectedIndex);
		if (selectedIndex>-1)
		{
			BSFixedString str = BSFixedString("HandleID");
			PipboyObject::PipboyTableItem *ti = (*g_PipboyDataManager)->inventoryData.inventoryObjects[selectedIndex]->table.Find(&str);
			if (ti)
			{
				UInt32 val = ((PipboyPrimitiveValue<UInt32>*)(ti->value))->value;
				_MESSAGE("handleID: %u", val);
			}
			BSFixedString str2 = BSFixedString("StackID");
			PipboyObject::PipboyTableItem *ti2 = (*g_PipboyDataManager)->inventoryData.inventoryObjects[selectedIndex]->table.Find(&str2);
			if (ti2)
			{
				tracePipboyArray((PipboyArray*)ti2->value);
			}
		}
		/*
		for (size_t i = 0; i < (*g_PipboyDataManager)->inventoryData.inventoryObjects.count; i++)
		{
			tracePipboyValue((*g_PipboyDataManager)->inventoryData.inventoryObjects[i]);
		}
		*/
	}
	return PipboyMenuInvoke_Original(menu, args);
}


void ContainerMenuInvoke_Hook(ContainerMenuBase * menu, GFxFunctionHandler::Args * args) {
	ContainerMenuInvoke_Original(menu, args);
	return;
	if (args->optionID != 3) return;
	int itemIndex = args->args[0].GetInt();
	if (itemIndex < 0) return;
	int isContainer = args->args[1].GetInt();
	auto movie = menu->movie;
	auto root = movie->movieRoot;
	GFxValue ListArray, ListArrayItem, ListArrayItemCardInfoList;
	BGSInventoryItem* ii = nullptr;
	if (isContainer == 0)
	{
		root->GetVariable(&ListArray, "root1.FilterHolder_mc.Menu_mc.playerListArray");
	}
	else
	{
		root->GetVariable(&ListArray, "root1.FilterHolder_mc.Menu_mc.containerListArray");
	}
	ListArray.GetElement(itemIndex, &ListArrayItem);
	if (ListArrayItem.HasMember("haveExtraData")) return;
	UInt32 handleID = 0;
	UInt32 stackID = 0;
	if (DYNAMIC_CAST(menu, GameMenuBase, ContainerMenu))
	{
		//_MESSAGE("is Container menu");
		if (isContainer)
		{
			handleID = menu->contItems[itemIndex].HandleID;
			stackID = menu->contItems[itemIndex].stackid;
		}
		else
		{
			handleID = menu->playerItems[itemIndex].HandleID;
			stackID = menu->playerItems[itemIndex].stackid;
		}
	}
	else if (DYNAMIC_CAST(menu, GameMenuBase, BarterMenu))
	{
		//_MESSAGE("is Barter menu");
		GFxValue tempVal;
		ListArrayItem.GetMember("handle", &tempVal);
		if (tempVal.type == GFxValue::kType_Undefined) return;
		handleID = tempVal.GetUInt();
		ListArrayItem.GetMember("stackArray", &tempVal);
		tempVal.GetElement(0, &tempVal);
		stackID = tempVal.GetUInt();
	}
	else
	{
		return;
	}

	ii = getInventoryItemByHandleID_int(handleID);
	if (!ii) return;
	ListArrayItem.GetMember("ItemCardInfoList", &ListArrayItemCardInfoList);
	// put ur code there. use ii and stackID variables

	// end of ur code

	GFxValue haveExtraData;
	haveExtraData.SetBool(true);
	ListArrayItem.SetMember("haveExtraData", &haveExtraData);
	return;
}


class ViewCasterUpdateEventSink : public BSTEventSink<ViewCasterUpdateEvent>
{
public:
	virtual    EventResult    ReceiveEvent(ViewCasterUpdateEvent * evn, void * dispatcher) override
	{
		TESObjectREFR* ref = nullptr;
		LookupREFRByHandle(&evn->handle, &ref);
		if (ref)
		{
			_MESSAGE("ViewCasterUpdateEvent handle %d name %s formid %u", evn->handle, ref->baseForm->GetFullName(), ref->formID);
		}
		return kEvent_Continue;
	}
};

ViewCasterUpdateEventSink viewCasterUpdateEventSink;

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
		if (currentSWFPathString.find("ExamineMenu.swf") != std::string::npos)
		{
			_DMESSAGE("hooking ExamineMenu");


		}
	}
	return true;
}

#include ".\TestS.h"

//-------------------------
// Input Handler
//-------------------------
class F4SEInputHandler : public BSInputEventUser
{
public:
	F4SEInputHandler() : BSInputEventUser(true) { }

	virtual void OnButtonEvent(ButtonEvent * inputEvent)
	{
		UInt32	keyCode;
		UInt32	deviceType = inputEvent->deviceType;
		UInt32	keyMask = inputEvent->keyMask;
		keyCode = keyMask;

		float timer = inputEvent->timer;
		bool  isDown = inputEvent->isDown == 1.0f && timer == 0.0f;
		bool  isUp = inputEvent->isDown == 0.0f && timer != 0.0f;

		BSFixedString* control = inputEvent->GetControlID();
		if (isDown) {
			_MESSAGE("isDown keycode: %i, control name: %s", keyMask, control->c_str());
		}
		else if (isUp) {
			_MESSAGE("isUp keycode: %i, control name: %s", keyMask, control->c_str());
		}
	}
};

F4SEInputHandler g_DebugInputHandler;


void RegisterForInput(bool bRegister) {
	if (bRegister) {
		g_DebugInputHandler.enabled = true;
		tArray<BSInputEventUser*>* inputEvents = &((*g_menuControls)->inputEvents);
		BSInputEventUser* inputHandler = &g_DebugInputHandler;
		int idx = inputEvents->GetItemIndex(inputHandler);
		if (idx == -1) {
			inputEvents->Push(&g_DebugInputHandler);
			_MESSAGE("Registered for input events.");
		}
	}
	else {
		g_DebugInputHandler.enabled = false;
	}
}

EventResult	TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent * evn, void * dispatcher)
{
	_DMESSAGE("TESLoadGameEvent recieved");
	auto eventDispatcher = GET_EVENT_DISPATCHER(ViewCasterUpdateEvent);
	if (eventDispatcher) {
		_MESSAGE("GET_EVENT_DISPATCHER");
		eventDispatcher->AddEventSink(&viewCasterUpdateEventSink);
	}
	return kEvent_Continue;
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		_MESSAGE("kMessage_GameDataReady");
		//static auto pLoadGameHandler = new TESLoadGameHandler();
		//GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
		//ConditionDtype = reinterpret_cast<BGSDamageType*>(GetFormFromIdentifier("F4NVMaster.esm|332CB"));
		//testreg();
		//RegisterForInput(true);
		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:
		_MESSAGE("kMessage_GameLoaded");
		break;
	}
}




#include "f4se/PapyrusNativeFunctions.h"

class BGSSaveLoadManager
{
public:
	void*	unk00;
	void*	unk08;
	void*	unk10;
	void*	unk18;
	void*	unk20;
	void*	unk28;
	void*	unk30;
	void*	unk38;
	void*	unk40;
	void*	unk48;
	void*	unk50;
	void*	unk58;
	void*	unk60;
	void*	unk68;
	void*	unk70;
	UInt32	unk78;
	UInt32	numCharacters; // 7C
	void*	unk80;
	void*	unk88;
	void*	unk90;
	void*	characterList; // 98
	void*	unkA0;
	void*	unkA8;
	void*	unkB0;
	void*	unkB8;
	void*	unkC0[280];
};
STATIC_ASSERT(sizeof(BGSSaveLoadManager) == 0x980);

bool testfunk(StaticFunctionTag *base) {
	_MESSAGE("testfunk");

	Actor* playerref = *g_player;

	TESObjectREFR* ref = NULL;

	UInt32 * handle = commandTargetCompanionRef;
	_MESSAGE("handle %I32u\t\thex: 0x%016I64X", handle, handle);

	if (*handle != 0 && *handle != (*g_invalidRefHandle)) {
		LookupREFRByHandle(handle, &ref);
	}

	if (ref)
	{
		_MESSAGE("IsWaiting %d", IsWaiting((Actor*)ref));
		DumpClass(((Actor*)ref)->middleProcess, 10);
		DumpClass(((Actor*)ref)->middleProcess->unk08, 20);
		DumpClass(((Actor*)ref)->middleProcess->unk20, 0xC8 / 8);

		DumpClass(((Actor*)ref)->middleProcess->unk10, 0x5A0/8);
	}
	


	//_MESSAGE("flags08 0x%016I64X flags0C 0x%016I64X", (*g_player)->actorState.unk08, (*g_player)->actorState.flags);
	return true;
	TESObjectARMO* arm = DYNAMIC_CAST(LookupFormByID(0x976B3), TESForm, TESObjectARMO);
	if (arm)
	{
		DumpClass(arm, 0x2E0/8);

		DumpClass((void*)((uintptr_t)arm + 0x1A0), 10);
		DumpClass(*(void**)((uintptr_t)arm+0x1A8), 40);
		_MESSAGE("%s",arm->raceForm.race->models[0].GetModelName());
		_MESSAGE("%s", arm->raceForm.race->models[1].GetModelName());
		_MESSAGE("%s", arm->raceForm.race->unk120[0].GetModelName());
		_MESSAGE("%s", arm->raceForm.race->unk120[1].GetModelName());
	}
	return true;

	RelocPtr<void*>g_pipboyInventoryData(0x5ABCAB8); // 130
	_MESSAGE("address 0x%016I64X", (uintptr_t)&(*g_PipboyDataManager)->inventoryData + 0x60);
	_MESSAGE("address 0x%016I64X", g_pipboyInventoryData.GetUIntPtr() + 0x60);
	return true;

	typedef void(*_UpdateFunction1)(void* pipboyInventoryData, BGSInventoryItem* itemForCard);
	RelocAddr <_UpdateFunction1> UpdateFunction1(0x0C10A40);
	typedef void(*_UpdateFunction2)(void* pipboyInventoryData, UInt32 formType);
	RelocAddr <_UpdateFunction2> UpdateFunction2(0x0C0F860);


	EnterCriticalSection((LPCRITICAL_SECTION)(g_pipboyInventoryData.GetUIntPtr() + 0x60));
	playerref->inventoryList->inventoryLock.LockForRead();
	for (size_t i = 0; i < playerref->inventoryList->items.count; i++)
	{
		if (playerref->inventoryList->items[i].form->formType == kFormType_WEAP)
		{
			UpdateFunction1(g_pipboyInventoryData, &playerref->inventoryList->items[i]);
		}
	}
	playerref->inventoryList->inventoryLock.Unlock();
	UpdateFunction2(g_pipboyInventoryData, kFormType_WEAP);
	LeaveCriticalSection((LPCRITICAL_SECTION)(g_pipboyInventoryData.GetUIntPtr() + 0x60));
	

	return true;
	DumpClass(playerref->inventoryList, 0x80 / 8);

	DumpClass(*g_itemMenuDataMgr, 0xD0 / 8);
	if ((*g_itemMenuDataMgr)->unkArray10.entries) DumpClass((*g_itemMenuDataMgr)->unkArray10.entries, (*g_itemMenuDataMgr)->unkArray10.count); // EventSinks
	if ((*g_itemMenuDataMgr)->unkArray28.entries) DumpClass((*g_itemMenuDataMgr)->unkArray28.entries, 20);
	if ((*g_itemMenuDataMgr)->unkArray40.entries) DumpClass((*g_itemMenuDataMgr)->unkArray40.entries, 20);
	if ((*g_itemMenuDataMgr)->unkArray68.entries) DumpClass((*g_itemMenuDataMgr)->unkArray68.entries, 20);
	if ((*g_itemMenuDataMgr)->unkArray80.entries) DumpClass((*g_itemMenuDataMgr)->unkArray80.entries, 20);
	if ((*g_itemMenuDataMgr)->unkArray98.entries) DumpClass((*g_itemMenuDataMgr)->unkArray98.entries, 20);
	if ((*g_itemMenuDataMgr)->inventoryItems.entries) DumpClass((*g_itemMenuDataMgr)->inventoryItems.entries, 20);


	return true;

	DumpClass(*g_PipboyDataManager, 0xCC0 / 8);
	return true;
	RelocPtr<BGSKeyword*>kwd(0x05917A10);
	_MESSAGE("kwd: %s", (*kwd)->keyword.c_str());
	return true;
	SetPlayerNameTest("new name");
	return true;

	playerref->inventoryList->inventoryLock.LockForRead();

	for (size_t i = 0; i < playerref->inventoryList->items.count; i++)
	{
		TESForm* form = playerref->inventoryList->items[i].form;
		BGSInventoryItem::Stack* stack = playerref->inventoryList->items[i].stack;
		if (form->formType == kFormType_WEAP)
		{
			TESObjectWEAP* weap = (TESObjectWEAP*)form;

			stack->Visit([&](BGSInventoryItem::Stack * stackx)
			{
				ExtraDataList * stackDataList = stackx->extraData;

				if (stackDataList) {
					ExtraInstanceData * eid = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
					if (eid)
					{
						_MESSAGE("stack data");
						//DumpClass(eid->instanceData, 0x138 / 8);
						TESObjectWEAP::InstanceData* weapData = (TESObjectWEAP::InstanceData*)eid->instanceData;

						ObjectInstanceData objInst{ nullptr, nullptr };

						CalcInstanceData(objInst, form, eid->instanceData);
						if (objInst.data)
						{
							_MESSAGE("calculated data");
							//DumpClass(objInst.data, 0x138/8);
							weapData = (TESObjectWEAP::InstanceData*)objInst.data;
							SimpleCollector<DamageInfo>		damageInfo;// { 0, { NULL } };
							InventoryItemStack				stack{ 0, 0, 0, stackDataList };

							CollectDamageInfo(form, stack, damageInfo);

							for (size_t i = 0; i < damageInfo.itemsArray.count; ++i)
							{
								if (damageInfo.itemsArray.entries[i].damage != 0.0f)
								{
									_MESSAGE("damageType %i value %f", damageInfo.itemsArray.entries[i].type, damageInfo.itemsArray.entries[i].damage);
								}
							}

						}
					}
				}
				return true;
			});
		}
	}


	playerref->inventoryList->inventoryLock.Unlock();


	return true;
	//------------------- SAVE GAMES -------------

	RelocPtr <void*> g_UISaveLoadManager(0x5A13258); // 0x60?
	DumpClass(*g_UISaveLoadManager, 0x60/8);

	RelocPtr <BGSSaveLoadManager*> g_saveLoadManager(0x5AAC618); // 0x980
	DumpClass(*g_saveLoadManager, 0x980 / 8);
	_MESSAGE("numChar %i", (*g_saveLoadManager)->numCharacters);
	DumpClass((*g_saveLoadManager)->characterList, 50);

	//------------------- EO SAVE GAMES -------------


	/*struct xxy
	{
		TESForm* form;
		BSFixedString str;
		void Dump(void)
		{
			_MESSAGE("\t\tForm: %08X", form ? form->formID : 0);
			_MESSAGE("\t\tunk08: %s", str.c_str());
		}
	};
	RelocPtr <tHashSet<xxy, BSFixedString>> xxx(0x370F888);
	xxx->Dump();
	*/
	/*struct yyx
	{
		UInt32* formid;
		TESForm* form;

		void Dump(void)
		{
			DumpClass(this,2);
		}
	};
	RelocPtr <tHashSet<yyx, UInt32>*> yyy(0x590C748);
	(*yyy)->Dump();*/
	/*
	WorkshopMenu * menu = (WorkshopMenu *)(*g_ui)->GetMenu(BSFixedString("WorkshopMenu"));
	if (!menu)
	{
		_DMESSAGE("menu closed");
		return false;
	}
	else
	{
		_DMESSAGE("menu opened");
	}

	auto movie = menu->movie;
	if (!movie)
		return false;

	auto root = movie->movieRoot;
	if (!root)
		return false;
	NiTArray <NiAVObject *>* xarray = &menu->workshopMenuGeometry->unk28->m_children;
	for (size_t i = 0; i < xarray->m_size; i++)
	{
		_MESSAGE("name %s", xarray->m_data[i]->m_name.c_str());
	}
	*/
	//DumpClass(&menu->inventory3DManager, 0x140/8);
	//DumpClass(menu->workshopMenuGeometry, 0x30/8);
	//DumpWorkshopEntry(g_rootWorkshopEntry);
	//WM_Up(menu);
	//UInt16 workshopItemIndex = 0;
	//DumpClass(GetSelectedWorkshopEntry(*g_workshopDepth, &workshopItemIndex), 10);

	//*g_workshopDepth = 3;
	//static BSFixedString menuName("WorkshopMenu");
	//CALL_MEMBER_FN((*g_uiMessageManager), SendUIMessage)(menuName, kMessage_Message);

	//DumpClass(xxx->Dump(), 1000);
	return true;
	DumpClass(*g_PipboyDataManager, 500);
	_MESSAGE("----------------------------------------------------------------------------------");
	(*g_PipboyDataManager)->mapData.unkhs1.Dump();
	//DumpClass((*g_PipboyDataManager)->mapData.unkxx[5], 50);
	_MESSAGE("----------------------------------------------------------------------------------");

	(*g_PipboyDataManager)->mapData.unkhs2.Dump();
	//DumpClass((*g_PipboyDataManager)->mapData.unkxx[11], 50);
	
	return true;

	TESQuest* hc = DYNAMIC_CAST(LookupFormByID(0x80E), TESForm, TESQuest);
	IObjectHandlePolicy * hp = (*g_gameVM)->m_virtualMachine->GetHandlePolicy();
	UInt64 hdl = hp->Create(hc->kTypeID, hc);

	VMIdentifier* hcScriptIdentifier = nullptr;

	VirtualMachine::IdentifierItem * ii = (*g_gameVM)->m_virtualMachine->m_attachedScripts.Find(&hdl);

	if (ii->count == 1)
	{
		if (_stricmp(ii->GetScriptObject(ii->identifier.one)->m_typeInfo->m_typeName.c_str(), "Hardcore:HC_ManagerScript") == 0)
		{
			hcScriptIdentifier = ii->GetScriptObject(ii->identifier.one);
		}		
	}
	else
	{
		for (UInt32 i = 0; i < ii->count; ++i)
		{
			
			if (_stricmp(ii->GetScriptObject(ii->identifier.many[i])->m_typeInfo->m_typeName.c_str(), "Hardcore:HC_ManagerScript") == 0)
			{
				hcScriptIdentifier = ii->GetScriptObject(ii->identifier.many[i]);
				break;
			}
				
		}
	}

	VMValue FoodPool, DrinkPool;

	if (hcScriptIdentifier)
	{
		if (GetScriptVariableValue(hcScriptIdentifier, "FoodPool", &FoodPool))
		{
			_MESSAGE("FoodPool %d", FoodPool.data.i);
		}
		if (GetScriptVariableValue(hcScriptIdentifier, "DrinkPool", &DrinkPool))
		{
			_MESSAGE("DrinkPool %d", DrinkPool.data.i);
		}
	}

	/*class xxxVisitor : public VirtualMachine::IdentifierItem::IScriptVisitor
	{
	public:
		virtual bool Visit(VMIdentifier* obj)
		{
			_MESSAGE("\t\t\t%s %i", obj->m_typeInfo->m_typeName.c_str(), _stricmp(obj->m_typeInfo->m_typeName.c_str(), "Hardcore:HC_ManagerScript"));
			if(obj->m_typeInfo->memberData.unk00 == 3)
			{
			_MESSAGE("Members:");
			gLog.Indent();
			for(UInt32 i = 0; i < obj->m_typeInfo->memberData.numMembers; ++i)
			{
			_MESSAGE("%s", obj->m_typeInfo->properties->defs[i].propertyName.c_str());
			DumpClass((void*)((uintptr_t)obj+0x10*(i+3)), 2);
			}
			gLog.Outdent();
			}
			
			return true;
		}
	};

	if (xxx)
	{
		xxxVisitor visitor;
		xxx->ForEachScript(&visitor);
	}*/

	return true;

}

bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, bool>("testfunk", "MyDebug:debugS", testfunk, vm));
	return true;
}

typedef bool(*_GetPropertyValue)(void* param1, void* param2, void* param3, void* param4);

RelocAddr <_GetPropertyValue> GetPropertyValue(0x002759FB0);
_GetPropertyValue GetPropertyValue_Original;

bool GetPropertyValue_Hook(void* param1, void* param2, void* param3, void* param4) {
	_MESSAGE("GetPropertyValue_Hook");
	return GetPropertyValue_Original(param1, param2, param3, param4);

}



_WorkshopMenuProcessMessage WorkshopMenuProcessMessage_Original;

void WorkshopMenuProcessMessage_Hook(WorkshopMenu* menu, UIMessage * message) {
	if (message->type != 0)
	{
		_MESSAGE("WorkshopMenuProcessMessage_Hook %i", message->type);
		//DumpClass(message, 10);
	}

	WorkshopMenuProcessMessage_Original(menu, message);
}

_OnWorkshopMenuButtonEvent OnWorkshopMenuButtonEvent_Original;

bool OnWorkshopMenuButtonEvent_Hook(BSInputEventUser* eu, ButtonEvent * inputEvent) {
	//_MESSAGE("OnWorkshopMenuButtonEvent_Hook %s", inputEvent->controlID.c_str());
	WorkshopMenu* wm = (WorkshopMenu*)((uintptr_t)eu - 0x10);
	//DumpClass((void*)((uintptr_t)eu-0x10), 0x500/8);


	bool result = OnWorkshopMenuButtonEvent_Original(eu, inputEvent);


	//_MESSAGE("============================ WORKSHOP MENU DUMP ================================");
	//UInt16 workshopItemIndex = 0;
	//DumpClass(GetSelectedWorkshopEntry(*g_workshopDepth, &workshopItemIndex),10);
	//_MESSAGE("%i %i", *g_workshopDepth, workshopItemIndex);
	/*
	RelocPtr <void*> x_parent(0x59198D0);
	DumpClass(x_parent,10);





	gLog.Indent();
	for (size_t i = 0; i < x_entries->count; i++)
	{
		_MESSAGE("%s", x_entries->entries[i]->kwd? x_entries->entries[i]->kwd->GetFullName():"<none>");
		DumpClass(x_entries->entries[i], 10);
		if (x_entries->entries[i]->entries.count>0)
		{
			gLog.Indent();
			for (size_t j = 0; j < x_entries->entries[i]->entries.count; j++)
			{
				_MESSAGE("%s", x_entries->entries[i]->entries[j]->kwd ? x_entries->entries[i]->entries[j]->kwd->GetFullName() : "<none>");
				DumpClass(x_entries->entries[i]->entries[j], 10);
				if (x_entries->entries[i]->entries[j]->entries.count > 0)
				{
					gLog.Indent();
					for (size_t k = 0; k < x_entries->entries[i]->entries[j]->entries.count; k++)
					{
						_MESSAGE("%s", x_entries->entries[i]->entries[j]->entries[k]->kwd ? x_entries->entries[i]->entries[j]->entries[k]->kwd->GetFullName() : "<none>");
						DumpClass(x_entries->entries[i]->entries[j]->entries[k], 10);
					}
					gLog.Outdent();
				}
			}
			gLog.Outdent();
		}
	}
	gLog.Outdent();*/

	//

	//_MESSAGE("x_row %i", *x_row);
	return result;
}

void PRKFMessageHandler(F4SEMessagingInterface::Message* msg) {
	_DMESSAGE("PRKFReadyMessage recieved raw");
	switch (msg->type)
	{
	case PRKFReadyMessage::kMessage_PRKFReady:
	{
		_DMESSAGE("PRKFReadyMessage recieved");
		PRKFAddDataMessage message;
		message.ININame = "BEPerks";
		message.INIVersion = 3;
		message.disableVanillaPerks = 1;
		message.PerksList = DYNAMIC_CAST(GetFormFromIdentifier("Be Exceptional.esp|44DED"), TESForm, BGSListForm);
		message.SkillsList = DYNAMIC_CAST(GetFormFromIdentifier("Be Exceptional.esp|3C53B"), TESForm, BGSListForm);
		g_messaging->Dispatch(g_pluginHandle, PRKFAddDataMessage::kMessage_PRKFAddData, (void*)&message, sizeof(PRKFAddDataMessage*), nullptr);
	}
	break;
	}
}

#include "f4se/ObScript.h"
#include "f4se_common/SafeWrite.h"
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
			char str[512];
			sprintf_s(str, sizeof(str), "Your game version: v%d.%d.%d.%d\nExpected version: v%d.%d.%d.%d\n%s will be disabled.",
				GET_EXE_VERSION_MAJOR(f4se->runtimeVersion),
				GET_EXE_VERSION_MINOR(f4se->runtimeVersion),
				GET_EXE_VERSION_BUILD(f4se->runtimeVersion),
				GET_EXE_VERSION_SUB(f4se->runtimeVersion),
				GET_EXE_VERSION_MAJOR(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_MINOR(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_BUILD(CURRENT_RUNTIME_VERSION),
				GET_EXE_VERSION_SUB(CURRENT_RUNTIME_VERSION),
				mName.c_str()
			);

			MessageBox(NULL, str, mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface *)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			_MESSAGE("couldn't get messaging interface");
			return false;
		}
		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
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

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		InitAddresses();
		InitWSMAddresses();
		InitCWAddresses();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		g_rootWorkshopEntry.SetEffective(g_rootWorkshopEntry.GetUIntPtr()-0x10);
		if (false)
		{
			_MESSAGE("ObScriptCommands");
			for (ObScriptCommand* iter = g_firstObScriptCommand; iter->opcode < (kObScript_NumObScriptCommands + kObScript_ScriptOpBase); iter++) {
				//if (strcmp(iter->longName, "AddItem") == 0) {
				//if (iter->params)
				//{
				//	_MESSAGE("%s: numParams: %i)", iter->longName, iter->numParams);
				//	DumpClass(iter->params, iter->numParams*2);
				//}
				
				_MESSAGE("%s (%s): execute 0x%08X parse 0x%08X eval 0x%08X", iter->longName, iter->shortName, (uintptr_t)iter->execute - RelocationManager::s_baseAddr, (uintptr_t)iter->parse - RelocationManager::s_baseAddr, (uintptr_t)iter->eval - RelocationManager::s_baseAddr);
				//}
			}
			_MESSAGE("ConsoleCommands");
			for (ObScriptCommand* iter = g_firstConsoleCommand; iter->opcode < (kObScript_NumConsoleCommands + kObScript_ConsoleOpBase); iter++) {
				_MESSAGE("%s (%s): execute 0x%08X parse 0x%08X eval 0x%08X", iter->longName, iter->shortName, (uintptr_t)iter->execute - RelocationManager::s_baseAddr, (uintptr_t)iter->parse - RelocationManager::s_baseAddr, (uintptr_t)iter->eval - RelocationManager::s_baseAddr);
			}
		}



		logMessage("load");
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		g_messaging->RegisterListener(g_pluginHandle, nullptr, PRKFMessageHandler);

		if (!g_branchTrampoline.Create(1024 * 64))
		{
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
		}
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		if (g_scaleform)
		{
			g_scaleform->Register("test", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr))
		{
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}

		/*
		{
			struct ContainerMenuInvoke_Code : Xbyak::CodeGenerator {
				ContainerMenuInvoke_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(r11, rsp);
					mov(ptr[r11 + 0x18], rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(ContainerMenuInvoke.GetUIntPtr() + 7);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			ContainerMenuInvoke_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			ContainerMenuInvoke_Original = (_ContainerMenuInvoke)codeBuf;

			g_branchTrampoline.Write6Branch(ContainerMenuInvoke.GetUIntPtr(), (uintptr_t)ContainerMenuInvoke_Hook);
		}

		{
			struct PipboyMenuInvoke_Code : Xbyak::CodeGenerator {
				PipboyMenuInvoke_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(r11, rsp);
					push(rbp);
					push(rbx);
					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(PipboyMenuInvoke.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			PipboyMenuInvoke_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			PipboyMenuInvoke_Original = (_PipboyMenuInvoke)codeBuf;

			g_branchTrampoline.Write5Branch(PipboyMenuInvoke.GetUIntPtr(), (uintptr_t)PipboyMenuInvoke_Hook);
		}

		{
			struct GetPropertyValue_Code : Xbyak::CodeGenerator {
				GetPropertyValue_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 8], rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(GetPropertyValue.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			GetPropertyValue_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			GetPropertyValue_Original = (_GetPropertyValue)codeBuf;

			g_branchTrampoline.Write5Branch(GetPropertyValue.GetUIntPtr(), (uintptr_t)GetPropertyValue_Hook);
		}




		{
			struct WorkshopMenuProcessMessage_Code : Xbyak::CodeGenerator {
				WorkshopMenuProcessMessage_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp + 8], rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(WorkshopMenuProcessMessage.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			WorkshopMenuProcessMessage_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			WorkshopMenuProcessMessage_Original = (_WorkshopMenuProcessMessage)codeBuf;

			g_branchTrampoline.Write5Branch(WorkshopMenuProcessMessage.GetUIntPtr(), (uintptr_t)WorkshopMenuProcessMessage_Hook);
		}

		{
			struct OnWorkshopMenuButtonEvent_Code : Xbyak::CodeGenerator {
				OnWorkshopMenuButtonEvent_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(rax,rsp);
					push(rbp);
					push(r14);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(OnWorkshopMenuButtonEvent.GetUIntPtr() + 6);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			OnWorkshopMenuButtonEvent_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			OnWorkshopMenuButtonEvent_Original = (_OnWorkshopMenuButtonEvent)codeBuf;

			g_branchTrampoline.Write6Branch(OnWorkshopMenuButtonEvent.GetUIntPtr(), (uintptr_t)OnWorkshopMenuButtonEvent_Hook);
		}


		*/

		/*{
			struct PopulateItemCardInfoList_Code : Xbyak::CodeGenerator {
				PopulateItemCardInfoList_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(rax, rsp);
					mov(ptr[rax+0x20], r9);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(PopulateItemCardInfoList.GetUIntPtr() + 7);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			PopulateItemCardInfoList_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			PopulateItemCardInfoList_Original = (_PopulateItemCardInfoList)codeBuf;

			g_branchTrampoline.Write6Branch(PopulateItemCardInfoList.GetUIntPtr(), (uintptr_t)PopulateItemCardInfoList_Hook);
		}*/

		/*{
			struct ExamineMenu__DrawNextFrame_Code : Xbyak::CodeGenerator {
				ExamineMenu__DrawNextFrame_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
				{
					Xbyak::Label retnLabel;

					mov(ptr[rsp+0x10], rbx);

					jmp(ptr[rip + retnLabel]);

					L(retnLabel);
					dq(ExamineMenu__DrawNextFrame.GetUIntPtr() + 5);
				}
			};

			void * codeBuf = g_localTrampoline.StartAlloc();
			ExamineMenu__DrawNextFrame_Code code(codeBuf);
			g_localTrampoline.EndAlloc(code.getCurr());

			ExamineMenu__DrawNextFrame_Original = (_ExamineMenu__DrawNextFrame)codeBuf;

			g_branchTrampoline.Write5Branch(ExamineMenu__DrawNextFrame.GetUIntPtr(), (uintptr_t)ExamineMenu__DrawNextFrame_Hook);
		}*/

		unsigned char data[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
		//SafeWriteBuf(RelocAddr<uintptr_t>(0xB8E6EF).GetUIntPtr(), &data, sizeof(data));
		//g_branchTrampoline.Write5Call(wsm_secondAddress.GetUIntPtr(), (uintptr_t)myReplacingFunction);
		//ExamineMenu__Invoke_Original = HookUtil::SafeWrite64(ExamineMenu__Invoke_HookTarget.GetUIntPtr(), &ExamineMenu__Invoke_Hook);

		return true;
	}

};
