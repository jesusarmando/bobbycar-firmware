#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetFrontLeftInvertedDisplay;
class SetFrontRightInvertedDisplay;
class SetBackLeftInvertedDisplay;
class SetBackRightInvertedDisplay;
class CommonSettingsMenu;
}

namespace {
class InvertMenu final : public MenuDisplay<
    TEXT_SETINVERTED,
    SwitchScreenMenuItem<SetFrontLeftInvertedDisplay, TEXT_INVERTFRONTLEFT>,
    SwitchScreenMenuItem<SetFrontRightInvertedDisplay, TEXT_INVERTFRONTRIGHT>,
    SwitchScreenMenuItem<SetBackLeftInvertedDisplay, TEXT_INVERTBACKLEFT>,
    SwitchScreenMenuItem<SetBackRightInvertedDisplay, TEXT_INVERTBACKRIGHT>,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK>
>
{};
}
