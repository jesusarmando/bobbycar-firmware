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
template<const char *Ttext, typename Ttexts, template<int> class ColorInterface>
class FeedbackDebugMenu :
    public MenuDisplay,
    public StaticText<Ttext>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, typename Ttexts::BatVoltageText,       ColorInterface<TFT_DARKGREY>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BatVoltageFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BoardTempText,        ColorInterface<TFT_DARKGREY>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::BoardTempFixedText,   ColorInterface<TFT_DARKGREY>, DummyAction>,
        makeComponent<MenuItem, typename Ttexts::TimeoutCntSerialText, StaticFont<2>, ColorInterface<TFT_DARKGREY>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};

class FrontFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_FRONTFEEDBACK, FrontTexts, FrontFeedbackColor> {};
class BackFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_BACKFEEDBACK, BackTexts, FrontFeedbackColor> {}; }
