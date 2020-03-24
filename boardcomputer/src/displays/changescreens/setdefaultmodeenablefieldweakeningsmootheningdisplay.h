#pragma once

#include "changevaluedisplay_bool.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeEnableFieldWeakeningSmootheningDisplay : public ChangeValueDisplay<bool>
{
public:
    SetDefaultModeEnableFieldWeakeningSmootheningDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Enable weakening smoothening", modes::defaultMode.enableWeakeningSmoothening, prevDisplay}
    {}
};
}
