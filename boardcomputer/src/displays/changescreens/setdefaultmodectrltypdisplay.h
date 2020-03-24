#pragma once

#include "changevaluedisplay_controltype.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeCtrlTypDisplay : public ChangeValueDisplay<ControlType, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeCtrlTypDisplay();
};

SetDefaultModeCtrlTypDisplay::SetDefaultModeCtrlTypDisplay() :
    ChangeValueDisplay<ControlType, DefaultModeSettingsMenu>{modes::defaultMode.ctrlTyp}
{
}
}
