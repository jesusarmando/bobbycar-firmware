#pragma once

#include "accessorinterface.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "actions/rebootaction.h"
#include "icons/back.h"
#include "esptexthelpers.h"
#include "texts.h"

namespace {
class DynamicDebugMenu;
class MainMenu;
}

namespace {
class DebugMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEBUG>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_REBOOT>,      RebootAction>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICMENU>, SwitchScreenAction<DynamicDebugMenu>>,
        makeComponent<MenuItem, EspHeapSizeText,              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFreeHeapText,              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspMinFreeHeapText,           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspMaxAllocHeapText,          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspPsramSizeText,             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFreePsramText,             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspMinFreePsramText,          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspMaxAllocPsramText,         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspChipRevisionText,          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspCpuFreqMHzText,            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspCycleCountText,            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspSdkVersionText,            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFlashChipSizeText,         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFlashChipSpeedText,        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFlashChipModeText,         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspSketchSizeText,            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspSketchMd5Text,             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, EspFreeSketchSpaceText,       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
