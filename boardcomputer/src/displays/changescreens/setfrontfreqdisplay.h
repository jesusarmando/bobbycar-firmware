#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class BuzzerMenu;
}

namespace {
class SetFrontFreqDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETFRONTFREQ>
{
public:
    SetFrontFreqDisplay();
};

SetFrontFreqDisplay::SetFrontFreqDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETFRONTFREQ>{front.command.buzzer.freq}
{
}
}
