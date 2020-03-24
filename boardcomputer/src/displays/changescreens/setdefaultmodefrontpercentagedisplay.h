#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeFrontPercentageDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeFrontPercentageDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set front percentage", modes::defaultMode.frontPercentage, prevDisplay}
    {}
};
}
