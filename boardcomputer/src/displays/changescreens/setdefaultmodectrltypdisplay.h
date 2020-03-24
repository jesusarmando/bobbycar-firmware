#pragma once

#include "changevaluedisplay_controltype.h"

#include "modes/defaultmode.h"

namespace {
class SetDefaultModeCtrlTypDisplay : public ChangeValueDisplay<ControlType>
{
public:
    SetDefaultModeCtrlTypDisplay(Display &prevDisplay) :
        ChangeValueDisplay<ControlType>{modes::defaultMode.ctrlTyp, prevDisplay}
    {}
};
}
