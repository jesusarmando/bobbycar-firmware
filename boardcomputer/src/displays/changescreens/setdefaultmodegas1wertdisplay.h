#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeGas1WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETGAS1WERT>
{
public:
    SetDefaultModeGas1WertDisplay();
};

SetDefaultModeGas1WertDisplay::SetDefaultModeGas1WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETGAS1WERT>{modes::defaultMode.gas1_wert}
{
}
}
