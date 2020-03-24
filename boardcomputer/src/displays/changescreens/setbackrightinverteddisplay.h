#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetBackRightInvertedDisplay : public ChangeValueDisplay<bool>
{
public:
    SetBackRightInvertedDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Invert back right", back.invertRight, prevDisplay}
    {}
};
}
