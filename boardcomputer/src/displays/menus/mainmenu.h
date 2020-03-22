#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"

#include "displays/statusdisplay.h"
#include "settingsmenu.h"
#include "demosmenu.h"

namespace {
class MainMenu final : public MenuDisplay
{
public:
    const char *displayName() const override { return "MainMenu"; }
    const char *menuTitle() const override { return "Main menu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem item0{displays::status, displays::status.displayName()};
    SwitchScreenItem item1{displays::settingsMenu, displays::settingsMenu.menuTitle()};
    SwitchScreenItem item2{displays::demosMenu, displays::demosMenu.menuTitle()};
    RebootItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

namespace displays {
MainMenu mainMenu;
}
};
