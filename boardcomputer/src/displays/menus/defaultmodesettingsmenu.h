#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SetDefaultModeCtrlTypDisplay;
class SetDefaultModeCtrlModDisplay;
class SetDefaultModeEnableFieldWeakeningSmootheningDisplay;
class SetDefaultModeWeakeningSmootheningDisplay;
class SetDefaultModeFrontPercentageDisplay;
class SetDefaultModeBackPercentageDisplay;
class SetDefaultModeAddSchwelleDisplay;
class SetDefaultModeGas1WertDisplay;
class SetDefaultModeGas2WertDisplay;
class SetDefaultModeBrems1WertDisplay;
class SetDefaultModeBrems2WertDisplay;
class SettingsMenu;
}

namespace {
class DefaultModeSettingsMenu final : public MenuDisplay<
    TEXT_DEFAULTMODESETTIGNS,
    SwitchScreenMenuItem<SetDefaultModeCtrlTypDisplay, TEXT_SETCONTROLTYPE>,
    SwitchScreenMenuItem<SetDefaultModeCtrlModDisplay, TEXT_SETCONTROLMODE>,
    SwitchScreenMenuItem<SetDefaultModeEnableFieldWeakeningSmootheningDisplay, TEXT_ENABLEWEAKENINGSMOOTHENING>,
    SwitchScreenMenuItem<SetDefaultModeWeakeningSmootheningDisplay, TEXT_SETWEAKINGSMOOTHENING>,
    SwitchScreenMenuItem<SetDefaultModeFrontPercentageDisplay, TEXT_SETFRONTPERCENTAGE>,
    SwitchScreenMenuItem<SetDefaultModeBackPercentageDisplay, TEXT_SETBACKPERCENTAGE>,
    SwitchScreenMenuItem<SetDefaultModeAddSchwelleDisplay, TEXT_SETADDSCHWELLE>,
    SwitchScreenMenuItem<SetDefaultModeGas1WertDisplay, TEXT_SETGAS1WERT>,
    SwitchScreenMenuItem<SetDefaultModeGas2WertDisplay, TEXT_SETGAS2WERT>,
    SwitchScreenMenuItem<SetDefaultModeBrems1WertDisplay, TEXT_SETBREMS1WERT>,
    SwitchScreenMenuItem<SetDefaultModeBrems2WertDisplay, TEXT_SETBREMS2WERT>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
