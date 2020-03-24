#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetGasMaxDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu>
{
public:
    SetGasMaxDisplay();
};

SetGasMaxDisplay::SetGasMaxDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu>{"Set gasMax", gasMax}
{
}
}
