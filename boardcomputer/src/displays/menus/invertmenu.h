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
struct FrontLeftInvertedAccessor { static auto &getRef() { return front.invertLeft; } };
struct FrontRightInvertedAccessor { static auto &getRef() { return front.invertRight; } };
struct BackLeftInvertedAccessor { static auto &getRef() { return back.command.left.enable; } };
struct BackRightInvertedAccessor { static auto &getRef() { return back.invertRight; } };

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
