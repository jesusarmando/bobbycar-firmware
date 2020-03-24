#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class SetNMotMaxDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetNMotMaxDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set nMotMax", settings.nMotMax, prevDisplay}
    {}
};
}
