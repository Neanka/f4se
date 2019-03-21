#pragma once
#include "Shared.h"
#include "f4se/ScaleformLoader.h"


namespace G
{
    void Init();
	extern RVA<BSScaleformManager*>			scaleformManager;
    extern RVA<UI*>                         ui;
    extern RVA<GameVM*>                     gameVM;
    extern RVA<DataHandler*>                dataHandler;
    extern RVA<PlayerCharacter*>            player;
    extern RVA<INISettingCollection*>       iniSettings;
    extern RVA<INIPrefSettingCollection*>   iniPrefSettings;
}
