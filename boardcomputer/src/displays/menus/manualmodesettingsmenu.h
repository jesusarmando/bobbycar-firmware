#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetManualModeCtrlTypDisplay;
class SetManualModeCtrlModDisplay;
class SettingsMenu;
}

namespace {
class ManualModeSettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Manual mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SetManualModeCtrlTypDisplay> item0{"Set control type"};
    SwitchScreenMenuItem<SetManualModeCtrlModDisplay> item1{"Set control mode"};
    SwitchScreenMenuItem<SettingsMenu> item2{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 3> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2)
    }};
};
}
