#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBackPercentageDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeBackPercentageDisplay();
};

SetDefaultModeBackPercentageDisplay::SetDefaultModeBackPercentageDisplay():
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set back percentage", modes::defaultMode.backPercentage}
{
}
}
