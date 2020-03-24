#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetPhaseAdvMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu>
{
public:
    SetPhaseAdvMaxDisplay();
};

SetPhaseAdvMaxDisplay::SetPhaseAdvMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu>{"Set phaseAdvMax", settings.phaseAdvMax}
{
}
}
