#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
class SetFrontLedDisplay : public ChangeValueDisplay<bool, MainMenu>
{
public:
    SetFrontLedDisplay();
};

SetFrontLedDisplay::SetFrontLedDisplay() :
    ChangeValueDisplay<bool, MainMenu>{"Set front LED", front.command.led}
{
}
}
