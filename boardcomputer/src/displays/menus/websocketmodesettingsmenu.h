#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WebsocketModeSettingsMenu :
    public StaticText<TEXT_WEBSOCKETMODESETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_BACK>, DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >
{};
}
