#pragma once

#include "changevaluedisplay.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "modes/defaultmode.h"

namespace {
class SetDefaultModeAddSchwelleDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>
{
public:
    SetDefaultModeAddSchwelleDisplay();
};

SetDefaultModeAddSchwelleDisplay::SetDefaultModeAddSchwelleDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu>{"Set add Schwelle", modes::defaultMode.add_schwelle}
{
}
}
