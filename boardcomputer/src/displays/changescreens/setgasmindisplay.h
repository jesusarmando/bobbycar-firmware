#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetGasMinDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETGASMIN>
{
public:
    SetGasMinDisplay();
};

SetGasMinDisplay::SetGasMinDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETGASMIN>{gasMin}
{
}
}
