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
#include "debugcolorhelpers.h"

namespace {
class DebugMenu;
}

namespace {
template<const char *Ttext, typename Ttexts, typename ColorInterface>
class MotorFeedbackDebugMenu :
    public MenuDisplay,
    public StaticText<Ttext>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, typename Ttexts::AngleText,        ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::SpeedText,        ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::SpeedKmhText,     ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::ErrorText,        ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::CurrentText,      ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::CurrentFixedText, ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::ChopsText,        ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::HallText,         ColorInterface, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                             SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};

class FrontLeftMotorFeedbackDebugMenu : public MotorFeedbackDebugMenu<TEXT_FRONTLEFTFEEDBACK, FrontTexts::LeftFeedback, FrontFeedbackColor> {};
class FrontRightMotorFeedbackDebugMenu : public MotorFeedbackDebugMenu<TEXT_FRONTRIGHTFEEDBACK, FrontTexts::RightFeedback, FrontFeedbackColor> {};
class BackLeftMotorFeedbackDebugMenu : public MotorFeedbackDebugMenu<TEXT_BACKLEFTFEEDBACK, BackTexts::LeftFeedback, BackFeedbackColor> {};
class BackRightMotorFeedbackDebugMenu : public MotorFeedbackDebugMenu<TEXT_BACKRIGHTFEEDBACK, BackTexts::RightFeedback, BackFeedbackColor> {};
}
