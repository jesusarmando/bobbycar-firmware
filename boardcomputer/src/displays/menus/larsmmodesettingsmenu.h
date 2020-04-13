#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
struct LarsmModeModeAccessor : public RefAccessor<LarsmMode::Mode> { LarsmMode::Mode &getRef() const override { return modes::larsmMode.mode; } };
template<typename Tscreen>
using LarsmModeModeChangeDisplay = makeComponent<ChangeValueDisplay<LarsmMode::Mode>, StaticText<TEXT_LARSMMODECHANGEMODE>, LarsmModeModeAccessor, SwitchScreenAction<Tscreen>>;

struct LarsmModeIterationsAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return modes::larsmMode.iterations; } };
template<typename Tscreen>
using LarsmModeIterationsChangeDisplay = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_LARSMMODECHANGEITERATIONS>, LarsmModeIterationsAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class LarsmModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODECHANGEMODE>,       SwitchScreenAction<LarsmModeModeChangeDisplay<LarsmModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODECHANGEITERATIONS>, SwitchScreenAction<LarsmModeIterationsChangeDisplay<LarsmModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                      SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
