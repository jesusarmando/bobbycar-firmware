#pragma once

#include "changevaluedisplay_controlmode.h"

#include "modes/manualmode.h"

namespace {
class SetManualModeCtrlModDisplay : public ChangeValueDisplay<ControlMode>
{
public:
    SetManualModeCtrlModDisplay(Display &prevDisplay) :
        ChangeValueDisplay<ControlMode>{modes::manualMode.ctrlMod, prevDisplay}
    {}
};
}
