#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class EnableMenu;
}

namespace {
class SetBackLeftEnabledDisplay : public ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEBACKLEFT>
{
public:
    SetBackLeftEnabledDisplay();
};

SetBackLeftEnabledDisplay::SetBackLeftEnabledDisplay() :
    ChangeValueDisplay<bool, EnableMenu, TEXT_ENABLEBACKLEFT>{back.command.left.enable}
{
}
}
