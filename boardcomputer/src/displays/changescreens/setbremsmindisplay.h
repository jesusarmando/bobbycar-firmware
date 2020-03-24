#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/potisettingsmenu.h"
#include "globals.h"

namespace {
class SetBremsMinDisplay : public ChangeValueDisplay<int16_t, PotiSettingsMenu>
{
public:
    SetBremsMinDisplay();
};

SetBremsMinDisplay::SetBremsMinDisplay() :
    ChangeValueDisplay<int16_t, PotiSettingsMenu>{"Set bremsMin", bremsMin}
{
}
}
