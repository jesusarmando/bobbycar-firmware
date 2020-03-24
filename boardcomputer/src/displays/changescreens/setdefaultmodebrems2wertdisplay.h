#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBrems2WertDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeBrems2WertDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set Brems 2 Wert", modes::defaultMode.brems2_wert, prevDisplay}
    {}
};
}
