#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
template<typename Tscreen>
class FrontLedChangeScreen :
    public StaticTitle<TEXT_SETFRONTLED>,
    public ChangeValueDisplay<bool>,
    public FrontLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };
template<typename Tscreen>
class BackLedChangeScreen :
    public StaticTitle<TEXT_SETBACKLED>,
    public ChangeValueDisplay<bool>,
    public BackLedAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class DebugMenu final :
    public StaticTitle<TEXT_DEBUG>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<BuzzerMenu<DebugMenu<Tscreen>>, TEXT_BUZZER>,
        StaticSwitchScreenMenuItem<FrontLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETFRONTLED>,
        StaticSwitchScreenMenuItem<BackLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETBACKLED>,
        StaticSwitchScreenMenuItem<DynamicDebugMenu<DebugMenu<Tscreen>>, TEXT_DYNAMICMENU>,
        BackMenuItem<Tscreen>
    >
{};
}
