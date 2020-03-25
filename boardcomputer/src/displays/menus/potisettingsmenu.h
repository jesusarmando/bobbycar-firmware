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
struct GasMinAccessor
{
    static auto getValue() { return gasMin; }
    template<typename T> static void setValue(T value) { gasMin = value; }
};
struct GasMaxAccessor
{
    static auto getValue() { return gasMax; }
    template<typename T> static void setValue(T value) { gasMax = value; }
};
struct BremsMinAccessor
{
    static auto getValue() { return bremsMin; }
    template<typename T> static void setValue(T value) { bremsMin = value; }
};
struct BremsMaxAccessor
{
    static auto getValue() { return bremsMax; }
    template<typename T> static void setValue(T value) { bremsMax = value; }
};

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
