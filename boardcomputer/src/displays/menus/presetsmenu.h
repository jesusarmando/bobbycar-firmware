#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/dummymenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class PresetsMenu : public MenuDisplay<
    TEXT_PRESETS,
    DummyMenuItem<TEXT_STREET>,
    DummyMenuItem<TEXT_SIDEWALK>,
    DummyMenuItem<TEXT_POLICE>,
    DummyMenuItem<TEXT_RACE>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
