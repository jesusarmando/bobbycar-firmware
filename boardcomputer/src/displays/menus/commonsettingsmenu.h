#pragma once

#include <array>

#include "menudisplay.h"
#include "changenumberdisplay.h"
#include "globals.h"
#include "menuitems/switchscreenmenuitem.h"
#include "selectmodemenu.h"
#include "enablemenu.h"
#include "invertmenu.h"

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
    ChangeNumberDisplay<int16_t> m_changeIMotMaxDisplay{"Set iMotMax", settings.iMotMax, *this};
    ChangeNumberDisplay<int16_t> m_changeIDcMaxDisplay{"Set iDcMax", settings.iDcMax, *this};
    ChangeNumberDisplay<int16_t> m_changeNMotMaxDisplay{"Set nMotMax", settings.nMotMax, *this};
    ChangeNumberDisplay<int16_t> m_changeFieldWeakMaxDisplay{"Set fieldWeakMax", settings.fieldWeakMax, *this};
    ChangeNumberDisplay<int16_t> m_changePhaseAdvMaxDisplay{"Set phaseAdvMax", settings.phaseAdvMax, *this};
    EnableMenu m_enableMenu{*this};
    InvertMenu m_invertMenu{*this};

    SwitchScreenItem item0{m_selectModeMenu, m_selectModeMenu.menuTitle()};
    SwitchScreenItem item1{m_changeIMotMaxDisplay, m_changeIMotMaxDisplay.title()};
    SwitchScreenItem item2{m_changeIDcMaxDisplay, m_changeIDcMaxDisplay.title()};
    SwitchScreenItem item3{m_changeNMotMaxDisplay, m_changeNMotMaxDisplay.title()};
    SwitchScreenItem item4{m_changeFieldWeakMaxDisplay, m_changeFieldWeakMaxDisplay.title()};
    SwitchScreenItem item5{m_changePhaseAdvMaxDisplay, m_changePhaseAdvMaxDisplay.title()};
    SwitchScreenItem item6{m_enableMenu, m_enableMenu.menuTitle()};
    SwitchScreenItem item7{m_invertMenu, m_invertMenu.menuTitle()};
    SwitchScreenItem item8;

    const std::array<std::reference_wrapper<const MenuItem>, 9> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5),
        std::cref<MenuItem>(item6),
        std::cref<MenuItem>(item7),
        std::cref<MenuItem>(item8)
    }};
};

CommonSettingsMenu::CommonSettingsMenu(Display &prevDisplay) :
    item8{prevDisplay, "Back"}
{
}
}
