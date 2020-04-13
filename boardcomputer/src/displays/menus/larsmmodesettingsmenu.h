#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
class LarsmModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
struct LarsmModeModeAccessor : public RefAccessor<LarsmMode::Mode> { LarsmMode::Mode &getRef() const override { return modes::larsmMode.mode; } };
using LarsmModeModeChangeDisplay = makeComponent<ChangeValueDisplay<LarsmMode::Mode>, StaticText<TEXT_LARSMMODECHANGEMODE>, LarsmModeModeAccessor, SwitchScreenAction<LarsmModeSettingsMenu>>;

struct LarsmModeIterationsAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return modes::larsmMode.iterations; } };
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
