#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
struct DefaultModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::defaultMode.ctrlTyp; } };
template<typename Tscreen>
class DefaultModeCtrlTypChangeDisplay :
    public StaticTitle<TEXT_SETCONTROLTYPE>,
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
    public StaticTitle<TEXT_SETCONTROLMODE>,
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
    public StaticTitle<TEXT_ENABLEWEAKENINGSMOOTHENING>,
    public ChangeValueDisplay<bool>,
    public DefaultModeEnableFieldWeakeningSmootheningAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct DefaultModeWeakeningSmootheningAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.weakeningSmoothening; } };
template<typename Tscreen>
class DefaultModeWeakeningSmootheningChangeDisplay :
    public StaticTitle<TEXT_SETWEAKINGSMOOTHENING>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeWeakeningSmootheningAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeFrontPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.frontPercentage; } };
template<typename Tscreen>
class DefaultModeFrontPercentageChangeDisplay :
    public StaticTitle<TEXT_SETFRONTPERCENTAGE>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeFrontPercentageAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeBackPercentageAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.backPercentage; } };
template<typename Tscreen>
class DefaultModeBackPercentageChangeDisplay :
    public StaticTitle<TEXT_SETBACKPERCENTAGE>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeBackPercentageAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeAddSchwelleAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.add_schwelle; } };
template<typename Tscreen>
class DefaultModeAddSchwelleChangeDisplay :
    public StaticTitle<TEXT_SETADDSCHWELLE>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeAddSchwelleAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeGas1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas1_wert; } };
template<typename Tscreen>
class DefaultModeGas1WertChangeDisplay :
    public StaticTitle<TEXT_SETGAS1WERT>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeGas1WertAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeGas2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.gas2_wert; } };
template<typename Tscreen>
class DefaultModeGas2WertChangeDisplay :
    public StaticTitle<TEXT_SETGAS2WERT>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeGas2WertAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeBrems1WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems1_wert; } };
template<typename Tscreen>
class DefaultModeBrems1WertChangeDisplay :
    public StaticTitle<TEXT_SETBREMS1WERT>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeBrems1WertAccessor,
    public SwitchScreenAction<Tscreen>
{};

struct DefaultModeBrems2WertAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.brems2_wert; } };
template<typename Tscreen>
class DefaultModeBrems2WertChangeDisplay :
    public StaticTitle<TEXT_SETBREMS2WERT>,
    public ChangeValueDisplay<int16_t>,
    public DefaultModeBrems2WertAccessor,
    public SwitchScreenAction<Tscreen>
{};

template<typename Tscreen>
class DefaultModeSettingsMenu final :
    public StaticTitle<TEXT_DEFAULTMODESETTIGNS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLTYPE>,
        StaticSwitchScreenMenuItem<DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLMODE>,
        StaticSwitchScreenMenuItem<DefaultModeEnableFieldWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_ENABLEWEAKENINGSMOOTHENING>,
        StaticSwitchScreenMenuItem<DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETWEAKINGSMOOTHENING>,
        StaticSwitchScreenMenuItem<DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETFRONTPERCENTAGE>,
        StaticSwitchScreenMenuItem<DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBACKPERCENTAGE>,
        StaticSwitchScreenMenuItem<DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETADDSCHWELLE>,
        StaticSwitchScreenMenuItem<DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETGAS1WERT>,
        StaticSwitchScreenMenuItem<DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETGAS2WERT>,
        StaticSwitchScreenMenuItem<DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBREMS1WERT>,
        StaticSwitchScreenMenuItem<DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBREMS2WERT>,
        BackMenuItem<Tscreen>
    >
{};
}
