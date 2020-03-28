#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/manualmode.h"

namespace {
struct ManualModeCtrlTypAccessor { static auto &getRef() { return modes::manualMode.ctrlTyp; } };
struct ManualModeCtrlModAccessor { static auto &getRef() { return modes::manualMode.ctrlMod; } };

template<typename Tscreen>
class ManualModeSettingsMenu final : public MenuDisplay<
    TEXT_MANUALMODESETTINGS,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, ManualModeSettingsMenu<Tscreen>, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, ManualModeSettingsMenu<Tscreen>, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
