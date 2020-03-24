#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/buzzermenu.h"
#include "globals.h"

namespace {
class SetFrontPatternDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu>
{
public:
    SetFrontPatternDisplay();
};

SetFrontPatternDisplay::SetFrontPatternDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu>{"Set front pattern", front.command.buzzer.pattern}
{
}
}
