#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetFrontLeftEnabledDisplay : public ChangeValueDisplay<bool>
{
public:
    SetFrontLeftEnabledDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Enable front left", front.command.left.enable, prevDisplay}
    {}
};
}
