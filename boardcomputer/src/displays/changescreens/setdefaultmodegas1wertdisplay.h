#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeGas1WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeGas1WertDisplay();
};

SetDefaultModeGas1WertDisplay::SetDefaultModeGas1WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set Gas 1 Wert", modes::defaultMode.gas1_wert}
{
}
}
