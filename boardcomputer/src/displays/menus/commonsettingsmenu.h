#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SelectModeMenu;
class SetIMotMaxDisplay;
class SetIDcMaxDisplay;
class SetNMotMaxDisplay;
class SetFieldWeakMaxDisplay;
class SetPhaseAdvMaxDisplay;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
class CommonSettingsMenu final : public MenuDisplay<
    TEXT_COMMONSETTINGS,
    SwitchScreenMenuItem<SelectModeMenu, TEXT_SELECTMODE>,
    SwitchScreenMenuItem<SetIMotMaxDisplay, TEXT_SETIMOTMAX>,
    SwitchScreenMenuItem<SetIDcMaxDisplay, TEXT_SETIDCMAX>,
    SwitchScreenMenuItem<SetNMotMaxDisplay, TEXT_SETNMOTMAX>,
    SwitchScreenMenuItem<SetFieldWeakMaxDisplay, TEXT_SETFIELDWEAKMAX>,
    SwitchScreenMenuItem<SetPhaseAdvMaxDisplay, TEXT_SETPHASEADVMAX>,
    SwitchScreenMenuItem<EnableMenu, TEXT_SETENABLED>,
    SwitchScreenMenuItem<InvertMenu, TEXT_SETINVERTED>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
