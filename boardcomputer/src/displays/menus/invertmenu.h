#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertLeft; } };
template<typename Tscreen>
class FrontLeftInvertedChangeScreen :
    public StaticTitle<TEXT_INVERTFRONTLEFT>,
    public ChangeValueDisplay<bool>,
    public FrontLeftInvertedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct FrontRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertRight; } };
template<typename Tscreen>
class FrontRightInvertedChangeScreen :
    public StaticTitle<TEXT_INVERTFRONTRIGHT>,
    public ChangeValueDisplay<bool>,
    public FrontRightInvertedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.left.enable; } };
template<typename Tscreen>
class BackLeftInvertedChangeScreen :
    public StaticTitle<TEXT_INVERTBACKLEFT>,
    public ChangeValueDisplay<bool>,
    public BackLeftInvertedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackRightInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.invertRight; } };
template<typename Tscreen>
class BackRightInvertedChangeScreen :
    public StaticTitle<TEXT_INVERTBACKRIGHT>,
    public ChangeValueDisplay<bool>,
    public BackRightInvertedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class InvertMenu final :
    public StaticTitle<TEXT_SETINVERTED>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<FrontLeftInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTFRONTLEFT>,
        StaticSwitchScreenMenuItem<FrontRightInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTFRONTRIGHT>,
        StaticSwitchScreenMenuItem<BackLeftInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTBACKLEFT>,
        StaticSwitchScreenMenuItem<BackRightInvertedChangeScreen<InvertMenu<Tscreen>>, TEXT_INVERTBACKRIGHT>,
        BackMenuItem<Tscreen>
    >
{};
}
