#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetBremsMaxDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETBREMSMAX>
{
public:
    SetBremsMaxDisplay();
};

SetBremsMaxDisplay::SetBremsMaxDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETBREMSMAX>{bremsMax}
{
}
}
