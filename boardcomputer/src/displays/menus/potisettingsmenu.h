#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "displays/calibratedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct GasMinAccessor { static auto &getRef() { return gasMin; } };
template<typename Tscreen>
using GasMinChangeScreen = ChangeValueDisplay<int16_t, GasMinAccessor, Tscreen, TEXT_SETGASMIN>;

struct GasMaxAccessor { static auto &getRef() { return gasMax; } };
template<typename Tscreen>
using GasMaxChangeScreen = ChangeValueDisplay<int16_t, GasMaxAccessor, Tscreen, TEXT_SETGASMAX>;

struct BremsMinAccessor { static auto &getRef() { return bremsMin; } };
template<typename Tscreen>
using BremsMinChangeScreen = ChangeValueDisplay<int16_t, BremsMinAccessor, Tscreen, TEXT_SETBREMSMIN>;

struct BremsMaxAccessor { static auto &getRef() { return bremsMax; } };
template<typename Tscreen>
using BremsMaxChangeScreen = ChangeValueDisplay<int16_t, BremsMaxAccessor, Tscreen, TEXT_SETBREMSMAX>;

template<typename Tscreen>
class PotiSettingsMenu final :
    public StaticTitle<TEXT_POTISETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<GasMinChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETGASMIN>,
        StaticSwitchScreenMenuItem<GasMaxChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETGASMAX>,
        StaticSwitchScreenMenuItem<BremsMinChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETBREMSMIN>,
        StaticSwitchScreenMenuItem<BremsMaxChangeScreen<PotiSettingsMenu<Tscreen>>, TEXT_SETBREMSMAX>,
        StaticSwitchScreenMenuItem<CalibrateDisplay<PotiSettingsMenu<Tscreen>>, TEXT_CALIBRATE>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
