#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"

namespace {
class StatusDisplay;
class SettingsMenu;
class DemosMenu;
class BuzzerMenu;
class SetFrontLedDisplay;
class SetBackLedDisplay;
}

namespace {
class MainMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Main menu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<StatusDisplay> item0{"Status"};
    SwitchScreenMenuItem<SettingsMenu> item1{"Settings"};
    SwitchScreenMenuItem<DemosMenu> item2{"Demos"};
    SwitchScreenMenuItem<BuzzerMenu> item3{"Buzzer"};
    SwitchScreenMenuItem<SetFrontLedDisplay> item4{"Set front LED"};
    SwitchScreenMenuItem<SetBackLedDisplay> item5{"Set back LED"};
    RebootItem item6;

    const std::array<std::reference_wrapper<const MenuItem>, 7> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5),
        std::cref<MenuItem>(item6)
    }};
};
};
