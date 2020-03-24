#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/potisettingsmenu.h"
#include "globals.h"

namespace {
class SetBremsMaxDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu>
{
public:
    SetBremsMaxDisplay();
};

SetBremsMaxDisplay::SetBremsMaxDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu>{"Set bremsMax", bremsMax}
{
}
}
