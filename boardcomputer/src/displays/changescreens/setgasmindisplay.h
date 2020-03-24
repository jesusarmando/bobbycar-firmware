#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/potisettingsmenu.h"
#include "globals.h"

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
