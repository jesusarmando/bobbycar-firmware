#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeWeakeningSmootheningDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING>
{
public:
    SetDefaultModeWeakeningSmootheningDisplay();
};

SetDefaultModeWeakeningSmootheningDisplay::SetDefaultModeWeakeningSmootheningDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETWEAKINGSMOOTHENING>{modes::defaultMode.weakeningSmoothening}
{
}
}
