#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetDefaultModeCtrlTypDisplay;
class SetDefaultModeCtrlModDisplay;
class SetDefaultModeEnableFieldWeakeningSmootheningDisplay;
class SetDefaultModeWeakeningSmootheningDisplay;
class SetDefaultModeFrontPercentageDisplay;
class SetDefaultModeBackPercentageDisplay;
class SetDefaultModeAddSchwelleDisplay;
class SetDefaultModeGas1WertDisplay;
class SetDefaultModeGas2WertDisplay;
class SetDefaultModeBrems1WertDisplay;
class SetDefaultModeBrems2WertDisplay;
class SettingsMenu;
}

namespace {
class DefaultModeSettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Default mode settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SetDefaultModeCtrlTypDisplay> item0{"Set control type"};
    SwitchScreenMenuItem<SetDefaultModeCtrlModDisplay> item1{"Set control mode"};
    SwitchScreenMenuItem<SetDefaultModeEnableFieldWeakeningSmootheningDisplay> item2{"Enable weakening smoothening"};
    SwitchScreenMenuItem<SetDefaultModeWeakeningSmootheningDisplay> item3{"Set weaking smoothening"};
    SwitchScreenMenuItem<SetDefaultModeFrontPercentageDisplay> item4{"Set front percentage"};
    SwitchScreenMenuItem<SetDefaultModeBackPercentageDisplay> item5{"Set back percentage"};
    SwitchScreenMenuItem<SetDefaultModeAddSchwelleDisplay> item6{"Set add Schwelle"};
    SwitchScreenMenuItem<SetDefaultModeGas1WertDisplay> item7{"Set Gas 1 Wert"};
    SwitchScreenMenuItem<SetDefaultModeGas2WertDisplay> item8{"Set Gas 2 Wert"};
    SwitchScreenMenuItem<SetDefaultModeBrems1WertDisplay> item9{"Set Brems 1 Wert"};
    SwitchScreenMenuItem<SetDefaultModeBrems2WertDisplay> item10{"Set Brems 2 Wert"};
    SwitchScreenMenuItem<SettingsMenu> item11{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 12> carr{{
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
        std::cref<MenuItem>(item10),
        std::cref<MenuItem>(item11)
    }};
};
}
