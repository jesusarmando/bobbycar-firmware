#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class BuzzerMenu;
}

namespace {
class SetBackFreqDisplay : public ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETBACKFREQ>
{
public:
    SetBackFreqDisplay();
};

SetBackFreqDisplay::SetBackFreqDisplay() :
    ChangeValueDisplay<uint8_t, BuzzerMenu, TEXT_SETBACKFREQ>{back.command.buzzer.freq}
{
}
}
