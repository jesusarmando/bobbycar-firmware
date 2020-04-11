#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WebsocketModeSettingsMenu final :
    public StaticTitle<TEXT_WEBSOCKETMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
