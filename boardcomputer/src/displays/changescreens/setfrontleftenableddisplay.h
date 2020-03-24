#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetFrontLeftEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu>
{
public:
    SetFrontLeftEnabledDisplay();
};

SetFrontLeftEnabledDisplay::SetFrontLeftEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu>{"Enable front left", front.command.left.enable}
{
}
}
