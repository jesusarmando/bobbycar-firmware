#pragma once

#include <array>

#include "globals.h"
#include "menudisplay.h"
#include "menuitems/selectcontroltypeitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SelectControlTypeMenu final : public MenuDisplay
{
public:
    SelectControlTypeMenu(ControlType &controlType, Display &prevDisplay);

    void start() override;

    const char *displayName() const override { return "SelectControlTypeMenu"; }
    const char *menuTitle() const override { return "Select control type"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ControlType &m_controlType;

    SelectControlTypeItem item0;
    SelectControlTypeItem item1;
    SelectControlTypeItem item2;
    SwitchScreenItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

SelectControlTypeMenu::SelectControlTypeMenu(ControlType &controlType, Display &prevDisplay) :
    m_controlType{controlType},
    item0{ControlType::Commutation, controlType, prevDisplay, "Commutation"},
    item1{ControlType::Sinusoidal, controlType, prevDisplay, "Sinusoidal"},
    item2{ControlType::FieldOrientedControl, controlType, prevDisplay, "Field oriented control"},
    item3{prevDisplay, "Back"}
{
}

void SelectControlTypeMenu::start()
{
    MenuDisplay::start();

    if (m_controlType == ControlType::Commutation)
        m_current = begin() + 0;
    else if (m_controlType == ControlType::Sinusoidal)
        m_current = begin() + 1;
    else if (m_controlType == ControlType::FieldOrientedControl)
        m_current = begin() + 2;
    else
        m_current = begin() + 3;
}
}
