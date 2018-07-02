#include "f4se/PluginAPI.h"
#include "f4se/GameAPI.h"
#include <shlobj.h>

#include "main.h"
#include "Shared.h"

#include "f4se_common/f4se_version.h"

// Translation
#include "f4se/ScaleformTranslator.h"
#include "f4se/ScaleformLoader.h"
#include "f4se/Translation.h"

std::string mName = "DEF_UI Translator";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEMessagingInterface		*g_messaging = NULL;

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameLoaded:
		// Inject translations
		BSScaleformTranslator* translator = (BSScaleformTranslator*)(*g_scaleformManager)->stateBag->GetStateAddRef(GFxState::kInterface_Translator);
		if (translator) {
			std::string def_ui = "def_ui";
			Translation::ParseTranslation(translator, def_ui);
		}
		break;
	}
}

extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\def_ui.log");

		_MESSAGE("def_ui v1.0");
		_MESSAGE("def_ui query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"def_ui";
		info->version =		1;

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

		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		_MESSAGE("def_ui load");
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		return true;
	}

};
