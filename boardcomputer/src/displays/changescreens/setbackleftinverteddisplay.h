#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetBackLeftInvertedDisplay : public ChangeValueDisplay<bool>
{
public:
    SetBackLeftInvertedDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Invert back left", back.invertLeft, prevDisplay}
    {}
};
}
