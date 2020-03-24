#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class SetIMotMaxDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetIMotMaxDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set iMotMax", settings.iMotMax, prevDisplay}
    {}
};
}
