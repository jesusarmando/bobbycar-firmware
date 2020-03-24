#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetPhaseAdvMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETPHASEADVMAX>
{
public:
    SetPhaseAdvMaxDisplay();
};

SetPhaseAdvMaxDisplay::SetPhaseAdvMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETPHASEADVMAX>{settings.phaseAdvMax}
{
}
}
