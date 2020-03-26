#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/setdynamicvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
class CommonSettingsMenu;
}

namespace {
struct ModeAccessor { static auto &getRef() { return currentMode; } };
struct DefaultModeGetter { static auto getValue() { return &modes::defaultMode; } };
struct ManualModeGetter { static auto getValue() { return &modes::manualMode; } };
struct BluetoothModeGetter { static auto getValue() { return &modes::bluetoothMode; } };

class SelectModeMenu final : public MenuDisplay<
    TEXT_SELECTMODE,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, DefaultModeGetter, CommonSettingsMenu, TEXT_DEFAULT>,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, ManualModeGetter, CommonSettingsMenu, TEXT_MANUAL>,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, BluetoothModeGetter, CommonSettingsMenu, TEXT_BLUETOOTH>,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_BACK>
>
{
public:
    void start() override;
};

void SelectModeMenu::start()
{
    MenuDisplay::start();

    if (ModeAccessor::getRef() == DefaultModeGetter::getValue())
        setSelectedItem(begin() + 0);
    else if (ModeAccessor::getRef() == ManualModeGetter::getValue())
        setSelectedItem(begin() + 1);
    else if (ModeAccessor::getRef() == BluetoothModeGetter::getValue())
        setSelectedItem(begin() + 2);
    else
        setSelectedItem(begin() + 3);
}
}
