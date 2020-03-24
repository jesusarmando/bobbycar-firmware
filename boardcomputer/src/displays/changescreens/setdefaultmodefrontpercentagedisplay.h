#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeFrontPercentageDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeFrontPercentageDisplay();
};

SetDefaultModeFrontPercentageDisplay::SetDefaultModeFrontPercentageDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set front percentage", modes::defaultMode.frontPercentage}
{
}
}
