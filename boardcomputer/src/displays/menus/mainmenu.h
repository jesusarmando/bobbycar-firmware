#pragma once

#include <array>

#include "displays/statusdisplay.h"
#include "menudisplay.h"
#include "settingsmenu.h"
#include "demosmenu.h"
#include "buzzermenu.h"
#include "changenumberdisplay.h"

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
    BuzzerMenu m_buzzerMenu{*this};
    ChangeNumberDisplay<bool> m_frontLed{"Front LED", front.command.led, *this};
    ChangeNumberDisplay<bool> m_backLed{"Back LED", back.command.led, *this};

    SwitchScreenItem item0{m_statusDisplay, "Status"};
    SwitchScreenItem item1{m_settingsMenu, m_settingsMenu.menuTitle()};
    SwitchScreenItem item2{m_demoMenu, m_demoMenu.menuTitle()};
    SwitchScreenItem item3{m_buzzerMenu, m_buzzerMenu.menuTitle()};
    SwitchScreenItem item4{m_frontLed, m_frontLed.title()};
    SwitchScreenItem item5{m_backLed, m_backLed.title()};
    RebootItem item6;

    const std::array<std::reference_wrapper<const MenuItem>, 7> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5),
        std::cref<MenuItem>(item6)
    }};
};
};
