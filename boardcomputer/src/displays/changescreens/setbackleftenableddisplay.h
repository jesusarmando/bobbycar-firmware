#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class SetBackLeftEnabledDisplay : public ChangeValueDisplay<bool>
{
public:
    SetBackLeftEnabledDisplay(Display &prevDisplay) :
        ChangeValueDisplay<bool>{"Enable back left", back.command.left.enable, prevDisplay}
    {}
};
}
