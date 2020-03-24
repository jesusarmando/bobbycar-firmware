#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeWeakeningSmootheningDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeWeakeningSmootheningDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set weaking smoothening", modes::defaultMode.weakeningSmoothening, prevDisplay}
    {}
};
}
