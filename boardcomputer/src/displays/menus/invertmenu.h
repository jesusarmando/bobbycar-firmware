#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftInvertedAccessor { static auto &getRef() { return front.invertLeft; } };
struct FrontRightInvertedAccessor { static auto &getRef() { return front.invertRight; } };
struct BackLeftInvertedAccessor { static auto &getRef() { return back.command.left.enable; } };
struct BackRightInvertedAccessor { static auto &getRef() { return back.invertRight; } };

template<typename Tscreen>
class InvertMenu final : public MenuDisplay<
    TEXT_SETINVERTED,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLeftInvertedAccessor, InvertMenu<Tscreen>, TEXT_INVERTFRONTLEFT>, TEXT_INVERTFRONTLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontRightInvertedAccessor, InvertMenu<Tscreen>, TEXT_INVERTFRONTRIGHT>, TEXT_INVERTFRONTRIGHT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLeftInvertedAccessor, InvertMenu<Tscreen>, TEXT_INVERTBACKLEFT>, TEXT_INVERTBACKLEFT>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackRightInvertedAccessor, InvertMenu<Tscreen>, TEXT_INVERTBACKRIGHT>, TEXT_INVERTBACKRIGHT>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
