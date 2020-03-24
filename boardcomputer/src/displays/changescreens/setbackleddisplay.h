#pragma once

#include "changevaluedisplay_bool.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
class SetBackLedDisplay : public ChangeValueDisplay<bool, MainMenu>
{
public:
    SetBackLedDisplay();
};

SetBackLedDisplay::SetBackLedDisplay() :
    ChangeValueDisplay<bool, MainMenu>{"Set back LED", back.command.led}
{
}
}
