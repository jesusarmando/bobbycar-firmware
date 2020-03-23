#pragma once

#include <array>

#include "menudisplay.h"
#include "changenumberdisplay.h"
#include "globals.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/selectmodemenu.h"

namespace {
class CommonSettingsMenu final : public MenuDisplay
{
public:
    CommonSettingsMenu(Display &prevDisplay);

    const char *menuTitle() const override { return "Common settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SelectModeMenu m_selectModeMenu{*this};
    ChangeNumberDisplay m_changeIMotMaxDisplay{"Set iMotMax", settings.iMotMax, *this};
    ChangeNumberDisplay m_changeIDcMaxDisplay{"Set iDcMax", settings.iDcMax, *this};
    ChangeNumberDisplay m_changeNMotMaxDisplay{"Set nMotMax", settings.nMotMax, *this};
    ChangeNumberDisplay m_changeFieldWeakMaxDisplay{"Set fieldWeakMax", settings.fieldWeakMax, *this};
    ChangeNumberDisplay m_changePhaseAdvMaxDisplay{"Set phaseAdvMax", settings.phaseAdvMax, *this};

    SwitchScreenItem item0{m_selectModeMenu, m_selectModeMenu.menuTitle()};
    SwitchScreenItem item1{m_changeIMotMaxDisplay, m_changeIMotMaxDisplay.title()};
    SwitchScreenItem item2{m_changeIDcMaxDisplay, m_changeIDcMaxDisplay.title()};
    SwitchScreenItem item3{m_changeNMotMaxDisplay, m_changeNMotMaxDisplay.title()};
    SwitchScreenItem item4{m_changeFieldWeakMaxDisplay, m_changeFieldWeakMaxDisplay.title()};
    SwitchScreenItem item5{m_changePhaseAdvMaxDisplay, m_changePhaseAdvMaxDisplay.title()};
    SwitchScreenItem item6;

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

CommonSettingsMenu::CommonSettingsMenu(Display &prevDisplay) :
    item6{prevDisplay, "Back"}
{
}
}
