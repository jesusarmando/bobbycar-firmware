#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetNMotMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu>
{
public:
    SetNMotMaxDisplay();
};

SetNMotMaxDisplay::SetNMotMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu>{"Set nMotMax", settings.nMotMax}
{
}
}
