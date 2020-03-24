#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

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
