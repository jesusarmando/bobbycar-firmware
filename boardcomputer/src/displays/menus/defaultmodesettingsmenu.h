#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
struct DefaultModeCtrlTypAccessor { static auto &getRef() { return modes::defaultMode.ctrlTyp; } };
template<typename Tscreen>
using DefaultModeCtrlTypChangeDisplay = ChangeValueDisplay<ControlType, DefaultModeCtrlTypAccessor, Tscreen, TEXT_SETCONTROLTYPE>;

struct DefaultModeCtrlModAccessor { static auto &getRef() { return modes::defaultMode.ctrlMod; } };
template<typename Tscreen>
using DefaultModeCtrlModChangeDisplay = ChangeValueDisplay<ControlMode, DefaultModeCtrlModAccessor, Tscreen, TEXT_SETCONTROLMODE>;

struct DefaultModeEnableFieldWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.enableWeakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeEnableFieldWeakeningSmootheningChangeDisplay = ChangeValueDisplay<bool, DefaultModeEnableFieldWeakeningSmootheningAccessor, Tscreen, TEXT_ENABLEWEAKENINGSMOOTHENING>;

struct DefaultModeWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.weakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeWeakeningSmootheningChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeWeakeningSmootheningAccessor, Tscreen, TEXT_SETWEAKINGSMOOTHENING>;

struct DefaultModeFrontPercentageAccessor { static auto &getRef() { return modes::defaultMode.frontPercentage; } };
template<typename Tscreen>
using DefaultModeFrontPercentageChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeFrontPercentageAccessor, Tscreen, TEXT_SETFRONTPERCENTAGE>;

struct DefaultModeBackPercentageAccessor { static auto &getRef() { return modes::defaultMode.backPercentage; } };
template<typename Tscreen>
using DefaultModeBackPercentageChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeBackPercentageAccessor, Tscreen, TEXT_SETBACKPERCENTAGE>;

struct DefaultModeAddSchwelleAccessor { static auto &getRef() { return modes::defaultMode.add_schwelle; } };
template<typename Tscreen>
using DefaultModeAddSchwelleChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeAddSchwelleAccessor, Tscreen, TEXT_SETADDSCHWELLE>;

struct DefaultModeGas1WertAccessor { static auto &getRef() { return modes::defaultMode.gas1_wert; } };
template<typename Tscreen>
using DefaultModeGas1WertChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeGas1WertAccessor, Tscreen, TEXT_SETGAS1WERT>;

struct DefaultModeGas2WertAccessor { static auto &getRef() { return modes::defaultMode.gas2_wert; } };
template<typename Tscreen>
using DefaultModeGas2WertChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeGas2WertAccessor, Tscreen, TEXT_SETGAS2WERT>;

struct DefaultModeBrems1WertAccessor { static auto &getRef() { return modes::defaultMode.brems1_wert; } };
template<typename Tscreen>
using DefaultModeBrems1WertChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeBrems1WertAccessor, Tscreen, TEXT_SETBREMS1WERT>;

struct DefaultModeBrems2WertAccessor { static auto &getRef() { return modes::defaultMode.brems2_wert; } };
template<typename Tscreen>
using DefaultModeBrems2WertChangeDisplay = ChangeValueDisplay<int16_t, DefaultModeBrems2WertAccessor, Tscreen, TEXT_SETBREMS2WERT>;

template<typename Tscreen>
class DefaultModeSettingsMenu final : public MenuDisplay<
    TEXT_DEFAULTMODESETTIGNS,
    SwitchScreenMenuItem<DefaultModeCtrlTypChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<DefaultModeCtrlModChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<DefaultModeEnableFieldWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_ENABLEWEAKENINGSMOOTHENING>,
    SwitchScreenMenuItem<DefaultModeWeakeningSmootheningChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETWEAKINGSMOOTHENING>,
    SwitchScreenMenuItem<DefaultModeFrontPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETFRONTPERCENTAGE>,
    SwitchScreenMenuItem<DefaultModeBackPercentageChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBACKPERCENTAGE>,
    SwitchScreenMenuItem<DefaultModeAddSchwelleChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETADDSCHWELLE>,
    SwitchScreenMenuItem<DefaultModeGas1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETGAS1WERT>,
    SwitchScreenMenuItem<DefaultModeGas2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETGAS2WERT>,
    SwitchScreenMenuItem<DefaultModeBrems1WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBREMS1WERT>,
    SwitchScreenMenuItem<DefaultModeBrems2WertChangeDisplay<DefaultModeSettingsMenu<Tscreen>>, TEXT_SETBREMS2WERT>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
