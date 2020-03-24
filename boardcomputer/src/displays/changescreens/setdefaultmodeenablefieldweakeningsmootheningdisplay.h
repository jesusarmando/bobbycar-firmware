#pragma once

#include "changevaluedisplay_bool.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeEnableFieldWeakeningSmootheningDisplay : public ChangeValueDisplay<bool, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING>
{
public:
    SetDefaultModeEnableFieldWeakeningSmootheningDisplay();
};

SetDefaultModeEnableFieldWeakeningSmootheningDisplay::SetDefaultModeEnableFieldWeakeningSmootheningDisplay() :
    ChangeValueDisplay<bool, DefaultModeSettingsMenu, TEXT_ENABLEWEAKENINGSMOOTHENING>{modes::defaultMode.enableWeakeningSmoothening}
{
}
}
