#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeGas2WertDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeGas2WertDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set Gas 2 Wert", modes::defaultMode.gas2_wert, prevDisplay}
    {}
};
}
