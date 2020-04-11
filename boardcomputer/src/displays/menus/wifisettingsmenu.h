#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/wifiscanmenu.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WifiSettingsMenu final : public MenuDisplay<
    TEXT_WIFISETTINGS,
    SwitchScreenMenuItem<WifiScanMenu<WifiSettingsMenu<Tscreen>>, TEXT_WIFISCAN>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
