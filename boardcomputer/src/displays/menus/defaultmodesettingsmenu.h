#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "accessorhelper.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
struct DefaultModeCtrlTypAccessor { static auto &getRef() { return modes::defaultMode.ctrlTyp; } };
template<typename Tscreen>
using DefaultModeCtrlTypChangeDisplay = ChangeValueDisplay<ControlType, AccessorHelper<DefaultModeCtrlTypAccessor>, Tscreen, TEXT_SETCONTROLTYPE>;

struct DefaultModeCtrlModAccessor { static auto &getRef() { return modes::defaultMode.ctrlMod; } };
template<typename Tscreen>
using DefaultModeCtrlModChangeDisplay = ChangeValueDisplay<ControlMode, AccessorHelper<DefaultModeCtrlModAccessor>, Tscreen, TEXT_SETCONTROLMODE>;

struct DefaultModeEnableFieldWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.enableWeakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeEnableFieldWeakeningSmootheningChangeDisplay = ChangeValueDisplay<bool, AccessorHelper<DefaultModeEnableFieldWeakeningSmootheningAccessor>, Tscreen, TEXT_ENABLEWEAKENINGSMOOTHENING>;

struct DefaultModeWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.weakeningSmoothening; } };
template<typename Tscreen>
using DefaultModeWeakeningSmootheningChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeWeakeningSmootheningAccessor>, Tscreen, TEXT_SETWEAKINGSMOOTHENING>;

struct DefaultModeFrontPercentageAccessor { static auto &getRef() { return modes::defaultMode.frontPercentage; } };
template<typename Tscreen>
using DefaultModeFrontPercentageChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeFrontPercentageAccessor>, Tscreen, TEXT_SETFRONTPERCENTAGE>;

struct DefaultModeBackPercentageAccessor { static auto &getRef() { return modes::defaultMode.backPercentage; } };
template<typename Tscreen>
using DefaultModeBackPercentageChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeBackPercentageAccessor>, Tscreen, TEXT_SETBACKPERCENTAGE>;

struct DefaultModeAddSchwelleAccessor { static auto &getRef() { return modes::defaultMode.add_schwelle; } };
template<typename Tscreen>
using DefaultModeAddSchwelleChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeAddSchwelleAccessor>, Tscreen, TEXT_SETADDSCHWELLE>;

struct DefaultModeGas1WertAccessor { static auto &getRef() { return modes::defaultMode.gas1_wert; } };
template<typename Tscreen>
using DefaultModeGas1WertChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeGas1WertAccessor>, Tscreen, TEXT_SETGAS1WERT>;

struct DefaultModeGas2WertAccessor { static auto &getRef() { return modes::defaultMode.gas2_wert; } };
template<typename Tscreen>
using DefaultModeGas2WertChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeGas2WertAccessor>, Tscreen, TEXT_SETGAS2WERT>;

struct DefaultModeBrems1WertAccessor { static auto &getRef() { return modes::defaultMode.brems1_wert; } };
template<typename Tscreen>
using DefaultModeBrems1WertChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeBrems1WertAccessor>, Tscreen, TEXT_SETBREMS1WERT>;

struct DefaultModeBrems2WertAccessor { static auto &getRef() { return modes::defaultMode.brems2_wert; } };
template<typename Tscreen>
using DefaultModeBrems2WertChangeDisplay = ChangeValueDisplay<int16_t, AccessorHelper<DefaultModeBrems2WertAccessor>, Tscreen, TEXT_SETBREMS2WERT>;

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
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
