#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBrems2WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeBrems2WertDisplay();
};

SetDefaultModeBrems2WertDisplay::SetDefaultModeBrems2WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set Brems 2 Wert", modes::defaultMode.brems2_wert}
{
}
}
