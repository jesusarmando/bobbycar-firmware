#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetFrontLeftEnabledDisplay;
class SetFrontRightEnabledDisplay;
class SetBackLeftEnabledDisplay;
class SetBackRightEnabledDisplay;
class CommonSettingsMenu;
}

namespace {
class EnableMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Set enabled"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SetFrontLeftEnabledDisplay> item0{"Enable front left"};
    SwitchScreenMenuItem<SetFrontRightEnabledDisplay> item1{"Enable front right"};
    SwitchScreenMenuItem<SetBackLeftEnabledDisplay> item2{"Enable back left"};
    SwitchScreenMenuItem<SetBackRightEnabledDisplay> item3{"Enable back right"};
    SwitchScreenMenuItem<CommonSettingsMenu> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
