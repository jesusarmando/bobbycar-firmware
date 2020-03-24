#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetBackRightEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu>
{
public:
    SetBackRightEnabledDisplay();
};

SetBackRightEnabledDisplay::SetBackRightEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu>{"Enable back right", back.command.right.enable}
{
}
}
