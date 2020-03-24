#pragma once

#include "menudisplay.h"
#include "displays/changescreens/setfrontfreqdisplay.h"
#include "displays/changescreens/setfrontpatterndisplay.h"
#include "displays/changescreens/setbackfreqdisplay.h"
#include "displays/changescreens/setbackpatterndisplay.h"
#include "displays/menus/mainmenu.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class BuzzerMenu : public MenuDisplay
{
public:
    const char *title() const override { return "Buzzer"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); }
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); }

private:
    SwitchScreenItem<SetFrontFreqDisplay> item0{"Set front freq"};
    SwitchScreenItem<SetFrontPatternDisplay> item1{"Set front pattern"};
    SwitchScreenItem<SetBackFreqDisplay> item2{"Set back freq"};
    SwitchScreenItem<SetBackPatternDisplay> item3{"Set back pattern"};
    SwitchScreenItem<MainMenu> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
