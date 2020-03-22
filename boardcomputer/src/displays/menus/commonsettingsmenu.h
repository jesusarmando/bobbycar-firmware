#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class CommonSettingsMenu final : public MenuDisplay
{
public:
    CommonSettingsMenu();

    const char *displayName() const override { return "CommonSettingsMenu"; }
    const char *menuTitle() const override { return "Common settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem item0;

    const std::array<std::reference_wrapper<const MenuItem>, 1> carr{{
        std::cref<MenuItem>(item0)
    }};
};

namespace displays {
CommonSettingsMenu commonSettingsMenu;
}
}
