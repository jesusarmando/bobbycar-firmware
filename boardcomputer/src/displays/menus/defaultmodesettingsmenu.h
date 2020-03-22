#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/selectcontroltypemenu.h"
#include "displays/menus/selectcontrolmodemenu.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu final : public MenuDisplay
{
public:
    DefaultModeSettingsMenu(Display &prevDisplay);

    const char *displayName() const override { return "DefaultModeSettingsMenu"; }
    const char *menuTitle() const override { return "Default mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SelectControlTypeMenu m_selectControlTypeMenu{modes::defaultMode.ctrlTyp, *this};
    SelectControlModeMenu m_selectControlModeMenu{modes::defaultMode.ctrlMod, *this};

    SwitchScreenItem item0{m_selectControlTypeMenu, m_selectControlTypeMenu.menuTitle()};
    SwitchScreenItem item1{m_selectControlModeMenu, m_selectControlModeMenu.menuTitle()};
    SwitchScreenItem item2;

    const std::array<std::reference_wrapper<const MenuItem>, 3> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2)
    }};
};

DefaultModeSettingsMenu::DefaultModeSettingsMenu(Display &prevDisplay) :
    item2{prevDisplay, "Back"}
{
}
}
