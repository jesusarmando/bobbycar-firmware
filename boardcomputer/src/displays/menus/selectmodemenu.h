#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/setdynamicvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SelectModeMenu final : public MenuDisplay
{
public:
    void start() override;

    const char *title() const override { return "Select mode"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu> item0{currentMode, &modes::defaultMode, "Default"};
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu> item1{currentMode, &modes::manualMode, "Manual"};
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu> item2{currentMode, &modes::bluetoothMode, "Bluetooth"};
    SwitchScreenMenuItem<CommonSettingsMenu> item3{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

void SelectModeMenu::start()
{
    MenuDisplay::start();

    if (currentMode == &modes::defaultMode)
        m_current = begin() + 0;
    else if (currentMode == &modes::manualMode)
        m_current = begin() + 1;
    else if (currentMode == &modes::bluetoothMode)
        m_current = begin() + 2;
    else
        m_current = begin() + 3;
}
}
