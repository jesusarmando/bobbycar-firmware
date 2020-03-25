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
struct DefaultModeCtrlTypAccessor
{
    static auto getValue() { return modes::defaultMode.ctrlTyp; }
    template<typename T> static void setValue(T value) { modes::defaultMode.ctrlTyp = value; }
};
struct DefaultModeCtrlModAccessor
{
    static auto getValue() { return modes::defaultMode.ctrlMod; }
    template<typename T> static void setValue(T value) { modes::defaultMode.ctrlMod = value; }
};
struct DefaultModeEnableFieldWeakeningSmootheningAccessor
{
    static auto getValue() { return modes::defaultMode.enableWeakeningSmoothening; }
    template<typename T> static void setValue(T value) { modes::defaultMode.enableWeakeningSmoothening = value; }
};
struct DefaultModeWeakeningSmootheningAccessor
{
    static auto getValue() { return modes::defaultMode.weakeningSmoothening; }
    template<typename T> static void setValue(T value) { modes::defaultMode.weakeningSmoothening = value; }
};
struct DefaultModeFrontPercentageAccessor
{
    static auto getValue() { return modes::defaultMode.frontPercentage; }
    template<typename T> static void setValue(T value) { modes::defaultMode.frontPercentage = value; }
};
struct DefaultModeBackPercentageAccessor
{
    static auto getValue() { return modes::defaultMode.backPercentage; }
    template<typename T> static void setValue(T value) { modes::defaultMode.backPercentage = value; }
};
struct DefaultModeAddSchwelleAccessor
{
    static auto getValue() { return modes::defaultMode.add_schwelle; }
    template<typename T> static void setValue(T value) { modes::defaultMode.add_schwelle = value; }
};
struct DefaultModeGas1WertAccessor
{
    static auto getValue() { return modes::defaultMode.gas1_wert; }
    template<typename T> static void setValue(T value) { modes::defaultMode.gas1_wert = value; }
};
struct DefaultModeGas2WertAccessor
{
    static auto getValue() { return modes::defaultMode.gas2_wert; }
    template<typename T> static void setValue(T value) { modes::defaultMode.gas2_wert = value; }
};
struct DefaultModeBrems1WertAccessor
{
    static auto getValue() { return modes::defaultMode.brems1_wert; }
    template<typename T> static void setValue(T value) { modes::defaultMode.brems1_wert = value; }
};
struct DefaultModeBrems2WertAccessor
{
    static auto getValue() { return modes::defaultMode.brems2_wert; }
    template<typename T> static void setValue(T value) { modes::defaultMode.brems2_wert = value; }
};

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
