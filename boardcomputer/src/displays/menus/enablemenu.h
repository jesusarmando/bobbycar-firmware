#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "accessorhelper.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftEnabledAccessor { static auto &getRef() { return front.command.left.enable; } };
template<typename Tscreen>
using FrontLeftEnabledChangeScreen = ChangeValueDisplay<bool, AccessorHelper<FrontLeftEnabledAccessor>, Tscreen, TEXT_ENABLEFRONTLEFT>;

struct FrontRightEnabledAccessor { static auto &getRef() { return front.command.right.enable; } };
template<typename Tscreen>
using FrontRightEnabledChangeScreen = ChangeValueDisplay<bool, AccessorHelper<FrontRightEnabledAccessor>, Tscreen, TEXT_ENABLEFRONTRIGHT>;

struct BackLeftEnabledAccessor { static auto &getRef() { return back.command.left.enable; } };
template<typename Tscreen>
using BackLeftEnabledChangeScreen = ChangeValueDisplay<bool, AccessorHelper<BackLeftEnabledAccessor>, Tscreen, TEXT_ENABLEBACKLEFT>;

struct BackRightEnabledAccessor { static auto &getRef() { return back.command.right.enable; } };
template<typename Tscreen>
using BackRightEnabledChangeScreen = ChangeValueDisplay<bool, AccessorHelper<BackRightEnabledAccessor>, Tscreen, TEXT_ENABLEBACKRIGHT>;

template<typename Tscreen>
class EnableMenu final :
    public StaticTitle<TEXT_SETENABLED>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTLEFT>,
        StaticSwitchScreenMenuItem<FrontRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTRIGHT>,
        StaticSwitchScreenMenuItem<BackLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKLEFT>,
        StaticSwitchScreenMenuItem<BackRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKRIGHT>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
