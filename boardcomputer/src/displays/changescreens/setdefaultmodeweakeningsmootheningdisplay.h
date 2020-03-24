#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeWeakeningSmootheningDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeWeakeningSmootheningDisplay();
};

SetDefaultModeWeakeningSmootheningDisplay::SetDefaultModeWeakeningSmootheningDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set weaking smoothening", modes::defaultMode.weakeningSmoothening}
{
}
}
