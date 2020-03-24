#pragma once

#include "changevaluedisplay.h"
#include "texts.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeSettingsMenu;
}

namespace {
class SetDefaultModeBrems2WertDisplay : public ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT>
{
public:
    SetDefaultModeBrems2WertDisplay();
};

SetDefaultModeBrems2WertDisplay::SetDefaultModeBrems2WertDisplay() :
    ChangeValueDisplay<int16_t, DefaultModeSettingsMenu, TEXT_SETBREMS2WERT>{modes::defaultMode.brems2_wert}
{
}
}
