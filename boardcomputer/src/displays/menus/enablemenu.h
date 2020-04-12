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
struct FrontLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.left.enable; } };
template<typename Tscreen>
using FrontLeftEnabledChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_ENABLEFRONTLEFT>, FrontLeftEnabledAccessor, SwitchScreenAction<Tscreen>>;

struct FrontRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.right.enable; } };
template<typename Tscreen>
using FrontRightEnabledChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_ENABLEFRONTRIGHT>, FrontRightEnabledAccessor, SwitchScreenAction<Tscreen>>;

struct BackLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.left.enable; } };
template<typename Tscreen>
using BackLeftEnabledChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_ENABLEBACKLEFT>, BackLeftEnabledAccessor, SwitchScreenAction<Tscreen>>;

struct BackRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.right.enable; } };
template<typename Tscreen>
using BackRightEnabledChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_ENABLEBACKRIGHT>, BackRightEnabledAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  SwitchScreenAction<FrontLeftEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, SwitchScreenAction<FrontRightEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   SwitchScreenAction<BackLeftEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  SwitchScreenAction<BackRightEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
