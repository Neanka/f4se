#include "main.h"
#include "Shared.h"

std::string mName = "test";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"
#include "gfxfunctions.h"

F4SEScaleformInterface		*g_scaleform = NULL;

typedef void(*_ContainerMenuInvoke)(ContainerMenuBase* menu, GFxFunctionHandler::Args* args);

RelocAddr <_ContainerMenuInvoke> ContainerMenuInvoke(0x00B0A280);
_ContainerMenuInvoke ContainerMenuInvoke_Original;

class PipboyMenu;
typedef void(*_PipboyMenuInvoke)(PipboyMenu* menu, GFxFunctionHandler::Args* args);

RelocAddr <_PipboyMenuInvoke> PipboyMenuInvoke(0x00B93F60);
_PipboyMenuInvoke PipboyMenuInvoke_Original;

void PipboyMenuInvoke_Hook(PipboyMenu * menu, GFxFunctionHandler::Args * args) {


	if (args->optionID == 0xD && args->numArgs == 4 && args->args[0].GetType() == GFxValue::kType_Int \
		&& args->args[1].GetType() == GFxValue::kType_Array && args->args[2].GetType() == GFxValue::kType_Array)
	{
		SInt32 selectedIndex = args->args[0].GetInt();
		_MESSAGE("%i selected index", selectedIndex);
		BSFixedString str = BSFixedString("HandleID");
		PipboyObject::PipboyTableItem *ti = (*g_PipboyDataManager)->inventoryObjects[selectedIndex]->table.Find(&str);
		if (ti)
		{
			UInt32 val = ((PipboyPrimitiveValue<UInt32>*)(ti->value))->value;
			_MESSAGE("handleID: %u", val);
		}
		BSFixedString str2 = BSFixedString("StackID");
		PipboyObject::PipboyTableItem *ti2 = (*g_PipboyDataManager)->inventoryObjects[selectedIndex]->table.Find(&str2);
		if (ti2)
		{
			tracePipboyArray((PipboyArray*)ti2->value);
		}
	}
	return PipboyMenuInvoke_Original(menu, args);
}

void ContainerMenuInvoke_Hook(ContainerMenuBase * menu, GFxFunctionHandler::Args * args) {
	ContainerMenuInvoke_Original(menu, args);
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

	TESForm* form = ii->form;
	BGSInventoryItem::Stack* currentStack = ii->stack;
	while (stackID != 0)
	{
		currentStack = currentStack->next;
		stackID--;
	}
	if (form->formType == kFormType_WEAP)
	{
		TESObjectWEAP* weap = (TESObjectWEAP*)form;
		float APCost = weap->weapData.actionCost;
		ExtraDataList * stackDataList = currentStack->extraData;
		if (stackDataList) {
			ExtraInstanceData * eid = DYNAMIC_CAST(stackDataList->GetByType(kExtraData_InstanceData), BSExtraData, ExtraInstanceData);
			if (eid)
			{
				APCost = ((TESObjectWEAP::InstanceData*)eid->instanceData)->actionCost;
			}
		}
		GFxValue extraData;
		root->CreateObject(&extraData);
		RegisterString(&extraData, root, "text", "APCost");
		RegisterString(&extraData, root, "value", std::to_string(int(round(APCost))).c_str());
		RegisterInt(&extraData, "difference", 0);
		ListArrayItemCardInfoList.PushBack(&extraData);
	}

	// end of ur code

	GFxValue haveExtraData;
	haveExtraData.SetBool(true);
	ListArrayItem.SetMember("haveExtraData", &haveExtraData);
	return;
}

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		//_MESSAGE("hooking %s", currentSWFPathString.c_str());
		if (currentSWFPathString.find("ContainerMenu.swf") != std::string::npos)
		{
		//	_DMESSAGE("hooking ContainerMenu");


		}
	}
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

		g_scaleform = (F4SEScaleformInterface *)f4se->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");
			return false;
		}

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		InitAddresses();
		RVAManager::UpdateAddresses(f4se->runtimeVersion);
		logMessage("load");
		if (!g_branchTrampoline.Create(1024 * 64))
		{
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
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

		return true;
	}

};
