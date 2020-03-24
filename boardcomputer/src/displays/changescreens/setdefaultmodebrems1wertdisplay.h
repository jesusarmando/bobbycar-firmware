#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeBrems1WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT>
{
public:
    SetDefaultModeBrems1WertDisplay();
};

SetDefaultModeBrems1WertDisplay::SetDefaultModeBrems1WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBREMS1WERT>{modes::defaultMode.brems1_wert}
{
}
}
