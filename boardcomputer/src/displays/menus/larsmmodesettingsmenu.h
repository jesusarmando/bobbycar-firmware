#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
struct LarsmModeModeAccessor : public RefAccessor<LarsmMode::Mode> { LarsmMode::Mode &getRef() const override { return modes::larsmMode.mode; } };
template<typename Tscreen>
class LarsmModeModeChangeDisplay :
    public StaticTitle<TEXT_LARSMMODECHANGEMODE>,
    public ChangeValueDisplay<LarsmMode::Mode>,
    public LarsmModeModeAccessor
{
    using Base = ChangeValueDisplay<LarsmMode::Mode>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class LarsmModeSettingsMenu final :
    public StaticTitle<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<LarsmModeModeChangeDisplay<LarsmModeSettingsMenu<Tscreen>>, TEXT_LARSMMODECHANGEMODE>,
        BackMenuItem<Tscreen>
    >
{};
}
