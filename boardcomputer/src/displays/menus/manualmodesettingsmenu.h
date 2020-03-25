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
struct ManualModeCtrlTypAccessor
{
    static auto getValue() { return modes::manualMode.ctrlTyp; }
    template<typename T> static void setValue(T value) { modes::manualMode.ctrlTyp = value; }
};
struct ManualModeCtrlModAccessor
{
    static auto getValue() { return modes::manualMode.ctrlMod; }
    template<typename T> static void setValue(T value) { modes::manualMode.ctrlMod = value; }
};

class ManualModeSettingsMenu final : public MenuDisplay<
    TEXT_MANUALMODESETTINGS,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
