#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct GasMinAccessor { static auto &getRef() { return gasMin; } };
struct GasMaxAccessor { static auto &getRef() { return gasMax; } };
struct BremsMinAccessor { static auto &getRef() { return bremsMin; } };
struct BremsMaxAccessor { static auto &getRef() { return bremsMax; } };

template<typename Tscreen>
class PotiSettingsMenu final : public MenuDisplay<
    TEXT_POTISETTINGS,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, GasMinAccessor, PotiSettingsMenu<Tscreen>, TEXT_SETGASMIN>, TEXT_SETGASMIN>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, GasMaxAccessor, PotiSettingsMenu<Tscreen>, TEXT_SETGASMAX>, TEXT_SETGASMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, BremsMinAccessor, PotiSettingsMenu<Tscreen>, TEXT_SETBREMSMIN>, TEXT_SETBREMSMIN>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, BremsMaxAccessor, PotiSettingsMenu<Tscreen>, TEXT_SETBREMSMAX>, TEXT_SETBREMSMAX>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
