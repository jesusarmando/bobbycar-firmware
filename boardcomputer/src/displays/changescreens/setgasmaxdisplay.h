#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetGasMaxDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETGASMAX>
{
public:
    SetGasMaxDisplay();
};

SetGasMaxDisplay::SetGasMaxDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETGASMAX>{gasMax}
{
}
}
