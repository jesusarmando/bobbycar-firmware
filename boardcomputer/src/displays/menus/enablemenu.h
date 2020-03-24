#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetFrontLeftEnabledDisplay;
class SetFrontRightEnabledDisplay;
class SetBackLeftEnabledDisplay;
class SetBackRightEnabledDisplay;
class CommonSettingsMenu;
}

namespace {
class EnableMenu final : public MenuDisplay<
    TEXT_SETENABLED,
    SwitchScreenMenuItem<SetFrontLeftEnabledDisplay, TEXT_ENABLEFRONTLEFT>,
    SwitchScreenMenuItem<SetFrontRightEnabledDisplay, TEXT_ENABLEFRONTRIGHT>,
    SwitchScreenMenuItem<SetBackLeftEnabledDisplay, TEXT_ENABLEBACKLEFT>,
    SwitchScreenMenuItem<SetBackRightEnabledDisplay, TEXT_ENABLEBACKRIGHT>,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK>
>
{};
}
