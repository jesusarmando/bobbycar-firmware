#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class SelectModeMenu;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
struct IMotMaxAccessor
{
    static auto getValue() { return settings.iMotMax; }
    template<typename T> static void setValue(T value) { settings.iMotMax = value; }
};
struct IDcMaxAccessor
{
    static auto getValue() { return settings.iDcMax; }
    template<typename T> static void setValue(T value) { settings.iDcMax = value; }
};
struct NMotMaxAccessor
{
    static auto getValue() { return settings.nMotMax; }
    template<typename T> static void setValue(T value) { settings.nMotMax = value; }
};
struct FieldWeakMaxAccessor
{
    static auto getValue() { return settings.nMotMax; }
    template<typename T> static void setValue(T value) { settings.nMotMax = value; }
};
struct PhaseAdvMaxAccessor
{
    static auto getValue() { return settings.phaseAdvMax; }
    template<typename T> static void setValue(T value) { settings.phaseAdvMax = value; }
};

class CommonSettingsMenu final : public MenuDisplay<
    TEXT_COMMONSETTINGS,
    SwitchScreenMenuItem<SelectModeMenu, TEXT_SELECTMODE>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, IMotMaxAccessor, CommonSettingsMenu, TEXT_SETIMOTMAX>, TEXT_SETIMOTMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, IDcMaxAccessor, CommonSettingsMenu, TEXT_SETIDCMAX>, TEXT_SETIDCMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, NMotMaxAccessor, CommonSettingsMenu, TEXT_SETNMOTMAX>, TEXT_SETNMOTMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX>, TEXT_SETFIELDWEAKMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, CommonSettingsMenu, TEXT_SETPHASEADVMAX>, TEXT_SETPHASEADVMAX>,
    SwitchScreenMenuItem<EnableMenu, TEXT_SETENABLED>,
    SwitchScreenMenuItem<InvertMenu, TEXT_SETINVERTED>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
