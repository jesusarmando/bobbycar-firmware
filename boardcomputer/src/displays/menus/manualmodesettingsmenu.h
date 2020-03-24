#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay_controlmode.h"
#include "changevaluedisplay_controltype.h"
#include "modes/manualmode.h"

namespace {
class ManualModeSettingsMenu final : public MenuDisplay
{
public:
    ManualModeSettingsMenu(Display &prevDisplay);

    const char *title() const override { return "Manual mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ChangeValueDisplay<ControlType> m_selectControlTypeMenu{"Set control type", modes::manualMode.ctrlTyp, *this};
    ChangeValueDisplay<ControlMode> m_selectControlModeMenu{"Set control mode", modes::manualMode.ctrlMod, *this};

    SwitchScreenItem item0{m_selectControlTypeMenu, m_selectControlTypeMenu.title()};
    SwitchScreenItem item1{m_selectControlModeMenu, m_selectControlModeMenu.title()};
    SwitchScreenItem item2;

    const std::array<std::reference_wrapper<const MenuItem>, 3> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2)
    }};
};

ManualModeSettingsMenu::ManualModeSettingsMenu(Display &prevDisplay):
    item2{prevDisplay, "Back"}
{
}
}
