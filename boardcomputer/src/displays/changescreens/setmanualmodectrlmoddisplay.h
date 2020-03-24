#pragma once

#include "changevaluedisplay_controlmode.h"
#include "modes/manualmode.h"

namespace {
class ManualModeSettingsMenu;
}

namespace {
class SetManualModeCtrlModDisplay : public ChangeValueDisplay<ControlMode, ManualModeSettingsMenu>
{
public:
    SetManualModeCtrlModDisplay();
};

SetManualModeCtrlModDisplay::SetManualModeCtrlModDisplay() :
    ChangeValueDisplay<ControlMode, ManualModeSettingsMenu>{modes::manualMode.ctrlMod}
{
}
}
