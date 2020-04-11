#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "accessorhelper.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "texts.h"
#include "globals.h"

namespace {
struct IMotMaxAccessor { static auto &getRef() { return settings.iMotMax; } };
template<typename Tscreen>
using IMotMaxChangeScreen = ChangeValueDisplay<int16_t, AccessorHelper<IMotMaxAccessor>, Tscreen, TEXT_SETIMOTMAX>;

struct IDcMaxAccessor { static auto &getRef() { return settings.iDcMax; } };
template<typename Tscreen>
using IDcMaxChangeScreen = ChangeValueDisplay<int16_t, AccessorHelper<IDcMaxAccessor>, Tscreen, TEXT_SETIDCMAX>;

struct NMotMaxAccessor { static auto &getRef() { return settings.nMotMax; } };
template<typename Tscreen>
using NMotMaxChangeScreen = ChangeValueDisplay<int16_t, AccessorHelper<NMotMaxAccessor>, Tscreen, TEXT_SETNMOTMAX>;

struct FieldWeakMaxAccessor { static auto &getRef() { return settings.fieldWeakMax; } };
template<typename Tscreen>
using FieldWeakMaxChangeScreen = ChangeValueDisplay<int16_t, AccessorHelper<FieldWeakMaxAccessor>, Tscreen, TEXT_SETFIELDWEAKMAX>;

struct PhaseAdvMaxAccessor { static auto &getRef() { return settings.phaseAdvMax; } };
template<typename Tscreen>
using PhaseAdvMaxChangeScreen = ChangeValueDisplay<int16_t, AccessorHelper<PhaseAdvMaxAccessor>, Tscreen, TEXT_SETPHASEADVMAX>;

template<typename Tscreen>
class CommonSettingsMenu final :
    public StaticTitle<TEXT_COMMONSETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<IMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIMOTMAX>,
        StaticSwitchScreenMenuItem<IDcMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETIDCMAX>,
        StaticSwitchScreenMenuItem<NMotMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETNMOTMAX>,
        StaticSwitchScreenMenuItem<FieldWeakMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETFIELDWEAKMAX>,
        StaticSwitchScreenMenuItem<PhaseAdvMaxChangeScreen<CommonSettingsMenu<Tscreen>>, TEXT_SETPHASEADVMAX>,
        StaticSwitchScreenMenuItem<EnableMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETENABLED>,
        StaticSwitchScreenMenuItem<InvertMenu<CommonSettingsMenu<Tscreen>>, TEXT_SETINVERTED>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
