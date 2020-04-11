#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class PresetsMenu :
    public StaticTitle<TEXT_PRESETS>,
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_STREET>,
        StaticDummyMenuItem<TEXT_SIDEWALK>,
        StaticDummyMenuItem<TEXT_POLICE>,
        StaticDummyMenuItem<TEXT_RACE>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
