#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/potisettingsmenu.h"
#include "globals.h"

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
