#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetFrontRightInvertedDisplay : public ChangeValueDisplay<bool>
{
public:
    SetFrontRightInvertedDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Invert front right", front.invertRight, prevDisplay}
    {}
};
}
