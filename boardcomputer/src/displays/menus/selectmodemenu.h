#pragma once

#include "staticmenudisplay.h"
#include "accessorhelper.h"
#include "menuitems/setdynamicvaluemenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "modes/bluetoothmode.h"

namespace {
struct ModeAccessor { static auto &getRef() { return currentMode; } };
struct DefaultModeAccessor { static auto getValue() { return &modes::defaultMode; } };
struct TempomatModeAccessor { static auto getValue() { return &modes::tempomatMode; } };
struct BluetoothModeAccessor { static auto getValue() { return &modes::bluetoothMode; } };

template<typename Tscreen>
class SelectModeMenu final :
    public StaticTitle<TEXT_SELECTMODE>,
    public StaticMenuDisplay<
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, DefaultModeAccessor, Tscreen, TEXT_DEFAULT>,
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, TempomatModeAccessor, Tscreen, TEXT_TEMPOMAT>,
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, BluetoothModeAccessor, Tscreen, TEXT_BLUETOOTH>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, DefaultModeAccessor, Tscreen, TEXT_DEFAULT>,
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, TempomatModeAccessor, Tscreen, TEXT_TEMPOMAT>,
        SetDynamicValueMenuItem<ModeBase*, AccessorHelper<ModeAccessor>, BluetoothModeAccessor, Tscreen, TEXT_BLUETOOTH>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Tscreen>
void SelectModeMenu<Tscreen>::start()
{
    Base::start();

    if (AccessorHelper<ModeAccessor>::getValue() == DefaultModeAccessor::getValue())
        Base::setSelectedIndex(0);
    else if (AccessorHelper<ModeAccessor>::getValue() == TempomatModeAccessor::getValue())
        Base::setSelectedIndex(1);
    else if (AccessorHelper<ModeAccessor>::getValue() == BluetoothModeAccessor::getValue())
        Base::setSelectedIndex(2);
    else
        Base::setSelectedIndex(3);
}
}
