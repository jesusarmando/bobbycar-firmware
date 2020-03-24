#pragma once

#include "changevaluedisplay.h"
#include "globals.h"

namespace {
class CommonSettingsMenu;
}

namespace {
class SetFieldWeakMaxDisplay : public ChangeValueDisplay<int16_t, CommonSettingsMenu>
{
public:
    SetFieldWeakMaxDisplay();
};

SetFieldWeakMaxDisplay::SetFieldWeakMaxDisplay() :
    ChangeValueDisplay<int16_t, CommonSettingsMenu>{"Set fieldWeakMax", settings.fieldWeakMax}
{
}
}

