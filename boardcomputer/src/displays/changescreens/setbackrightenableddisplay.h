#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetBackRightEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEBACKRIGHT>
{
public:
    SetBackRightEnabledDisplay();
};

SetBackRightEnabledDisplay::SetBackRightEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEBACKRIGHT>{back.command.right.enable}
{
}
}
