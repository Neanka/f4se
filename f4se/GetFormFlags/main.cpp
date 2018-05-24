#include "main.h"
#include "Shared.h"

std::string mName = "GetFormFlags";
UInt32 mVer = 1;
IDebugLog	gLog;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;
F4SEPapyrusInterface		*g_papyrus = NULL;

#include "f4se/PapyrusArgs.h"
#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se/PapyrusUtilities.h"

DECLARE_STRUCT(FormFlags, "Form");

class TESObjectBOOK : public TESBoundObject
{

public:
	enum { kTypeID = kFormType_BOOK };

	enum	// type - these are technically flags
	{
		kType_None = 0,
		kType_Skill = 1 << 0,	// 01
		kType_CantBeTaken = 1 << 1,	// 02
		kType_Spell = 1 << 2,	// 04 takes priority over skill
		kType_Read = 1 << 3,	// 08 set once the book is equipped by the player, along with the CHANGE_BOOK_READ (0x40) change flag
		kType_AddPerk = 1 << 4
	};

	TESFullName					fullName;
	BGSModelMaterialSwap		materialSwap;
	TESIcon						icon;
	TESValueForm				value;
	TESWeightForm				weight;
	TESDescription				description; // E8
	BGSDestructibleObjectForm	destructible;
	BGSMessageIcon				messageIcon;
	BGSPickupPutdownSounds		pickupSounds;
	BGSKeywordForm				keyword;
	BGSFeaturedItemMessage		featuredMessage;

	UInt8						_flags;					// 0x170
	BGSPerk						* unk178;
	UInt64						unk180;
	void						* unk188;				// TESObjectSTAT
	TESDescription				description2;
};
STATIC_ASSERT(sizeof(TESObjectBOOK) == 0x1A8);
STATIC_ASSERT(offsetof(TESObjectBOOK, description) == 0xE8);

FormFlags GetFlags(TESForm * form)
{
	FormFlags result;
	result.Set<UInt32>("formFlags", form->flags);
	UInt32 specialFlags = 0;
	switch (form->formType)
	{
	case (TESObjectBOOK::kTypeID):
		specialFlags = ((TESObjectBOOK*)form)->_flags;
	default:
		break;
	}
	result.Set<UInt32>("specialFlags", specialFlags);
		
	DumpClass(form, 3);
	return result;
}

bool IsNonPlayable(TESForm * form)
{
	return (form->flags & 4);
}

bool RegisterPapyrus(VirtualMachine *vm) {
	vm->RegisterFunction(
		new NativeFunction0 <TESForm, FormFlags>("GetFlags", "Form", GetFlags, vm));
	vm->RegisterFunction(
		new NativeFunction0 <TESForm, bool>("IsNonPlayable", "Form", IsNonPlayable, vm));
	_MESSAGE("Registered Papyrus native functions.");

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
		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_50) {
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.50 only.", f4se->runtimeVersion);
			MessageBox(NULL, (LPCSTR)("Unsupported runtime version (expected v1.10.50). \n"+mName+" will be disabled.").c_str(), (LPCSTR)mName.c_str(), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}
		// Get the papyrus interface
		g_papyrus = (F4SEPapyrusInterface *)f4se->QueryInterface(kInterface_Papyrus);
		if (!g_papyrus) {
			_MESSAGE("couldn't get papyrus interface");
			return false;
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");
		g_papyrus->Register(RegisterPapyrus);
		return true;
	}

};
