#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/manualmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/mainmenu.h"

namespace {
class SettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem<CommonSettingsMenu> item0{"Common settings"};
    SwitchScreenItem<DefaultModeSettingsMenu> item1{"Default mode settings"};
    SwitchScreenItem<ManualModeSettingsMenu> item2{"Manual mode settings"};
    SwitchScreenItem<BluetoothModeSettingsMenu> item3{"Bluetooth mode settings"};
    SwitchScreenItem<PotiSettingsMenu> item4{"Poti settings"};
    SwitchScreenItem<MainMenu> item5{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 6> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5)
    }};
};
}
