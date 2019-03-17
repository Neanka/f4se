#include "main.h"

#include "f4se_common/SafeWrite.h"

std::string mName = "ACW";
UInt32 mVer = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEScaleformInterface		*g_scaleform = NULL;
F4SEMessagingInterface		*g_messaging = NULL;

#define AMMO_COUNT_FADE_TIME_ADDRESS 0x375CF30 // 48 8D 4D D8 E8 ? ? ? ? 84 C0 74 ? 8B 15 +0xD , 2 , 6
#define CLIP_COUNT_999_CHECK_ADDRESS 0x0A0EF3D // B9 E7 03 00 00 3B C1 0F 47 C1 48 83 C4 20 5B C3
#define RESERVE_COUNT_999_CHECK_ADDRESS 0x0A0EFBE // B9 E7 03 00 00 3B C1 0F 47 C1 48 83 C4 20 5B C3
#define AMMO_COUNT_STRING_FORMAT_ADDRESS 0x2D14068 // 84 C0 74 ? 44 8B 83 98 01 00 00  +0xB , 3 , 7
#define CLIP_COUNT_WAS_CHANGED_CHECK_ADDRESS 0x0A0E94E
#define RESERVE_COUNT_WAS_CHANGED_CHECK_ADDRESS 0x0A0E8EA
#define UPDATE_COMPONENT_HOOK_ADDRESS 0x2D13F48

RelocPtr <UInt32> uAmmoCounterFadeTimeMS(AMMO_COUNT_FADE_TIME_ADDRESS);

typedef UInt32(*_HUDAmmoCounter__UpdateComponent)(HUDAmmoCounter* hUDAmmoCounter);
RelocAddr <_HUDAmmoCounter__UpdateComponent> HUDAmmoCounter__UpdateComponent_HookTarget(UPDATE_COMPONENT_HOOK_ADDRESS);
//RelocAddr <_HUDAmmoCounter__UpdateComponent> HUDAmmoCounter__UpdateComponent(0x000A0E580);
_HUDAmmoCounter__UpdateComponent HUDAmmoCounter__UpdateComponent_Original;

UInt8 bHorisontalAlign = 0;
UInt8 bZeroFilled = 1;
UInt8 iDigitCount = 3;
UInt32 iFadeTimeMS = 10000;
UInt8 bShowReserveCount = 1;

UInt8 bTunePosition = 0;
float fX = 0.0;
float fY = -84.0;
float fScaleX = 1.0;
float fScaleY = 1.0;
float fRotation = 0.0;

float lineLength = 0.0;
float lineX = 0.0;
bool bIsDirty = false;

#define ReadSettingMainInt(key)	\
	key = GetPrivateProfileInt("Main", #key, key, "./Data/MCM/Settings/ACW.ini"); \
	_MESSAGE("%s=%i", #key, key);

#define ReadSettingMainFloat(key)	\
	GetPrivateProfileStringA("Main", #key, (LPCSTR)std::to_string(key).c_str(), sResult.get(), MAX_PATH, "./Data/MCM/Settings/ACW.ini"); \
	key = std::stof(sResult.get()); \
	_MESSAGE("%s=%f", #key, key);

void ReadSettings()
{
	ReadSettingMainInt(bHorisontalAlign);
	ReadSettingMainInt(bZeroFilled);
	ReadSettingMainInt(iDigitCount);
	ReadSettingMainInt(iFadeTimeMS);
	ReadSettingMainInt(bShowReserveCount);
	ReadSettingMainInt(bTunePosition);

	std::unique_ptr<char[]> sResult(new char[MAX_PATH]);
	ReadSettingMainFloat(fX);
	ReadSettingMainFloat(fY);
	ReadSettingMainFloat(fScaleX);
	ReadSettingMainFloat(fScaleY);
	ReadSettingMainFloat(fRotation);
}

void ApplySettings(GFxMovieRoot * movieRoot = nullptr)
{
	if (iFadeTimeMS)
		*uAmmoCounterFadeTimeMS = iFadeTimeMS;
	else
		*uAmmoCounterFadeTimeMS = UINT32_MAX;

	UInt32 data = 999;
	unsigned char data2[] = { 0x25, 0x30, 0x33, 0x75, 0x00 };
	unsigned char data3[] = { 0x25, 0x75, 0x00, 0x00, 0x00 };

	switch (iDigitCount)
	{
	case 1:
		data = 9;
		data2[2] = 0x31;
		break;
	case 2:
		data = 99;
		data2[2] = 0x32;
		break;
	case 3:
		data = 999;
		data2[2] = 0x33;
		break;
	case 4:
		data = 9999;
		data2[2] = 0x34;
		break;
	default:
		data = UINT32_MAX;
		data2[2] = 0x35;
		break;
	}

	SafeWrite32(RelocAddr<uintptr_t>(CLIP_COUNT_999_CHECK_ADDRESS).GetUIntPtr(), data); // clip count 999 check 
	SafeWrite32(RelocAddr<uintptr_t>(RESERVE_COUNT_999_CHECK_ADDRESS).GetUIntPtr(), data); // reserve count 999 check 

	if (bZeroFilled)
		SafeWriteBuf(RelocAddr<uintptr_t>(AMMO_COUNT_STRING_FORMAT_ADDRESS).GetUIntPtr(), &data2, sizeof(data2)); // ammo count format "%03u"
	else
		SafeWriteBuf(RelocAddr<uintptr_t>(AMMO_COUNT_STRING_FORMAT_ADDRESS).GetUIntPtr(), &data3, sizeof(data3)); // ammo count format "%u"

	if (!movieRoot)
	{
		IMenu* menu = (*g_ui)->GetMenu(BSFixedString("HUDMenu"));
		if (!menu) return;
		GFxMovieView* movie = menu->movie;
		if (!movie) return;
		movieRoot = movie->movieRoot;
		if (!movieRoot) return;
	}
	if (bTunePosition)
		TuneWidgetPosition(movieRoot);
	ToggleReserveVisibility(bShowReserveCount, movieRoot);
	if (bHorisontalAlign && bShowReserveCount)
		SetHorizontalElementsPosition(movieRoot);
	else
		SetDefaultElementsPosition(movieRoot);
}

void ToggleReserveVisibility(UInt8 visible, GFxMovieRoot * movieRoot)
{
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.visible", &GFxValue(visible == 1));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.visible", &GFxValue(visible == 1));
	_MESSAGE("ToggleReserveVisibility");
}

void TuneLinePosition(float newLineLength)
{
	IMenu* menu = (*g_ui)->GetMenu(BSFixedString("HUDMenu"));
	if (!menu) return;
	GFxMovieView* movie = menu->movie;
	if (!movie) return;
	GFxMovieRoot* movieRoot = movie->movieRoot;
	if (!movieRoot) return;
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.width", &GFxValue(newLineLength));
	_MESSAGE("TuneLinePosition");
}

void TuneHorizontalPosition(float newLineX)
{
	IMenu* menu = (*g_ui)->GetMenu(BSFixedString("HUDMenu"));
	if (!menu) return;
	GFxMovieView* movie = menu->movie;
	if (!movie) return;
	GFxMovieRoot* movieRoot = movie->movieRoot;
	if (!movieRoot) return;
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.x", &GFxValue(newLineX));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ClipCount_tf.x", &GFxValue(newLineX - 142.0));
	_MESSAGE("TuneHorizontalPosition");
}

UInt32 HUDAmmoCounter__UpdateComponent_Hook(HUDAmmoCounter* hUDAmmoCounter) {

	//_MESSAGE("HUDAmmoCounter__UpdateComponent_Hook");
	//DumpClass(hUDAmmoCounter, 0x230/8);
	if (bIsDirty)
	{
		unsigned char data[] = { 0x90, 0x90 }; // skip count changed check to force update text fields
		SafeWriteBuf(RelocAddr<uintptr_t>(CLIP_COUNT_WAS_CHANGED_CHECK_ADDRESS).GetUIntPtr(), &data, sizeof(data));
		SafeWriteBuf(RelocAddr<uintptr_t>(RESERVE_COUNT_WAS_CHANGED_CHECK_ADDRESS).GetUIntPtr(), &data, sizeof(data));

		ApplySettings();
	}
	UInt32 result = HUDAmmoCounter__UpdateComponent_Original(hUDAmmoCounter);
	if (!bHorisontalAlign && bShowReserveCount)
	{
		GFxValue tw, tw1;
		hUDAmmoCounter->ClipCount_tf.GetMember("textWidth", &tw);
		hUDAmmoCounter->ReserveCount_tf.GetMember("textWidth", &tw1);
		float newLineLength = max(tw.GetNumber(), tw1.GetNumber());
		if (newLineLength != lineLength)
		{
			lineLength = newLineLength;
			TuneLinePosition(lineLength);
		}
	}
	if (bHorisontalAlign && bShowReserveCount)
	{
		GFxValue tw2;
		hUDAmmoCounter->ReserveCount_tf.GetMember("textWidth", &tw2);
		float newLineX = -14 - tw2.GetNumber();
		if (newLineX != lineX)
		{
			lineX = newLineX;
			TuneHorizontalPosition(lineX);
		}
	}
	if (bIsDirty)
	{
		bIsDirty = false;
		unsigned char data2[] = { 0x74, 0x38 }; // original 
		SafeWriteBuf(RelocAddr<uintptr_t>(CLIP_COUNT_WAS_CHANGED_CHECK_ADDRESS).GetUIntPtr(), &data2, sizeof(data2));
		SafeWriteBuf(RelocAddr<uintptr_t>(RESERVE_COUNT_WAS_CHANGED_CHECK_ADDRESS).GetUIntPtr(), &data2, sizeof(data2));
	}
	return result;
}

class Scaleform_Update : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args) {
		_MESSAGE("Scaleform_Update");
		ReadSettings();
		bIsDirty = true;
		//ApplySettings(args->movie->movieRoot);
	}
};

void TuneWidgetPosition(GFxMovieRoot * movieRoot)
{
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.x", &GFxValue(fX));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.y", &GFxValue(fY));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.scaleX", &GFxValue(fScaleX));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.scaleY", &GFxValue(fScaleY));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.rotation", &GFxValue(fRotation));
	_MESSAGE("TuneWidgetPosition");
}

void SetDefaultElementsPosition(GFxMovieRoot * movieRoot)
{
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ClipCount_tf.x", &GFxValue(-134.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.x", &GFxValue(-134.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ClipCount_tf.width", &GFxValue(137.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.width", &GFxValue(137.0));

	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.y", &GFxValue(-2.0));

	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.rotation", &GFxValue(0.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.y", &GFxValue(0.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.width", &GFxValue(44.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.x", &GFxValue(0.0));
	_MESSAGE("SetDefaultElementsPosition");
}

void SetHorizontalElementsPosition(GFxMovieRoot * movieRoot)
{
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ClipCount_tf.x", &GFxValue(-271.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.x", &GFxValue(-134.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ClipCount_tf.width", &GFxValue(137.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.width", &GFxValue(137.0));

	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.ReserveCount_tf.y", &GFxValue(-40.0));


	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.rotation", &GFxValue(108.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.width", &GFxValue(10.0));
	movieRoot->SetVariable("root.RightMeters_mc.AmmoCount_mc.AmmoLineInstance.y", &GFxValue(-6.0));


	_MESSAGE("SetHorizontalElementsPosition");
}

bool RegisterScaleform(GFxMovieView * view, GFxValue * f4se_root)
{

	GFxMovieRoot	*movieRoot = view->movieRoot;

	GFxValue currentSWFPath;
	std::string currentSWFPathString = "";
	if (movieRoot->GetVariable(&currentSWFPath, "root.loaderInfo.url")) {
		currentSWFPathString = currentSWFPath.GetString();
		RegisterFunction<Scaleform_Update>(f4se_root, view->movieRoot, "Update");
		if (currentSWFPathString.find("HUDMenu.swf") != std::string::npos)
		{
			_DMESSAGE("hooking HUDmenu");

			//ApplySettings(movieRoot);
			bIsDirty = true;
		}
	}
	return true;
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {

	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		_MESSAGE("kMessage_GameDataReady");
		ReadSettings();
		break;
	case F4SEMessagingInterface::kMessage_GameLoaded:
		_MESSAGE("kMessage_GameLoaded");
		break;
	}
}


extern "C"
{

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, (const char*)("\\My Games\\Fallout4\\F4SE\\" + mName + ".log").c_str());

		logMessage("query");

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = mName.c_str();
		info->version = mVer;

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
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface *f4se)
	{
		logMessage("load");

		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);

		if (g_scaleform)
		{
			g_scaleform->Register("ACW", RegisterScaleform);
			_MESSAGE("Scaleform Register Succeeded");
		}

		HUDAmmoCounter__UpdateComponent_Original = HookUtil::SafeWrite64(HUDAmmoCounter__UpdateComponent_HookTarget.GetUIntPtr(), &HUDAmmoCounter__UpdateComponent_Hook);

		return true;
	}

};
