#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class LarsmModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
using LarsmModeModeChangeDisplay = makeComponent<ChangeValueDisplay<LarsmModeMode>, StaticText<TEXT_LARSMMODECHANGEMODE>, LarsmModeModeAccessor, SwitchScreenAction<LarsmModeSettingsMenu>>;
using LarsmModeIterationsChangeDisplay = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_LARSMMODECHANGEITERATIONS>, LarsmModeIterationsAccessor, SwitchScreenAction<LarsmModeSettingsMenu>>;

class LarsmModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODECHANGEMODE>,       SwitchScreenAction<LarsmModeModeChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODECHANGEITERATIONS>, SwitchScreenAction<LarsmModeIterationsChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                      SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
