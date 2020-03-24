#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SelectModeMenu;
class SetIMotMaxDisplay;
class SetIDcMaxDisplay;
class SetNMotMaxDisplay;
class SetFieldWeakMaxDisplay;
class SetPhaseAdvMaxDisplay;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
class CommonSettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Common settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SelectModeMenu> item0{"Select mode"};
    SwitchScreenMenuItem<SetIMotMaxDisplay> item1{"Set iMotMax"};
    SwitchScreenMenuItem<SetIDcMaxDisplay> item2{"Set iDcMax"};
    SwitchScreenMenuItem<SetNMotMaxDisplay> item3{"Set nMotMax"};
    SwitchScreenMenuItem<SetFieldWeakMaxDisplay> item4{"Set fieldWeakMax"};
    SwitchScreenMenuItem<SetPhaseAdvMaxDisplay> item5{"Set phaseAdvMax"};
    SwitchScreenMenuItem<EnableMenu> item6{"Set enabled"};
    SwitchScreenMenuItem<InvertMenu> item7{"Set inverted"};
    SwitchScreenMenuItem<SettingsMenu> item8{"Back"};

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
}
