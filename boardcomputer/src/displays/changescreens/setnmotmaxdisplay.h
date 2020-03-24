#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetNMotMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETNMOTMAX>
{
public:
    SetNMotMaxDisplay();
};

SetNMotMaxDisplay::SetNMotMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETNMOTMAX>{settings.nMotMax}
{
}
}
