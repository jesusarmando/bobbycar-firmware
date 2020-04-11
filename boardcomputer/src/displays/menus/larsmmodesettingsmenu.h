#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class LarsmModeSettingsMenu final :
    public StaticTitle<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
