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
struct IMotMaxAccessor { static auto &getRef() { return settings.iMotMax; } };
struct IDcMaxAccessor { static auto &getRef() { return settings.iDcMax; } };
struct NMotMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
struct FieldWeakMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
struct PhaseAdvMaxAccessor { static auto &getRef() { return settings.phaseAdvMax; } };

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
