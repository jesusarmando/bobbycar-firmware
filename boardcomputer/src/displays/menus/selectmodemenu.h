#pragma once

#include <array>

#include "globals.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
class SelectModeMenu final : public MenuDisplay
{
public:
    SelectModeMenu(Display &prevDisplay);

    void start() override;

    const char *title() const override { return "Select mode"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SetValueMenuItem<ModeBase*> item0;
    SetValueMenuItem<ModeBase*> item1;
    SetValueMenuItem<ModeBase*> item2;
    SwitchScreenItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

SelectModeMenu::SelectModeMenu(Display &prevDisplay) :
    item0{&modes::defaultMode, currentMode, prevDisplay, "Default"},
    item1{&modes::manualMode, currentMode, prevDisplay, "Manual"},
    item2{&modes::bluetoothMode, currentMode, prevDisplay, "Bluetooth"},
    item3{prevDisplay, "Back"}
{
}

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
