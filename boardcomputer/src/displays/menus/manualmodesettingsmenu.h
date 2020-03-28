#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/manualmode.h"

namespace {
struct ManualModeCtrlTypAccessor { static auto &getRef() { return modes::manualMode.ctrlTyp; } };
template<typename Tscreen>
using ManualModeCtrlTypChangeScreen = ChangeValueDisplay<ControlType, ManualModeCtrlTypAccessor, Tscreen, TEXT_SETCONTROLMODE>;

struct ManualModeCtrlModAccessor { static auto &getRef() { return modes::manualMode.ctrlMod; } };
template<typename Tscreen>
using ManualModeCtrlModChangeScreen = ChangeValueDisplay<ControlMode, ManualModeCtrlModAccessor, Tscreen, TEXT_SETCONTROLMODE>;

template<typename Tscreen>
class ManualModeSettingsMenu final : public MenuDisplay<
    TEXT_MANUALMODESETTINGS,
    SwitchScreenMenuItem<ManualModeCtrlTypChangeScreen<ManualModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<ManualModeCtrlModChangeScreen<ManualModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
