#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftInvertedAccessor { static auto &getRef() { return front.invertLeft; } };
template<typename Tscreen>
using FrontLeftInvertedChangeScreen = ChangeValueDisplay<bool, FrontLeftInvertedAccessor, Tscreen, TEXT_INVERTFRONTLEFT>;

struct FrontRightInvertedAccessor { static auto &getRef() { return front.invertRight; } };
template<typename Tscreen>
using FrontRightInvertedChangeScreen = ChangeValueDisplay<bool, FrontRightInvertedAccessor, Tscreen, TEXT_INVERTFRONTRIGHT>;

struct BackLeftInvertedAccessor { static auto &getRef() { return back.command.left.enable; } };
template<typename Tscreen>
using BackLeftInvertedChangeScreen = ChangeValueDisplay<bool, BackLeftInvertedAccessor, Tscreen, TEXT_INVERTBACKLEFT>;

struct BackRightInvertedAccessor { static auto &getRef() { return back.invertRight; } };
template<typename Tscreen>
using BackRightInvertedChangeScreen = ChangeValueDisplay<bool, BackRightInvertedAccessor, Tscreen, TEXT_INVERTBACKRIGHT>;

template<typename Tscreen>
class InvertMenu final :
    public StaticTitle<TEXT_SETINVERTED>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontLeftInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTFRONTLEFT>,
        StaticSwitchScreenMenuItem<FrontRightInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTFRONTRIGHT>,
        StaticSwitchScreenMenuItem<BackLeftInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTBACKLEFT>,
        StaticSwitchScreenMenuItem<BackRightInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTBACKRIGHT>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
