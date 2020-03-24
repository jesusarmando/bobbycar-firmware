#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class BuzzerMenu;
}

namespace {
class SetBackPatternDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETBACKPATTERN>
{
public:
    SetBackPatternDisplay();
};

SetBackPatternDisplay::SetBackPatternDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETBACKPATTERN>{back.command.buzzer.pattern}
{
}
}
