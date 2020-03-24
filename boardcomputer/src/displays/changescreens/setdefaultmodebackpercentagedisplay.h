#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBackPercentageDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeBackPercentageDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set back percentage", modes::defaultMode.backPercentage, prevDisplay}
    {}
};
}
