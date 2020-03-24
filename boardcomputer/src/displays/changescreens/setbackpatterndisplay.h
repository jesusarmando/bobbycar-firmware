#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/buzzermenu.h"
#include "globals.h"

namespace {
class SetBackPatternDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu>
{
public:
    SetBackPatternDisplay();
};

SetBackPatternDisplay::SetBackPatternDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu>{"Set back freq", back.command.buzzer.pattern}
{
}
}
