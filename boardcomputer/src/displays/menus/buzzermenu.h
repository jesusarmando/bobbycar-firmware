#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetFrontFreqDisplay;
class SetFrontPatternDisplay;
class SetBackFreqDisplay;
class SetBackPatternDisplay;
class MainMenu;
}

namespace {
class BuzzerMenu : public MenuDisplay
{
public:
    const char *title() const override { return "Buzzer"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); }
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); }

private:
    SwitchScreenMenuItem<SetFrontFreqDisplay> item0{"Set front freq"};
    SwitchScreenMenuItem<SetFrontPatternDisplay> item1{"Set front pattern"};
    SwitchScreenMenuItem<SetBackFreqDisplay> item2{"Set back freq"};
    SwitchScreenMenuItem<SetBackPatternDisplay> item3{"Set back pattern"};
    SwitchScreenMenuItem<MainMenu> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
