#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/manualmode.h"

namespace {
class SettingsMenu;
}

namespace {
struct ManualModeCtrlTypAccessor { static auto &getRef() { return modes::manualMode.ctrlTyp; } };
struct ManualModeCtrlModAccessor { static auto &getRef() { return modes::manualMode.ctrlMod; } };

class ManualModeSettingsMenu final : public MenuDisplay<
    TEXT_MANUALMODESETTINGS,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
