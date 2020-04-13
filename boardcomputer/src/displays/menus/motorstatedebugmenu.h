#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "debugtexthelpers.h"

namespace {
class DebugMenu;
}

namespace {
template<const char *Ttext, typename Ttexts>
class MotorStateDebugMenu :
    public MenuDisplay,
    public StaticText<Ttext>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, typename Ttexts::EnableText,       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::PwmText,          DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::CtrlTypText,      DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::CtrlModText,      DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::IMotMaxText,      DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::IDcMaxText,       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::NMotMaxText,      DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::FieldWeakMaxText, DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::PhaseAdvMaxText,  DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,    SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};

class FrontLeftMotorStateDebugMenu : public MotorStateDebugMenu<TEXT_FRONTLEFTCOMMAND, FrontTexts::LeftCommand> {};
class FrontRightMotorStateDebugMenu : public MotorStateDebugMenu<TEXT_FRONTRIGHTCOMMAND, FrontTexts::RightCommand> {};
class BackLeftMotorStateDebugMenu : public MotorStateDebugMenu<TEXT_BACKLEFTCOMMAND, BackTexts::LeftCommand> {};
class BackRightMotorStateDebugMenu : public MotorStateDebugMenu<TEXT_BACKRIGHTCOMMAND, BackTexts::RightCommand> {};
}