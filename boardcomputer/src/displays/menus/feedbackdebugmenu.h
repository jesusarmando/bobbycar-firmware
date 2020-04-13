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
class FeedbackDebugMenu :
    public MenuDisplay,
    public StaticText<Ttext>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, typename Ttexts::BatVoltageText,       ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BatVoltageFixedText,  ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BoardTempText,        ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BoardTempFixedText,   ColorInterface, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::TimeoutCntSerialText, StaticFont<2>, ColorInterface, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};

class FrontFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_FRONTFEEDBACK, FrontTexts, FrontFeedbackColor> {};
class BackFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_BACKFEEDBACK, BackTexts, FrontFeedbackColor> {}; }
