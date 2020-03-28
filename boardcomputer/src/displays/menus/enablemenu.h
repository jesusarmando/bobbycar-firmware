#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftEnabledAccessor { static auto &getRef() { return front.command.left.enable; } };
struct FrontRightEnabledAccessor { static auto &getRef() { return front.command.right.enable; } };
struct BackLeftEnabledAccessor { static auto &getRef() { return back.command.left.enable; } };
struct BackRightEnabledAccessor { static auto &getRef() { return back.command.right.enable; } };

template<typename Tscreen>
class EnableMenu final : public MenuDisplay<
    TEXT_SETENABLED,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLeftEnabledAccessor, EnableMenu<Tscreen>, TEXT_ENABLEFRONTLEFT>, TEXT_ENABLEFRONTLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontRightEnabledAccessor, EnableMenu<Tscreen>, TEXT_ENABLEFRONTRIGHT>, TEXT_ENABLEFRONTRIGHT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLeftEnabledAccessor, EnableMenu<Tscreen>, TEXT_ENABLEBACKLEFT>, TEXT_ENABLEBACKLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackRightEnabledAccessor, EnableMenu<Tscreen>, TEXT_ENABLEBACKRIGHT>, TEXT_ENABLEBACKRIGHT>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
