#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeGas1WertDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeGas1WertDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set Gas 1 Wert", modes::defaultMode.gas1_wert, prevDisplay}
    {}
};
}
