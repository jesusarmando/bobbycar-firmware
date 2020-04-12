#pragma once

#include "staticmenudisplay.h"
#include "menuitems/backmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WebsocketModeSettingsMenu final :
    public StaticTitle<TEXT_WEBSOCKETMODESETTINGS>,
    public StaticMenuDisplay<
        BackMenuItem<Tscreen>
    >
{};
}
