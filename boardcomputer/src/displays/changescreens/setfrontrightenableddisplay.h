#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetFrontRightEnabledDisplay : public ChangeValueDisplay<bool>
{
public:
    SetFrontRightEnabledDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Enable front right", front.command.right.enable, prevDisplay}
    {}
};
}
