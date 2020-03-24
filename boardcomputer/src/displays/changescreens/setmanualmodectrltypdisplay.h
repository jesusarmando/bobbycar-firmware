#pragma once

#include "changevaluedisplay_controltype.h"
#include "texts.h"
#include "modes/manualmode.h"

namespace {
class ManualModeSettingsMenu;
}

namespace {
class SetManualModeCtrlTypDisplay : public ChangeValueDisplay<ControlType, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>
{
public:
    SetManualModeCtrlTypDisplay();
};

SetManualModeCtrlTypDisplay::SetManualModeCtrlTypDisplay() :
    ChangeValueDisplay<ControlType, ManualModeSettingsMenu, TEXT_SETCONTROLMODE>{modes::manualMode.ctrlTyp}
{
}
}
