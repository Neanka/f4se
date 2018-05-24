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
			_WARNING("WARNING: Unsupported runtime version %08X. This DLL is built for v1.10.89 only.", f4se->runtimeVersion);
			MessageBox(NULL, "Unsupported runtime version (expected v1.10.89). \ndef_ui will be disabled.", "def_ui", MB_OK | MB_ICONEXCLAMATION);
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
