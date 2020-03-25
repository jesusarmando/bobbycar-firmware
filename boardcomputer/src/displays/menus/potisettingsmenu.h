#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class SettingsMenu;
}

namespace {
struct GasMinAccessor { static auto &getRef() { return gasMin; } };
struct GasMaxAccessor { static auto &getRef() { return gasMax; } };
struct BremsMinAccessor { static auto &getRef() { return bremsMin; } };
struct BremsMaxAccessor { static auto &getRef() { return bremsMax; } };

class PotiSettingsMenu final : public MenuDisplay<
    TEXT_POTISETTINGS,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, GasMinAccessor, PotiSettingsMenu, TEXT_SETGASMIN>, TEXT_SETGASMIN>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, GasMaxAccessor, PotiSettingsMenu, TEXT_SETGASMAX>, TEXT_SETGASMAX>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, BremsMinAccessor, PotiSettingsMenu, TEXT_SETBREMSMIN>, TEXT_SETBREMSMIN>,
    SwitchScreenMenuItem<ChangeValueDisplay<int16_t, BremsMaxAccessor, PotiSettingsMenu, TEXT_SETBREMSMAX>, TEXT_SETBREMSMAX>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
