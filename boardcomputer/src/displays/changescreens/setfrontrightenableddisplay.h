#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetFrontRightEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEFRONTRIGHT>
{
public:
    SetFrontRightEnabledDisplay();
};

SetFrontRightEnabledDisplay::SetFrontRightEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEFRONTRIGHT>{front.command.right.enable}
{
}
}
