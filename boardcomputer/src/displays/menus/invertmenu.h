#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
struct FrontLeftInvertedAccessor
{
    static auto getValue() { return front.invertLeft; }
    template<typename T> static void setValue(T value) { front.invertLeft = value; }
};
struct FrontRightInvertedAccessor
{
    static auto getValue() { return front.invertRight; }
    template<typename T> static void setValue(T value) { front.invertRight = value; }
};
struct BackLeftInvertedAccessor
{
    static auto getValue() { return back.command.left.enable; }
    template<typename T> static void setValue(T value) { back.invertLeft = value; }
};
struct BackRightInvertedAccessor
{
    static auto getValue() { return back.invertRight; }
    template<typename T> static void setValue(T value) { back.invertRight = value; }
};

class InvertMenu final : public MenuDisplay<
    TEXT_SETINVERTED,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLeftInvertedAccessor, InvertMenu, TEXT_INVERTFRONTLEFT>, TEXT_INVERTFRONTLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontRightInvertedAccessor, InvertMenu, TEXT_INVERTFRONTRIGHT>, TEXT_INVERTFRONTRIGHT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLeftInvertedAccessor, InvertMenu, TEXT_INVERTBACKLEFT>, TEXT_INVERTBACKLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackRightInvertedAccessor, InvertMenu, TEXT_INVERTBACKRIGHT>, TEXT_INVERTBACKRIGHT>,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK>
>
{};
}
