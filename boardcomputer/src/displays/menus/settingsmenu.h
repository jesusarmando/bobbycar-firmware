#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

#include "commonsettingsmenu.h"
#include "defaultmodesettingsmenu.h"
#include "manualmodesettingsmenu.h"
#include "bluetoothmodesettingsmenu.h"
#include "potisettingsmenu.h"

namespace {
class SettingsMenu final : public MenuDisplay
{
public:
    SettingsMenu();

    const char *displayName() const override { return "SettingsMenu"; }
    const char *menuTitle() const override { return "Settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem item0{displays::commonSettingsMenu, displays::commonSettingsMenu.menuTitle()};
    SwitchScreenItem item1{displays::defaultModeSettingsMenu, displays::defaultModeSettingsMenu.menuTitle()};
    SwitchScreenItem item2{displays::manualModeSettingsMenu, displays::manualModeSettingsMenu.menuTitle()};
    SwitchScreenItem item3{displays::bluetoothModeSettingsMenu, displays::bluetoothModeSettingsMenu.menuTitle()};
    SwitchScreenItem item4{displays::potiSettingsMenu, displays::potiSettingsMenu.menuTitle()};
    SwitchScreenItem item5;

    const std::array<std::reference_wrapper<const MenuItem>, 6> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5)
    }};
};

namespace displays {
SettingsMenu settingsMenu;
}
}
