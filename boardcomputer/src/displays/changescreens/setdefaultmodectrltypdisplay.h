#pragma once

#include "changevaluedisplay_controltype.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeCtrlTypDisplay : public ChangeValueDisplay<ControlType, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE>
{
public:
    SetDefaultModeCtrlTypDisplay();
};

SetDefaultModeCtrlTypDisplay::SetDefaultModeCtrlTypDisplay() :
    ChangeValueDisplay<ControlType, DefaultModeSettingsMenu, TEXT_SETCONTROLTYPE>{modes::defaultMode.ctrlTyp}
{
}
}
