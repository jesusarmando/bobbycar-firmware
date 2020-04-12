#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WebsocketModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_WEBSOCKETMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
