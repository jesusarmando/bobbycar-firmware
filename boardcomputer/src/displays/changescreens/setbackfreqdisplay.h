#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/buzzermenu.h"
#include "globals.h"

namespace {
class SetBackFreqDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu>
{
public:
    SetBackFreqDisplay();
};

SetBackFreqDisplay::SetBackFreqDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu>{"Set back freq", back.command.buzzer.freq}
{
}
}
