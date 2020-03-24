#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetIMotMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETIMOTMAX>
{
public:
    SetIMotMaxDisplay();
};

SetIMotMaxDisplay::SetIMotMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETIMOTMAX>{settings.iMotMax}
{
}
}
