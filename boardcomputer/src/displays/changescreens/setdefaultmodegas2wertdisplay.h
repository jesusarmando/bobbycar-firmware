#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeGas2WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETGAS2WERT>
{
public:
    SetDefaultModeGas2WertDisplay();
};

SetDefaultModeGas2WertDisplay::SetDefaultModeGas2WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETGAS2WERT>{modes::defaultMode.gas2_wert}
{
}
}
