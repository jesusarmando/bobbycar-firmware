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
class TempomatModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
struct TempomatModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::tempomatMode.ctrlTyp; } };
using TempomatModeCtrlTypChangeScreen = makeComponent<ChangeValueDisplay<ControlType>, StaticText<TEXT_SETCONTROLMODE>, TempomatModeCtrlTypAccessor, SwitchScreenAction<TempomatModeSettingsMenu>>;

struct TempomatModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::tempomatMode.ctrlMod; } };
using TempomatModeCtrlModChangeScreen = makeComponent<ChangeValueDisplay<ControlMode>, StaticText<TEXT_SETCONTROLMODE>, TempomatModeCtrlModAccessor, SwitchScreenAction<TempomatModeSettingsMenu>>;

class TempomatModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TEMPOMATMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>, SwitchScreenAction<TempomatModeCtrlTypChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>, SwitchScreenAction<TempomatModeCtrlModChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,           SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
