#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class BuzzerMenu;
}

namespace {
class SetFrontPatternDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETFRONTPATTERN>
{
public:
    SetFrontPatternDisplay();
};

SetFrontPatternDisplay::SetFrontPatternDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETFRONTPATTERN>{front.command.buzzer.pattern}
{
}
}
