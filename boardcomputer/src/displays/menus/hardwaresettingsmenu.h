#pragma once

#include <ratio>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "settingsaccessors.h"

namespace {
class HardwareSettingsMenu;
class PotiSettingsMenu;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
using WheelDiameterMmChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_WHEELDIAMETERMM>, WheelDiameterMmAccessor, SwitchScreenAction<HardwareSettingsMenu>>;
using WheelDiameterInchChangeScreen = makeComponent<ChangeValueDisplay<float>, StaticText<TEXT_WHEELDIAMETERINCH>, WheelDiameterInchAccessor, RatioNumberStep<float, std::ratio<1,10>>, SwitchScreenAction<HardwareSettingsMenu>>;
using NumMagnetPolesChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_NUMMAGNETPOLES>, NumMagnetPolesAccessor, SwitchScreenAction<HardwareSettingsMenu>>;

class HardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_HARDWARESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,        SwitchScreenAction<EnableMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,       SwitchScreenAction<InvertMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,      SwitchScreenAction<PotiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERMM>,   SwitchScreenAction<WheelDiameterMmChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERINCH>, SwitchScreenAction<WheelDiameterInchChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_NUMMAGNETPOLES>,    SwitchScreenAction<NumMagnetPolesChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SWAPFRONTBACK>,     ToggleBoolAction, CheckboxIcon, SwapFrontBackAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
