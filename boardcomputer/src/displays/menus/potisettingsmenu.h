#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class SetGasMinDisplay;
class SetGasMaxDisplay;
class SetBremsMinDisplay;
class SetBremsMaxDisplay;
class SettingsMenu;
}

namespace {
class PotiSettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Poti settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<SetGasMinDisplay> item0{"Set gasMin"};
    SwitchScreenMenuItem<SetGasMaxDisplay> item1{"Set gasMax"};
    SwitchScreenMenuItem<SetBremsMinDisplay> item2{"Set bremsMin"};
    SwitchScreenMenuItem<SetBremsMaxDisplay> item3{"Set bremsMax"};
    SwitchScreenMenuItem<SettingsMenu> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
