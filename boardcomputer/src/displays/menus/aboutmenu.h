#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "esptexthelpers.h"
#include "texts.h"

namespace {
class SettingsMenu;
}

namespace {
constexpr char TEXT_VERSION[] = "Version: 1.0";
constexpr char TEXT_ESPINFO[] = "ESP info:";

class AboutMenu :
    public MenuDisplay,
    public StaticText<TEXT_ABOUT>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_VERSION>, DummyAction>,
        makeComponent<MenuItem, StaticText<nullptr>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_ESPINFO>, DummyAction>,
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
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
