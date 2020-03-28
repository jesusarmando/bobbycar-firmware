#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/selectmodemenu.h"
#include "changevaluedisplay.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "texts.h"
#include "globals.h"

namespace {
struct IMotMaxAccessor { static auto &getRef() { return settings.iMotMax; } };
struct IDcMaxAccessor { static auto &getRef() { return settings.iDcMax; } };
struct NMotMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
struct FieldWeakMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
struct PhaseAdvMaxAccessor { static auto &getRef() { return settings.phaseAdvMax; } };

template<typename Tscreen>
class CommonSettingsMenu final : public MenuDisplay<
    TEXT_COMMONSETTINGS,
    SwitchScreenMenuItem<SelectModeMenu<CommonSettingsMenu<Tscreen>>, TEXT_SELECTMODE>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, IMotMaxAccessor, CommonSettingsMenu<Tscreen>, TEXT_SETIMOTMAX>, TEXT_SETIMOTMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, IDcMaxAccessor, CommonSettingsMenu<Tscreen>, TEXT_SETIDCMAX>, TEXT_SETIDCMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, NMotMaxAccessor, CommonSettingsMenu<Tscreen>, TEXT_SETNMOTMAX>, TEXT_SETNMOTMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, CommonSettingsMenu<Tscreen>, TEXT_SETFIELDWEAKMAX>, TEXT_SETFIELDWEAKMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, CommonSettingsMenu<Tscreen>, TEXT_SETPHASEADVMAX>, TEXT_SETPHASEADVMAX>,
    SwitchScreenMenuItem<EnableMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETENABLED>,
    SwitchScreenMenuItem<InvertMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETINVERTED>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
