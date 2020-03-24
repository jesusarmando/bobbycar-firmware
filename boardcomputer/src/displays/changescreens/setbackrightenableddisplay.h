#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetBackRightEnabledDisplay : public ChangeValueDisplay<bool>
{
public:
    SetBackRightEnabledDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Enable back right", back.command.right.enable, prevDisplay}
    {}
};
}
