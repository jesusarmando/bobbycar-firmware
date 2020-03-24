#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class CommonSettingsMenu;
class DefaultModeSettingsMenu;
class ManualModeSettingsMenu;
class BluetoothModeSettingsMenu;
class PotiSettingsMenu;
class MainMenu;
}

namespace {
class SettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<CommonSettingsMenu> item0{"Common settings"};
    SwitchScreenMenuItem<DefaultModeSettingsMenu> item1{"Default mode settings"};
    SwitchScreenMenuItem<ManualModeSettingsMenu> item2{"Manual mode settings"};
    SwitchScreenMenuItem<BluetoothModeSettingsMenu> item3{"Bluetooth mode settings"};
    SwitchScreenMenuItem<PotiSettingsMenu> item4{"Poti settings"};
    SwitchScreenMenuItem<MainMenu> item5{"Back"};

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
