#pragma once

#include "changevaluedisplay_controlmode.h"
#include "texts.h"
#include "modes/manualmode.h"

namespace {
class ManualModeSettingsMenu;
}

namespace {
class SetManualModeCtrlModDisplay : public ChangeValueDisplay<ControlMode, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>
{
public:
    SetManualModeCtrlModDisplay();
};

SetManualModeCtrlModDisplay::SetManualModeCtrlModDisplay() :
    ChangeValueDisplay<ControlMode, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>{modes::manualMode.ctrlMod}
{
}
}
