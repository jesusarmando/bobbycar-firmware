#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBrems1WertDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeBrems1WertDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set Brems 1 Wert", modes::defaultMode.brems1_wert, prevDisplay}
    {}
};
}
