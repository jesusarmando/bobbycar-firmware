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
struct FrontLeftEnabledAccessor { static auto &getRef() { return front.command.left.enable; } };
struct FrontRightEnabledAccessor { static auto &getRef() { return front.command.right.enable; } };
struct BackLeftEnabledAccessor { static auto &getRef() { return back.command.left.enable; } };
struct BackRightEnabledAccessor { static auto &getRef() { return back.command.right.enable; } };

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
