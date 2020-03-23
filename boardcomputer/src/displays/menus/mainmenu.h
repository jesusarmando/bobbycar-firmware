#pragma once

#include <array>

#include "displays/statusdisplay.h"
#include "menudisplay.h"
#include "settingsmenu.h"
#include "demosmenu.h"

#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"

#include "displays/statusdisplay.h"
#include "settingsmenu.h"
#include "demosmenu.h"

namespace {
class MainMenu final : public MenuDisplay
{
public:
    const char *menuTitle() const override { return "Main menu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

    StatusDisplay m_statusDisplay{*this};
private:
    SettingsMenu m_settingsMenu{*this};
    DemosMenu m_demoMenu{*this};

    SwitchScreenItem item0{m_statusDisplay, "Status"};
    SwitchScreenItem item1{m_settingsMenu, m_settingsMenu.menuTitle()};
    SwitchScreenItem item2{m_demoMenu, m_demoMenu.menuTitle()};
    RebootItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};
};
