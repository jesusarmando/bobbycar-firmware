#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/selectmodeitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class ModeSelectionMenu final : public MenuDisplay
{
public:
    ModeSelectionMenu();

    const char *displayName() const override { return "ModeSelectionMenu"; }
    const char *menuTitle() const override { return "Mode selection"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SelectModeItem item0;
    SelectModeItem item1;
    SelectModeItem item2;
    SwitchScreenItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

namespace displays {
ModeSelectionMenu modeSelectionMenu;
}
}
