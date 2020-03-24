#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeBackPercentageDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE>
{
public:
    SetDefaultModeBackPercentageDisplay();
};

SetDefaultModeBackPercentageDisplay::SetDefaultModeBackPercentageDisplay():
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBACKPERCENTAGE>{modes::defaultMode.backPercentage}
{
}
}
