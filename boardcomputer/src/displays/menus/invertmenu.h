#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertLeft; } };
template<typename Tscreen>
using FrontLeftInvertedChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_INVERTFRONTLEFT>, FrontLeftInvertedAccessor, SwitchScreenAction<Tscreen>>;

struct FrontRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertRight; } };
template<typename Tscreen>
using FrontRightInvertedChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_INVERTFRONTRIGHT>, FrontRightInvertedAccessor, SwitchScreenAction<Tscreen>>;

struct BackLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.left.enable; } };
template<typename Tscreen>
using BackLeftInvertedChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_INVERTBACKLEFT>, BackLeftInvertedAccessor, SwitchScreenAction<Tscreen>>;

struct BackRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.invertRight; } };
template<typename Tscreen>
using BackRightInvertedChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_INVERTBACKRIGHT>, BackRightInvertedAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class InvertMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETINVERTED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  SwitchScreenAction<FrontLeftInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, SwitchScreenAction<FrontRightInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   SwitchScreenAction<BackLeftInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  SwitchScreenAction<BackRightInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
