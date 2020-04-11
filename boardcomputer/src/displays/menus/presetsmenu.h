#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/dummymenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class PresetsMenu : public MenuDisplay<
    TEXT_PRESETS,
    StaticDummyMenuItem<TEXT_STREET>,
    StaticDummyMenuItem<TEXT_SIDEWALK>,
    StaticDummyMenuItem<TEXT_POLICE>,
    StaticDummyMenuItem<TEXT_RACE>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
