#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftEnabledAccessor { static auto &getRef() { return front.command.left.enable; } };
template<typename Tscreen>
using FrontLeftEnabledChangeScreen = ChangeValueDisplay<bool, FrontLeftEnabledAccessor, Tscreen, TEXT_ENABLEFRONTLEFT>;

struct FrontRightEnabledAccessor { static auto &getRef() { return front.command.right.enable; } };
template<typename Tscreen>
using FrontRightEnabledChangeScreen = ChangeValueDisplay<bool, FrontRightEnabledAccessor, Tscreen, TEXT_ENABLEFRONTRIGHT>;

struct BackLeftEnabledAccessor { static auto &getRef() { return back.command.left.enable; } };
template<typename Tscreen>
using BackLeftEnabledChangeScreen = ChangeValueDisplay<bool, BackLeftEnabledAccessor, Tscreen, TEXT_ENABLEBACKLEFT>;

struct BackRightEnabledAccessor { static auto &getRef() { return back.command.right.enable; } };
template<typename Tscreen>
using BackRightEnabledChangeScreen = ChangeValueDisplay<bool, BackRightEnabledAccessor, Tscreen, TEXT_ENABLEBACKRIGHT>;

template<typename Tscreen>
class EnableMenu final : public MenuDisplay<
    TEXT_SETENABLED,
    SwitchScreenMenuItem<FrontLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTLEFT>,
    SwitchScreenMenuItem<FrontRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTRIGHT>,
    SwitchScreenMenuItem<BackLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKLEFT>,
    SwitchScreenMenuItem<BackRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKRIGHT>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
