#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetGasMinDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu>
{
public:
    SetGasMinDisplay();
};

SetGasMinDisplay::SetGasMinDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu>{"Set gasMin", gasMin}
{
}
}
