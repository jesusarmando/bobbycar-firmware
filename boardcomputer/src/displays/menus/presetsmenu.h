#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class MainMenu;
}

namespace {
class PresetsMenu :
    public MenuDisplay,
    public StaticText<TEXT_PRESETS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_STREET>,   DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SIDEWALK>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_POLICE>,   DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_RACE>,     DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,     SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
