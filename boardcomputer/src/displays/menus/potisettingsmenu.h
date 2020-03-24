#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetGasMinDisplay;
class SetGasMaxDisplay;
class SetBremsMinDisplay;
class SetBremsMaxDisplay;
class SettingsMenu;
}

namespace {
class PotiSettingsMenu final : public MenuDisplay<
    TEXT_POTISETTINGS,
    SwitchScreenMenuItem<SetGasMinDisplay, TEXT_SETGASMIN>,
    SwitchScreenMenuItem<SetGasMaxDisplay, TEXT_SETGASMAX>,
    SwitchScreenMenuItem<SetBremsMinDisplay, TEXT_SETBREMSMIN>,
    SwitchScreenMenuItem<SetBremsMaxDisplay, TEXT_SETBREMSMAX>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
