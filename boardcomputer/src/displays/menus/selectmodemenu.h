#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/setdynamicvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SelectModeMenu final : public MenuDisplay<TEXT_SELECTMODE>
{
public:
    void start() override;

    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu, TEXT_DEFAULT> item0{currentMode, &modes::defaultMode};
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu, TEXT_MANUAL> item1{currentMode, &modes::manualMode};
    SetDynamicValueMenuItem<ModeBase*, CommonSettingsMenu, TEXT_BLUETOOTH> item2{currentMode, &modes::bluetoothMode};
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK> item3;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 4> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3)
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
