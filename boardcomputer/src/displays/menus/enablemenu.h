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
class FrontLeftEnabledChangeScreen :
    public StaticText<TEXT_ENABLEFRONTLEFT>,
    public ChangeValueDisplay<bool>,
    public FrontLeftEnabledAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct FrontRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.right.enable; } };
template<typename Tscreen>
class FrontRightEnabledChangeScreen :
    public StaticText<TEXT_ENABLEFRONTRIGHT>,
    public ChangeValueDisplay<bool>,
    public FrontRightEnabledAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.left.enable; } };
template<typename Tscreen>
class BackLeftEnabledChangeScreen :
    public StaticText<TEXT_ENABLEBACKLEFT>,
    public ChangeValueDisplay<bool>,
    public BackLeftEnabledAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackRightEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.right.enable; } };
template<typename Tscreen>
class BackRightEnabledChangeScreen :
    public StaticText<TEXT_ENABLEBACKRIGHT>,
    public ChangeValueDisplay<bool>,
    public BackRightEnabledAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  DefaultFont, DefaultColor, SwitchScreenAction<FrontLeftEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, DefaultFont, DefaultColor, SwitchScreenAction<FrontRightEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   DefaultFont, DefaultColor, SwitchScreenAction<BackLeftEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  DefaultFont, DefaultColor, SwitchScreenAction<BackRightEnabledChangeScreen<EnableMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
