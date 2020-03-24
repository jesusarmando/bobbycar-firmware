#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class SetPhaseAdvMaxDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetPhaseAdvMaxDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set phaseAdvMax", settings.phaseAdvMax, prevDisplay}
    {}
};
}
