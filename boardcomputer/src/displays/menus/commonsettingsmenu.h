#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "texts.h"
#include "globals.h"

namespace {
struct IMotMaxAccessor { static auto &getRef() { return settings.iMotMax; } };
template<typename Tscreen>
using IMotMaxChangeScreen = ChangeValueDisplay<int16_t, IMotMaxAccessor, Tscreen, TEXT_SETIMOTMAX>;

struct IDcMaxAccessor { static auto &getRef() { return settings.iDcMax; } };
template<typename Tscreen>
using IDcMaxChangeScreen = ChangeValueDisplay<int16_t, IDcMaxAccessor, Tscreen, TEXT_SETIDCMAX>;

struct NMotMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
template<typename Tscreen>
using NMotMaxChangeScreen = ChangeValueDisplay<int16_t, NMotMaxAccessor, Tscreen, TEXT_SETNMOTMAX>;

struct FieldWeakMaxAccessor { static auto &getRef() { return settings.fieldWeakMax; } };
template<typename Tscreen>
using FieldWeakMaxChangeScreen = ChangeValueDisplay<int16_t, FieldWeakMaxAccessor, Tscreen, TEXT_SETFIELDWEAKMAX>;

struct PhaseAdvMaxAccessor { static auto &getRef() { return settings.phaseAdvMax; } };
template<typename Tscreen>
using PhaseAdvMaxChangeScreen = ChangeValueDisplay<int16_t, PhaseAdvMaxAccessor, Tscreen, TEXT_SETPHASEADVMAX>;

template<typename Tscreen>
class CommonSettingsMenu final : public MenuDisplay<
    TEXT_COMMONSETTINGS,
    SwitchScreenMenuItem<IMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIMOTMAX>,
    SwitchScreenMenuItem<IDcMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIDCMAX>,
    SwitchScreenMenuItem<NMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETNMOTMAX>,
    SwitchScreenMenuItem<FieldWeakMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETFIELDWEAKMAX>,
    SwitchScreenMenuItem<PhaseAdvMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETPHASEADVMAX>,
    SwitchScreenMenuItem<EnableMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETENABLED>,
    SwitchScreenMenuItem<InvertMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETINVERTED>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
