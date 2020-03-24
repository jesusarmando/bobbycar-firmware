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
    SettingsMenu(Display &prevDisplay);

    const char *title() const override { return "Settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    CommonSettingsMenu m_commonSettingsMenu{*this};
    DefaultModeSettingsMenu m_defaultModeSettingsMenu{*this};
    ManualModeSettingsMenu m_manualModeSettingsMenu{*this};
    BluetoothModeSettingsMenu m_bluetoothModeSettingsMenu{*this};
    PotiSettingsMenu m_potiSettingsMenu{*this};

    SwitchScreenItem item0{m_commonSettingsMenu, m_commonSettingsMenu.title()};
    SwitchScreenItem item1{m_defaultModeSettingsMenu, m_defaultModeSettingsMenu.title()};
    SwitchScreenItem item2{m_manualModeSettingsMenu, m_manualModeSettingsMenu.title()};
    SwitchScreenItem item3{m_bluetoothModeSettingsMenu, m_bluetoothModeSettingsMenu.title()};
    SwitchScreenItem item4{m_potiSettingsMenu, m_potiSettingsMenu.title()};
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

SettingsMenu::SettingsMenu(Display &prevDisplay) :
    item5{prevDisplay, "Back"}
{
}
}
