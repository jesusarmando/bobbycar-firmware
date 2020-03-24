#pragma once

#include "changevaluedisplay_controlmode.h"

#include "modes/defaultmode.h"

namespace {
class SetDefaultModeCtrlModDisplay : public ChangeValueDisplay<ControlMode>
{
public:
    SetDefaultModeCtrlModDisplay(Display &prevDisplay) :
        ChangeValueDisplay<ControlMode>{modes::defaultMode.ctrlMod, prevDisplay}
    {}
};
}
