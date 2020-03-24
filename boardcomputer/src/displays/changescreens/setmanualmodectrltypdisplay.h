#pragma once

#include "changevaluedisplay_controltype.h"
#include "modes/manualmode.h"

namespace {

class SetManualModeCtrlTypDisplay : public ChangeValueDisplay<ControlType>
{
public:
    SetManualModeCtrlTypDisplay(Display &prevDisplay) :
        ChangeValueDisplay<ControlType>{modes::manualMode.ctrlTyp, prevDisplay}
    {}
};
}
