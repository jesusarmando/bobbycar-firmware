#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
struct DefaultModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::defaultMode.ctrlTyp; } };
template<typename Tscreen>
using DefaultModeCtrlTypChangeDisplay = makeComponent<ChangeValueDisplay<ControlType>, StaticText<TEXT_SETCONTROLTYPE>, DefaultModeCtrlTypAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::defaultMode.ctrlMod; } };
template<typename Tscreen>
using DefaultModeCtrlModChangeDisplay = makeComponent<ChangeValueDisplay<ControlMode>, StaticText<TEXT_SETCONTROLMODE>, DefaultModeCtrlModAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeEnableFieldWeakeningSmootheningAccessor : public RefAccessor<bool> { bool &getRef() const override { return modes::defaultMode.enableWeakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeEnableFieldWeakeningSmootheningChangeDisplay = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_ENABLEWEAKENINGSMOOTHENING>, DefaultModeEnableFieldWeakeningSmootheningAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeWeakeningSmootheningAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.weakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeWeakeningSmootheningChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETWEAKINGSMOOTHENING>, DefaultModeWeakeningSmootheningAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeFrontPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.frontPercentage; } };
template<typename Tscreen>
using DefaultModeFrontPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETFRONTPERCENTAGE>, DefaultModeFrontPercentageAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeBackPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.backPercentage; } };
template<typename Tscreen>
using DefaultModeBackPercentageChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBACKPERCENTAGE>, DefaultModeBackPercentageAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeAddSchwelleAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.add_schwelle; } };
template<typename Tscreen>
using DefaultModeAddSchwelleChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETADDSCHWELLE>, DefaultModeAddSchwelleAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeGas1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas1_wert; } };
template<typename Tscreen>
using DefaultModeGas1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS1WERT>, DefaultModeGas1WertAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeGas2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas2_wert; } };
template<typename Tscreen>
using DefaultModeGas2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETGAS2WERT>, DefaultModeGas2WertAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeBrems1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems1_wert; } };
template<typename Tscreen>
using DefaultModeBrems1WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS1WERT>, DefaultModeBrems1WertAccessor, SwitchScreenAction<Tscreen>>;

struct DefaultModeBrems2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems2_wert; } };
template<typename Tscreen>
using DefaultModeBrems2WertChangeDisplay = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_SETBREMS2WERT>, DefaultModeBrems2WertAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class DefaultModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEFAULTMODESETTIGNS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>,             SwitchScreenAction<DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>,             SwitchScreenAction<DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEWEAKENINGSMOOTHENING>, SwitchScreenAction<DefaultModeEnableFieldWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETWEAKINGSMOOTHENING>,      SwitchScreenAction<DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPERCENTAGE>,         SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPERCENTAGE>,          SwitchScreenAction<DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETADDSCHWELLE>,             SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS1WERT>,                SwitchScreenAction<DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS2WERT>,                SwitchScreenAction<DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS1WERT>,              SwitchScreenAction<DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS2WERT>,              SwitchScreenAction<DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                       SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
