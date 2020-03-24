#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class PotiSettingsMenu;
}

namespace {
class SetBremsMinDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETBREMSMIN>
{
public:
    SetBremsMinDisplay();
};

SetBremsMinDisplay::SetBremsMinDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu, TEXT_SETBREMSMIN>{bremsMin}
{
}
}
