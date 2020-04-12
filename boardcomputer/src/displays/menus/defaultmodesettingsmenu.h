#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
struct DefaultModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::defaultMode.ctrlTyp; } };
template<typename Tscreen>
class DefaultModeCtrlTypChangeDisplay :
    public StaticText<TEXT_SETCONTROLTYPE>,
    public ChangeValueDisplay<ControlType>,
    public DefaultModeCtrlTypAccessor
{
    using Base = ChangeValueDisplay<ControlType>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct DefaultModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::defaultMode.ctrlMod; } };
template<typename Tscreen>
class DefaultModeCtrlModChangeDisplay :
    public StaticText<TEXT_SETCONTROLMODE>,
    public ChangeValueDisplay<ControlMode>,
    public DefaultModeCtrlModAccessor
{
    using Base = ChangeValueDisplay<ControlMode>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct DefaultModeEnableFieldWeakeningSmootheningAccessor : public RefAccessor<bool> { bool &getRef() const override { return modes::defaultMode.enableWeakeningSmoothening; } };
template<typename Tscreen>
class DefaultModeEnableFieldWeakeningSmootheningChangeDisplay :
    public StaticText<TEXT_ENABLEWEAKENINGSMOOTHENING>,
    public ChangeValueDisplay<bool>,
    public DefaultModeEnableFieldWeakeningSmootheningAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

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
    public StaticText<TEXT_DEFAULTMODESETTIGNS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>,             DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>,             DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEWEAKENINGSMOOTHENING>, DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeEnableFieldWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETWEAKINGSMOOTHENING>,      DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTPERCENTAGE>,         DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKPERCENTAGE>,          DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETADDSCHWELLE>,             DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS1WERT>,                DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAS2WERT>,                DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS1WERT>,              DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMS2WERT>,              DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                       DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >
{};
}
