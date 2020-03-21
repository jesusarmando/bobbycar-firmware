#pragma once

#include <array>

#include "menudisplay.h"
#include "switchscreenmenuitem.h"

#include "displays/statusdisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"

namespace {
class MainMenu : public MenuDisplay
{
public:
    const char *displayName() const override { return "MainMenu"; }

    const std::reference_wrapper<MenuItem> *begin() override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() override { return std::end(arr); };
    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem item0{displays::status, displays::status.displayName()};
    SwitchScreenItem item1{displays::starfield, displays::starfield.displayName()};
    SwitchScreenItem item2{displays::pingPong, displays::pingPong.displayName()};
    SwitchScreenItem item3{displays::spiro, displays::spiro.displayName()};

    const std::array<std::reference_wrapper<MenuItem>, 4> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3)
    }};
    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

namespace displays {
MainMenu mainMenu;
}
};
