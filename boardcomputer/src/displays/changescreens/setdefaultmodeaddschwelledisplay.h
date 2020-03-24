#pragma once

#include "changevaluedisplay.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeAddSchwelleDisplay : public ChangeValueDisplay<int16_t>
{
public:
    SetDefaultModeAddSchwelleDisplay(Display &prevDisplay):
        ChangeValueDisplay<int16_t>{"Set add Schwelle", modes::defaultMode.add_schwelle, prevDisplay}
    {}
};
}
