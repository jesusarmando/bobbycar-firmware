#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetFrontRightEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu>
{
public:
    SetFrontRightEnabledDisplay();
};

SetFrontRightEnabledDisplay::SetFrontRightEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu>{"Enable front right", front.command.right.enable}
{
}
}
