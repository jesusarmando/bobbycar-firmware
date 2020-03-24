#pragma once

#include <array>

#include "menudisplay.h"
#include "displays/statusdisplay.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/changescreens/setfrontleddisplay.h"
#include "displays/changescreens/setbackleddisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"

namespace {
class MainMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Main menu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem<StatusDisplay> item0{"Status"};
    SwitchScreenItem<SettingsMenu> item1{"Settings"};
    SwitchScreenItem<DemosMenu> item2{"Demos"};
    SwitchScreenItem<BuzzerMenu> item3{"Buzzer"};
    SwitchScreenItem<SetFrontLedDisplay> item4{"Set front LED"};
    SwitchScreenItem<SetBackLedDisplay> item5{"Set back LED"};
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
