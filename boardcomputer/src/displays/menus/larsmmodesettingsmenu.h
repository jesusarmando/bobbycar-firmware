#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/larsmmode.h"
#include "accessorhelper.h"

namespace {
struct LarsmModeModeAccessor { static auto &getRef() { return modes::larsmMode.mode; } };
template<typename Tscreen>
using LarsmModeModeChangeDisplay = ChangeValueDisplay<LarsmMode::Mode, AccessorHelper<LarsmModeModeAccessor>, Tscreen, TEXT_LARSMMODECHANGEMODE>;

template<typename Tscreen>
class LarsmModeSettingsMenu final :
    public StaticTitle<TEXT_LARSMMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<LarsmModeModeChangeDisplay<LarsmModeSettingsMenu<Tscreen>>, TEXT_LARSMMODECHANGEMODE>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
