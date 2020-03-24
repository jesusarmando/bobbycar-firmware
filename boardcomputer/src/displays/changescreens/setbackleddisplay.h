#pragma once

#include "changevaluedisplay_bool.h"
#include "texts.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
class SetBackLedDisplay : public ChangeValueDisplay<bool, MainMenu, TEXT_SETBACKLED>
{
public:
    SetBackLedDisplay();
};

SetBackLedDisplay::SetBackLedDisplay() :
    ChangeValueDisplay<bool, MainMenu, TEXT_SETBACKLED>{back.command.led}
{
}
}
