#pragma once

#include "changevaluedisplay_controlmode.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeCtrlModDisplay : public ChangeValueDisplay<ControlMode, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeCtrlModDisplay();
};

SetDefaultModeCtrlModDisplay::SetDefaultModeCtrlModDisplay() :
    ChangeValueDisplay<ControlMode, DefaultModeSettingsMenu>{modes::defaultMode.ctrlMod}
{
}
}
