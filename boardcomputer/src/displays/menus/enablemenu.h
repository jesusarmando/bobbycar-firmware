#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftEnabledAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.left.enable; } };
template<typename Tscreen>
class FrontLeftEnabledChangeScreen :
    public StaticTitle<TEXT_ENABLEFRONTLEFT>,
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
    public StaticTitle<TEXT_ENABLEFRONTRIGHT>,
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
    public StaticTitle<TEXT_ENABLEBACKLEFT>,
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
    public StaticTitle<TEXT_ENABLEBACKRIGHT>,
    public ChangeValueDisplay<bool>,
    public BackRightEnabledAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class EnableMenu final :
    public StaticTitle<TEXT_SETENABLED>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTLEFT>,
        StaticSwitchScreenMenuItem<FrontRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEFRONTRIGHT>,
        StaticSwitchScreenMenuItem<BackLeftEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKLEFT>,
        StaticSwitchScreenMenuItem<BackRightEnabledChangeScreen<EnableMenu<Tscreen>>, TEXT_ENABLEBACKRIGHT>,
        BackMenuItem<Tscreen>
    >
{};
}
