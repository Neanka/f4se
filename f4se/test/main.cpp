#include "main.h"
#include "Shared.h"

std::string mName = "test";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

#include "xbyak/xbyak.h"
#include "f4se_common/BranchTrampoline.h"
#include "gfxfunctions.h"

F4SEScaleformInterface		*g_scaleform = NULL;

typedef void(*_ContainerMenuInvoke)(ContainerMenu* menu, GFxFunctionHandler::Args* args);

RelocAddr <_ContainerMenuInvoke> ContainerMenuInvoke(0x00B0A280);
_ContainerMenuInvoke ContainerMenuInvoke_Original;


void ContainerMenuInvoke_Hook(ContainerMenu * menu, GFxFunctionHandler::Args * args) {

	if (args->optionID == 0 || args->optionID == 3) return ContainerMenuInvoke_Original(menu, args);
	_MESSAGE("Update item cards");
		auto movie = menu->movie;
		auto root = movie->movieRoot;

		GFxValue playerListArray, playerListArrayItem, playerListArrayItemCardInfoList;
		root->GetVariable(&playerListArray, "root1.FilterHolder_mc.Menu_mc.playerListArray");

		for (size_t i = 0; i < playerListArray.GetArraySize(); i++)
		{
			playerListArray.GetElement(i, &playerListArrayItem);
			if (!playerListArrayItem.HasMember("haveExtraData"))
			{
				playerListArrayItem.GetMember("ItemCardInfoList", &playerListArrayItemCardInfoList);

				BGSInventoryItem* ii = getInventoryItemByHandleID_int(menu->playerItems[i].HandleID);
				if (ii)
				{
					TESForm* form = ii->form;
					BGSInventoryItem::Stack* currentStack = ii->stack;
					UInt16 stackid = menu->playerItems[i].stackid;
					while (stackid != 0)
					{
						currentStack = currentStack->next;
						stackid--;
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
						playerListArrayItemCardInfoList.PushBack(&extraData);
					}
				}

				GFxValue haveExtraData;
				haveExtraData.SetBool(true);
				playerListArrayItem.SetMember("haveExtraData", &haveExtraData);
			}
		}


		GFxValue containerListArray, containerListArrayItem, containerListArrayItemCardInfoList;
		root->GetVariable(&containerListArray, "root1.FilterHolder_mc.Menu_mc.containerListArray");

		for (size_t i = 0; i < containerListArray.GetArraySize(); i++)
		{
			containerListArray.GetElement(i, &containerListArrayItem);
			if (!containerListArrayItem.HasMember("haveExtraData"))
			{
				containerListArrayItem.GetMember("ItemCardInfoList", &containerListArrayItemCardInfoList);

				BGSInventoryItem* ii = getInventoryItemByHandleID_int(menu->contItems[i].HandleID);
				if (ii)
				{
					TESForm* form = ii->form;
					BGSInventoryItem::Stack* currentStack = ii->stack;
					UInt16 stackid = menu->contItems[i].stackid;
					while (stackid != 0)
					{
						currentStack = currentStack->next;
						stackid--;
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
						containerListArrayItemCardInfoList.PushBack(&extraData);
					}
				}

				GFxValue haveExtraData;
				haveExtraData.SetBool(true);
				containerListArrayItem.SetMember("haveExtraData", &haveExtraData);
			}
		}
		return ContainerMenuInvoke_Original(menu, args);
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
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_89) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.89 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.89). \n"+mName+" will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
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
		return true;
	}

};
