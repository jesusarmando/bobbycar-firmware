#pragma once

#include "changevaluedisplay_controlmode.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeCtrlModDisplay : public ChangeValueDisplay<ControlMode, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE>
{
public:
    SetDefaultModeCtrlModDisplay();
};

SetDefaultModeCtrlModDisplay::SetDefaultModeCtrlModDisplay() :
    ChangeValueDisplay<ControlMode, DefaultModeSettingsMenu, TEXT_SETCONTROLMODE>{modes::defaultMode.ctrlMod}
{
}
}
