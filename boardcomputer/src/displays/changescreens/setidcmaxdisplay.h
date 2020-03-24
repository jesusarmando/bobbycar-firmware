#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class SetIDcMaxDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetIDcMaxDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set iDcMax", settings.iDcMax, prevDisplay}
    {}
};
}
