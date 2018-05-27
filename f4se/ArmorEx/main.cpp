#include "main.h"
#include "Shared.h"

std::string mName = "ArmorEx";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEPapyrusInterface		*g_papyrus = NULL;

/*
TESObjectARMO* xx = DYNAMIC_CAST(LookupFormByID(0x1153DB), TESForm, TESObjectARMO);
//DumpClass(xx, 0x1D0 / 8);
if (xx)
{
DumpClass(GetArmorMessageIcon(xx,false), 3);
_DMESSAGE(" messageicon male %s", GetArmorMessageIcon(xx, false)->unk08.str.c_str());
DumpClass(GetArmorMessageIcon(xx, true), 3);
_DMESSAGE(" messageicon female %s", GetArmorMessageIcon(xx, true)->unk08.str.c_str());
DumpClass(GetArmorIcon(xx, false), 2);
_DMESSAGE(" icon male %s", GetArmorIcon(xx, false)->str.c_str());
DumpClass(GetArmorIcon(xx, true), 2);
_DMESSAGE(" icon female %s", GetArmorIcon(xx, true)->str.c_str());
}
*/
BGSMessageIcon* GetArmorMessageIcon(TESObjectARMO* armo, bool isFemale)
{
	return Utils::GetOffsetPtr<BGSMessageIcon>(armo, isFemale ? 0x188 : 0x170);
}

TESIcon* GetArmorIcon(TESObjectARMO* armo, bool isFemale)
{
	return Utils::GetOffsetPtr<TESIcon>(armo, isFemale ? 0x160 : 0x150);
}

BSFixedString Pap_GetArmorMessageIconPath(StaticFunctionTag*, TESObjectARMO* armo, bool isFemale)
{
	return GetArmorMessageIcon(armo, isFemale)->unk08.str;
}

BSFixedString Pap_GetArmorIconPath(StaticFunctionTag*, TESObjectARMO* armo, bool isFemale)
{
	return GetArmorIcon(armo, isFemale)->str;
}

#include "f4se/PapyrusNativeFunctions.h"
bool RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, BSFixedString, TESObjectARMO*, bool>("GetMessageIconPath", "ArmorEx", Pap_GetArmorMessageIconPath, vm));
	vm->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, BSFixedString, TESObjectARMO*, bool>("GetIconPath", "ArmorEx", Pap_GetArmorIconPath, vm));
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
		logMessage("load");
		if (g_papyrus)
		{
			g_papyrus->Register(RegisterFuncs);
			_MESSAGE("Papyrus Register Succeeded");
		}
		return true;
	}

};
