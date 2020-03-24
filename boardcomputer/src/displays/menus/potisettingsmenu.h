#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/changescreens/setgasmindisplay.h"
#include "displays/changescreens/setgasmaxdisplay.h"
#include "displays/changescreens/setbremsmindisplay.h"
#include "displays/changescreens/setbremsmaxdisplay.h"
#include "displays/menus/settingsmenu.h"

namespace {
class PotiSettingsMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Poti settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem<SetGasMinDisplay> item0{"Set gasMin"};
    SwitchScreenItem<SetGasMaxDisplay> item1{"Set gasMax"};
    SwitchScreenItem<SetBremsMinDisplay> item2{"Set bremsMin"};
    SwitchScreenItem<SetBremsMaxDisplay> item3{"Set bremsMax"};
    SwitchScreenItem<SettingsMenu> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
