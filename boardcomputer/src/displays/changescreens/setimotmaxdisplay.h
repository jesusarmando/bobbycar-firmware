#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetIMotMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu>
{
public:
    SetIMotMaxDisplay();
};

SetIMotMaxDisplay::SetIMotMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu>{"Set iMotMax", settings.iMotMax}
{
}
}
