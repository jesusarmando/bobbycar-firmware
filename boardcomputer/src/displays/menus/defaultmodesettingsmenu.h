#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class DefaultModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
using DefaultModeCtrlTypChangeDisplay = makeComponent<ChangeValueDisplay<ControlType>, StaticText<TEXT_SETCONTROLTYPE>, DefaultModeCtrlTypAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeCtrlModChangeDisplay = makeComponent<ChangeValueDisplay<ControlMode>, StaticText<TEXT_SETCONTROLMODE>, DefaultModeCtrlModAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeSmoothingChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETSMOOTHING>, DefaultModeSmoothingAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeFrontPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFRONTPERCENTAGE>, DefaultModeFrontPercentageAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeBackPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBACKPERCENTAGE>, DefaultModeBackPercentageAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeAddSchwelleChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETADDSCHWELLE>, DefaultModeAddSchwelleAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeGas1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS1WERT>, DefaultModeGas1WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeGas2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS2WERT>, DefaultModeGas2WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeBrems1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS1WERT>, DefaultModeBrems1WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;
using DefaultModeBrems2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS2WERT>, DefaultModeBrems2WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

class DefaultModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEFAULTMODESETTIGNS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>,     SwitchScreenAction<DefaultModeCtrlTypChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>,     SwitchScreenAction<DefaultModeCtrlModChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLESMOOTHING>,     ToggleBoolAction, CheckboxIcon, DefaultModeEnableSmoothingAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_SETSMOOTHING>,       SwitchScreenAction<DefaultModeSmoothingChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPERCENTAGE>, SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPERCENTAGE>,  SwitchScreenAction<DefaultModeBackPercentageChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETADDSCHWELLE>,     SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS1WERT>,        SwitchScreenAction<DefaultModeGas1WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS2WERT>,        SwitchScreenAction<DefaultModeGas2WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS1WERT>,      SwitchScreenAction<DefaultModeBrems1WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS2WERT>,      SwitchScreenAction<DefaultModeBrems2WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
