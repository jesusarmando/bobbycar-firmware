#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class SetFieldWeakMaxDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetFieldWeakMaxDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set fieldWeakMax", settings.fieldWeakMax, prevDisplay}
    {}
};
}
