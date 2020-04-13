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
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
struct DefaultModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::defaultMode.ctrlTyp; } };
using DefaultModeCtrlTypChangeDisplay = makeComponent<ChangeValueDisplay<ControlType>, StaticText<TEXT_SETCONTROLTYPE>, DefaultModeCtrlTypAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::defaultMode.ctrlMod; } };
using DefaultModeCtrlModChangeDisplay = makeComponent<ChangeValueDisplay<ControlMode>, StaticText<TEXT_SETCONTROLMODE>, DefaultModeCtrlModAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeEnableFieldWeakeningSmootheningAccessor : public RefAccessor<bool> { bool &getRef() const override { return modes::defaultMode.enableWeakeningSmoothening; } };

struct DefaultModeWeakeningSmootheningAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.weakeningSmoothening; } };
using DefaultModeWeakeningSmootheningChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETWEAKINGSMOOTHENING>, DefaultModeWeakeningSmootheningAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeFrontPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.frontPercentage; } };
using DefaultModeFrontPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFRONTPERCENTAGE>, DefaultModeFrontPercentageAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeBackPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.backPercentage; } };
using DefaultModeBackPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBACKPERCENTAGE>, DefaultModeBackPercentageAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeAddSchwelleAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.add_schwelle; } };
using DefaultModeAddSchwelleChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETADDSCHWELLE>, DefaultModeAddSchwelleAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeGas1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas1_wert; } };
using DefaultModeGas1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS1WERT>, DefaultModeGas1WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeGas2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas2_wert; } };
using DefaultModeGas2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS2WERT>, DefaultModeGas2WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeBrems1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems1_wert; } };
using DefaultModeBrems1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS1WERT>, DefaultModeBrems1WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

struct DefaultModeBrems2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems2_wert; } };
using DefaultModeBrems2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS2WERT>, DefaultModeBrems2WertAccessor, SwitchScreenAction<DefaultModeSettingsMenu>>;

class DefaultModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEFAULTMODESETTIGNS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>,             SwitchScreenAction<DefaultModeCtrlTypChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>,             SwitchScreenAction<DefaultModeCtrlModChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEWEAKENINGSMOOTHENING>, ToggleBoolAction, CheckboxIcon, DefaultModeEnableFieldWeakeningSmootheningAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_SETWEAKINGSMOOTHENING>,      SwitchScreenAction<DefaultModeWeakeningSmootheningChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPERCENTAGE>,         SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPERCENTAGE>,          SwitchScreenAction<DefaultModeBackPercentageChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETADDSCHWELLE>,             SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS1WERT>,                SwitchScreenAction<DefaultModeGas1WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS2WERT>,                SwitchScreenAction<DefaultModeGas2WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS1WERT>,              SwitchScreenAction<DefaultModeBrems1WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS2WERT>,              SwitchScreenAction<DefaultModeBrems2WertChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                       SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
