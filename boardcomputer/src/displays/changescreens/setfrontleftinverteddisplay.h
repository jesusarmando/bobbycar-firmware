#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetFrontLeftInvertedDisplay : public ChangeValueDisplay<bool>
{
public:
    SetFrontLeftInvertedDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Invert front left", front.invertLeft, prevDisplay}
    {}
};
}
