#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeGas2WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeGas2WertDisplay();
};

SetDefaultModeGas2WertDisplay::SetDefaultModeGas2WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set Gas 2 Wert", modes::defaultMode.gas2_wert}
{
}
}
