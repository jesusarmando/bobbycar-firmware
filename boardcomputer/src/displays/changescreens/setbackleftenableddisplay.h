#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetBackLeftEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu>
{
public:
    SetBackLeftEnabledDisplay();
};

SetBackLeftEnabledDisplay::SetBackLeftEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu>{"Enable back left", back.command.left.enable}
{
}
}
