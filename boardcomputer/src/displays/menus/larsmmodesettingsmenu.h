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
class LarsmModeModeChangeDisplay :
    public StaticText<TEXT_LARSMMODECHANGEMODE>,
    public ChangeValueDisplay<LarsmMode::Mode>,
    public LarsmModeModeAccessor
{
    using Base = ChangeValueDisplay<LarsmMode::Mode>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class LarsmModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODECHANGEMODE>, DefaultFont, DefaultColor, SwitchScreenAction<LarsmModeModeChangeDisplay<LarsmModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
