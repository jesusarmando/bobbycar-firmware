#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetIDcMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETIDCMAX>
{
public:
    SetIDcMaxDisplay();
};

SetIDcMaxDisplay::SetIDcMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETIDCMAX>{settings.iDcMax}
{
}
}
