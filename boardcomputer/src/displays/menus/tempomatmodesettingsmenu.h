#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/tempomatmode.h"

namespace {
struct TempomatModeCtrlTypAccessor { static auto &getRef() { return modes::tempomatMode.ctrlTyp; } };
template<typename Tscreen>
using TempomatModeCtrlTypChangeScreen = ChangeValueDisplay<ControlType, TempomatModeCtrlTypAccessor, Tscreen, TEXT_SETCONTROLMODE>;

struct TempomatModeCtrlModAccessor { static auto &getRef() { return modes::tempomatMode.ctrlMod; } };
template<typename Tscreen>
using TempomatModeCtrlModChangeScreen = ChangeValueDisplay<ControlMode, TempomatModeCtrlModAccessor, Tscreen, TEXT_SETCONTROLMODE>;

template<typename Tscreen>
class TempomatModeSettingsMenu final :
    public StaticTitle<TEXT_TEMPOMATMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLTYPE>,
        StaticSwitchScreenMenuItem<TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLMODE>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
