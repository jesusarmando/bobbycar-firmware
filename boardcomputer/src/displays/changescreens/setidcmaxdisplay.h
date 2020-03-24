#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetIDcMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu>
{
public:
    SetIDcMaxDisplay();
};

SetIDcMaxDisplay::SetIDcMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu>{"Set iDcMax", settings.iDcMax}
{
}
}
