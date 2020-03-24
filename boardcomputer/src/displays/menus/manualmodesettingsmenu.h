#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetManualModeCtrlTypDisplay;
class SetManualModeCtrlModDisplay;
class SettingsMenu;
}

namespace {
class ManualModeSettingsMenu final : public MenuDisplay<
    TEXT_MANUALMODESETTINGS,
    SwitchScreenMenuItem<SetManualModeCtrlTypDisplay, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<SetManualModeCtrlModDisplay, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
