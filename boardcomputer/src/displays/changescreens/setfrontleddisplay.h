#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
class SetFrontLedDisplay : public ChangeValueDisplay<bool, MainMenu, TEXT_SETFRONTLED>
{
public:
    SetFrontLedDisplay();
};

SetFrontLedDisplay::SetFrontLedDisplay() :
    ChangeValueDisplay<bool, MainMenu, TEXT_SETFRONTLED>{front.command.led}
{
}
}
