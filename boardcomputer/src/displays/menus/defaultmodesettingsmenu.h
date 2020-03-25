#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class SettingsMenu;
}

namespace {
struct DefaultModeCtrlTypAccessor { static auto &getRef() { return modes::defaultMode.ctrlTyp; } };
struct DefaultModeCtrlModAccessor { static auto &getRef() { return modes::defaultMode.ctrlMod; } };
struct DefaultModeEnableFieldWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.enableWeakeningSmoothening; } };
struct DefaultModeWeakeningSmootheningAccessor { static auto &getRef() { return modes::defaultMode.weakeningSmoothening; } };
struct DefaultModeFrontPercentageAccessor { static auto &getRef() { return modes::defaultMode.frontPercentage; } };
struct DefaultModeBackPercentageAccessor { static auto &getRef() { return modes::defaultMode.backPercentage; } };
struct DefaultModeAddSchwelleAccessor { static auto &getRef() { return modes::defaultMode.add_schwelle; } };
struct DefaultModeGas1WertAccessor { static auto &getRef() { return modes::defaultMode.gas1_wert; } };
struct DefaultModeGas2WertAccessor { static auto &getRef() { return modes::defaultMode.gas2_wert; } };
struct DefaultModeBrems1WertAccessor { static auto &getRef() { return modes::defaultMode.brems1_wert; } };
struct DefaultModeBrems2WertAccessor { static auto &getRef() { return modes::defaultMode.brems2_wert; } };

class DefaultModeSettingsMenu final : public MenuDisplay<
    TEXT_DEFAULTMODESETTIGNS,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlType, DefaultModeCtrlTypAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE>, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<ChangeValueDisplay<ControlMode, DefaultModeCtrlModAccessor, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE>, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, DefaultModeEnableFieldWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING>, TEXT_ENABLEWEAKENINGSMOOTHENING>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeWeakeningSmootheningAccessor, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING>, TEXT_SETWEAKINGSMOOTHENING>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeFrontPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE>, TEXT_SETFRONTPERCENTAGE>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeBackPercentageAccessor, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE>, TEXT_SETBACKPERCENTAGE>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeAddSchwelleAccessor, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE>, TEXT_SETADDSCHWELLE>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeGas1WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS1WERT>, TEXT_SETGAS1WERT>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeGas2WertAccessor, DefaultModeSettingsMenu, TEXT_SETGAS2WERT>, TEXT_SETGAS2WERT>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeBrems1WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT>, TEXT_SETBREMS1WERT>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, DefaultModeBrems2WertAccessor, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT>, TEXT_SETBREMS2WERT>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
