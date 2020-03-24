#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeFrontPercentageDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE>
{
public:
    SetDefaultModeFrontPercentageDisplay();
};

SetDefaultModeFrontPercentageDisplay::SetDefaultModeFrontPercentageDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETFRONTPERCENTAGE>{modes::defaultMode.frontPercentage}
{
}
}
