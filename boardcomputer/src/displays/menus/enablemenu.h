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
struct FrontLeftEnabledAccessor
{
    static auto getValue() { return front.command.left.enable; }
    template<typename T> static void setValue(T value) { front.command.left.enable = value; }
};
struct FrontRightEnabledAccessor
{
    static auto getValue() { return front.command.right.enable; }
    template<typename T> static void setValue(T value) { front.command.right.enable = value; }
};
struct BackLeftEnabledAccessor
{
    static auto getValue() { return back.command.left.enable; }
    template<typename T> static void setValue(T value) { back.command.left.enable = value; }
};
struct BackRightEnabledAccessor
{
    static auto getValue() { return back.command.right.enable; }
    template<typename T> static void setValue(T value) { back.command.right.enable = value; }
};

class EnableMenu final : public MenuDisplay<
    TEXT_SETENABLED,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLeftEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTLEFT>, TEXT_ENABLEFRONTLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontRightEnabledAccessor, EnableMenu, TEXT_ENABLEFRONTRIGHT>, TEXT_ENABLEFRONTRIGHT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLeftEnabledAccessor, EnableMenu, TEXT_ENABLEBACKLEFT>, TEXT_ENABLEBACKLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackRightEnabledAccessor, EnableMenu, TEXT_ENABLEBACKRIGHT>, TEXT_ENABLEBACKRIGHT>,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK>
>
{};
}
