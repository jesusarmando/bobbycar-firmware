#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
template<typename Tscreen>
class FrontLedChangeScreen :
    public ChangeValueDisplay<bool>,
    public StaticText<TEXT_SETFRONTLED>,
    public FrontLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };
template<typename Tscreen>
class BackLedChangeScreen :
    public ChangeValueDisplay<bool>,
    public StaticText<TEXT_SETBACKLED>,
    public BackLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class DebugMenu :
    public StaticText<TEXT_DEBUG>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_BUZZER>,      DefaultFont, DefaultColor, SwitchScreenAction<BuzzerMenu<DebugMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTLED>, DefaultFont, DefaultColor, SwitchScreenAction<FrontLedChangeScreen<DebugMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKLED>,  DefaultFont, DefaultColor, SwitchScreenAction<BackLedChangeScreen<DebugMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_DYNAMICMENU>, DefaultFont, DefaultColor, SwitchScreenAction<DynamicDebugMenu<DebugMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >
{};
}
