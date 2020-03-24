#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetFieldWeakMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX>
{
public:
    SetFieldWeakMaxDisplay();
};

SetFieldWeakMaxDisplay::SetFieldWeakMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu, TEXT_SETFIELDWEAKMAX>{settings.fieldWeakMax}
{
}
}

