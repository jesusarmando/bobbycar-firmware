#pragma once

#include "changevaluedisplay_bool.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeEnableFieldWeakeningSmootheningDisplay : public ChangeValueDisplay<bool, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeEnableFieldWeakeningSmootheningDisplay();
};

SetDefaultModeEnableFieldWeakeningSmootheningDisplay::SetDefaultModeEnableFieldWeakeningSmootheningDisplay() :
    ChangeValueDisplay<bool, DefaultModeSettingsMenu>{"Enable weakening smoothening", modes::defaultMode.enableWeakeningSmoothening}
{
}
}
