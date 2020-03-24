#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "changevaluedisplay_bool.h"
#include "changevaluedisplay_controlmode.h"
#include "changevaluedisplay_controltype.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu final : public MenuDisplay
{
public:
    DefaultModeSettingsMenu(Display &prevDisplay);

    const char *title() const override { return "Default mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SetDefaultModeCtrlTypDisplay m_selectControlTypeMenu{*this};
    SetDefaultModeCtrlModDisplay m_selectControlModeMenu{*this};
    SetDefaultModeEnableFieldWeakeningSmootheningDisplay m_enableWeakeningSmootheningDisplay{*this};
    SetDefaultModeWeakeningSmootheningDisplay m_weakeningSmootheningDisplay{*this};
    SetDefaultModeFrontPercentageDisplay m_frontPercentageDisplay{*this};
    SetDefaultModeBackPercentageDisplay m_backPercentageDisplay{*this};
    SetDefaultModeAddSchwelleDisplay m_add_schwelleDisplay{*this};
    SetDefaultModeGas1WertDisplay m_gas1_wertDisplay{*this};
    SetDefaultModeGas2WertDisplay m_gas2_wertDisplay{*this};
    SetDefaultModeBrems1WertDisplay m_brems1_wertDisplay{*this};
    SetDefaultModeBrems2WertDisplay m_brems2_wertDisplay{*this};

    SwitchScreenItem item0{m_selectControlTypeMenu, m_selectControlTypeMenu.title()};
    SwitchScreenItem item1{m_selectControlModeMenu, m_selectControlModeMenu.title()};
    SwitchScreenItem item2{m_enableWeakeningSmootheningDisplay, m_enableWeakeningSmootheningDisplay.title()};
    SwitchScreenItem item3{m_weakeningSmootheningDisplay, m_weakeningSmootheningDisplay.title()};
    SwitchScreenItem item4{m_frontPercentageDisplay, m_frontPercentageDisplay.title()};
    SwitchScreenItem item5{m_backPercentageDisplay, m_backPercentageDisplay.title()};
    SwitchScreenItem item6{m_add_schwelleDisplay, m_add_schwelleDisplay.title()};
    SwitchScreenItem item7{m_gas1_wertDisplay, m_gas1_wertDisplay.title()};
    SwitchScreenItem item8{m_gas2_wertDisplay, m_gas2_wertDisplay.title()};
    SwitchScreenItem item9{m_brems1_wertDisplay, m_brems1_wertDisplay.title()};
    SwitchScreenItem item10{m_brems2_wertDisplay, m_brems2_wertDisplay.title()};

    const std::array<std::reference_wrapper<const MenuItem>, 11> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5),
        std::cref<MenuItem>(item6),
        std::cref<MenuItem>(item7),
        std::cref<MenuItem>(item8),
        std::cref<MenuItem>(item9),
        std::cref<MenuItem>(item10)
    }};
};

DefaultModeSettingsMenu::DefaultModeSettingsMenu(Display &prevDisplay) :
    item2{prevDisplay, "Back"}
{
}
}
