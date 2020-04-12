#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/tempomatmode.h"

namespace {
struct TempomatModeCtrlTypAccessor : public RefAccessor<ControlType> { ControlType &getRef() const override { return modes::tempomatMode.ctrlTyp; } };
template<typename Tscreen>
class TempomatModeCtrlTypChangeScreen :
    public StaticText<TEXT_SETCONTROLMODE>,
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
    public StaticText<TEXT_SETCONTROLMODE>,
    public ChangeValueDisplay<ControlMode>,
    public TempomatModeCtrlModAccessor
{
    using Base = ChangeValueDisplay<ControlMode>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class TempomatModeSettingsMenu :
    public StaticText<TEXT_TEMPOMATMODESETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLTYPE>, DefaultFont, DefaultColor, SwitchScreenAction<TempomatModeCtrlTypChangeScreen<TempomatModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETCONTROLMODE>, DefaultFont, DefaultColor, SwitchScreenAction<TempomatModeCtrlModChangeScreen<TempomatModeSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,           DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
