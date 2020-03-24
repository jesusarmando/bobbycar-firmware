#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeBrems1WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeBrems1WertDisplay();
};

SetDefaultModeBrems1WertDisplay::SetDefaultModeBrems1WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set Brems 1 Wert", modes::defaultMode.brems1_wert}
{
}
}
