#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/tempomatmode.h"

namespace {
struct TempomatModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::tempomatMode.ctrlTyp; } };
template<typename Tscreen>
class TempomatModeCtrlTypChangeScreen :
    public StaticTitle<TEXT_SETCONTROLMODE>,
    public ChangeValueDisplay<ControlType>,
    public TempomatModeCtrlTypAccessor
{
    using Base = ChangeValueDisplay<ControlType>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct TempomatModeCtrlModAccessor : public RefAccessor<ControlMode> { ControlMode &getRef() const override { return modes::tempomatMode.ctrlMod; } };
template<typename Tscreen>
class TempomatModeCtrlModChangeScreen :
    public StaticTitle<TEXT_SETCONTROLMODE>,
    public ChangeValueDisplay<ControlMode>,
    public TempomatModeCtrlModAccessor
{
    using Base = ChangeValueDisplay<ControlMode>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class TempomatModeSettingsMenu final :
    public StaticTitle<TEXT_TEMPOMATMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLTYPE>,
        StaticSwitchScreenMenuItem<TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<Tscreen>>, TEXT_SETCONTROLMODE>,
        BackMenuItem<Tscreen>
    >
{};
}
