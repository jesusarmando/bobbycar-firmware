#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class PresetsMenu :
    public StaticText<TEXT_PRESETS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_STREET>,   DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SIDEWALK>, DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_POLICE>,   DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_RACE>,     DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,     DefaultFont, DefaultColor,  SwitchScreenAction<Tscreen>>
    >
{};
}
