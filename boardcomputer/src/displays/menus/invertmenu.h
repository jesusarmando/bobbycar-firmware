#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetFrontLeftInvertedDisplay;
class SetFrontRightInvertedDisplay;
class SetBackLeftInvertedDisplay;
class SetBackRightInvertedDisplay;
class CommonSettingsMenu;
}

namespace {
class InvertMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Set inverted"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SetFrontLeftInvertedDisplay> item0{"Invert front left"};
    SwitchScreenMenuItem<SetFrontRightInvertedDisplay> item1{"Invert front right"};
    SwitchScreenMenuItem<SetBackLeftInvertedDisplay> item2{"Invert back left"};
    SwitchScreenMenuItem<SetBackRightInvertedDisplay> item3{"Invert back right"};
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
