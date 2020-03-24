#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetFrontLeftEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEFRONTLEFT>
{
public:
    SetFrontLeftEnabledDisplay();
};

SetFrontLeftEnabledDisplay::SetFrontLeftEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEFRONTLEFT>{front.command.left.enable}
{
}
}
