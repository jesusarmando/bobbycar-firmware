#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLeftInvertedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.invertLeft; } };
template<typename Tscreen>
class FrontLeftInvertedChangeScreen :
    public StaticText<TEXT_INVERTFRONTLEFT>,
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
    public StaticText<TEXT_INVERTFRONTRIGHT>,
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
    public StaticText<TEXT_INVERTBACKLEFT>,
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
    public StaticText<TEXT_INVERTBACKRIGHT>,
    public ChangeValueDisplay<bool>,
    public BackRightInvertedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class InvertMenu :
    public StaticText<TEXT_SETINVERTED>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  DefaultFont, DefaultColor, SwitchScreenAction<FrontLeftInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, DefaultFont, DefaultColor, SwitchScreenAction<FrontRightInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   DefaultFont, DefaultColor, SwitchScreenAction<BackLeftInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  DefaultFont, DefaultColor, SwitchScreenAction<BackRightInvertedChangeScreen<InvertMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >
{};
}
