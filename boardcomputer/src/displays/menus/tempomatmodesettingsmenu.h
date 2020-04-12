#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/tempomatmode.h"

namespace {
struct TempomatModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::tempomatMode.ctrlTyp; } };
template<typename Tscreen>
using TempomatModeCtrlTypChangeScreen = makeComponent<ChangeValueDisplay<ControlType>, StaticText<TEXT_SETCONTROLMODE>, TempomatModeCtrlTypAccessor, SwitchScreenAction<Tscreen>>;

struct TempomatModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::tempomatMode.ctrlMod; } };
template<typename Tscreen>
using TempomatModeCtrlModChangeScreen = makeComponent<ChangeValueDisplay<ControlMode>, StaticText<TEXT_SETCONTROLMODE>, TempomatModeCtrlModAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class TempomatModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TEMPOMATMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>, SwitchScreenAction<TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>, SwitchScreenAction<TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,           SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
