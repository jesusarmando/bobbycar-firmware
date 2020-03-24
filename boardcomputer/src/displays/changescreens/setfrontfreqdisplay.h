#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/buzzermenu.h"
#include "globals.h"

namespace {
class SetFrontFreqDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu>
{
public:
    SetFrontFreqDisplay();
};

SetFrontFreqDisplay::SetFrontFreqDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu>{"Set front freq", front.command.buzzer.freq}
{
}
}
