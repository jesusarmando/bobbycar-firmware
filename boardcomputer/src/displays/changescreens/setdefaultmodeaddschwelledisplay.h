#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeAddSchwelleDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE>
{
public:
    SetDefaultModeAddSchwelleDisplay();
};

SetDefaultModeAddSchwelleDisplay::SetDefaultModeAddSchwelleDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETADDSCHWELLE>{modes::defaultMode.add_schwelle}
{
}
}
