#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class BluetoothModeSettingsMenu final : public MenuDisplay
{
public:
    BluetoothModeSettingsMenu(Display &prevDisplay);

    const char *menuTitle() const override { return "Bluetooth mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem item0;

    const std::array<std::reference_wrapper<const MenuItem>, 1> carr{{
        std::cref<MenuItem>(item0)
    }};
};

BluetoothModeSettingsMenu::BluetoothModeSettingsMenu(Display &prevDisplay):
   item0{prevDisplay, "Back"}
{
}
}
