#pragma once

#include "changevaluedisplay_controltype.h"
#include "modes/manualmode.h"

namespace {
class ManualModeSettingsMenu;
}

namespace {
class SetManualModeCtrlTypDisplay : public ChangeValueDisplay<ControlType, ManualModeSettingsMenu>
{
public:
    SetManualModeCtrlTypDisplay();
};

SetManualModeCtrlTypDisplay::SetManualModeCtrlTypDisplay() :
    ChangeValueDisplay<ControlType, ManualModeSettingsMenu>{modes::manualMode.ctrlTyp}
{
}
}
