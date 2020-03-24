#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetFrontFreqDisplay;
class SetFrontPatternDisplay;
class SetBackFreqDisplay;
class SetBackPatternDisplay;
class MainMenu;
}

namespace {
class BuzzerMenu final : public MenuDisplay<
    TEXT_BUZZER,
    SwitchScreenMenuItem<SetFrontFreqDisplay, TEXT_SETBACKFREQ>,
    SwitchScreenMenuItem<SetFrontPatternDisplay, TEXT_SETFRONTPATTERN>,
    SwitchScreenMenuItem<SetBackFreqDisplay, TEXT_SETBACKFREQ>,
    SwitchScreenMenuItem<SetBackPatternDisplay, TEXT_SETBACKPATTERN>,
    SwitchScreenMenuItem<MainMenu, TEXT_BACK>
>
{};
}
