#pragma once

#include "menudisplay.h"
#include "menuitems/setdynamicvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "modes/bluetoothmode.h"

namespace {
struct ModeAccessor { static auto &getRef() { return currentMode; } };
struct DefaultModeGetter { static auto getValue() { return &modes::defaultMode; } };
struct TempomatModeGetter { static auto getValue() { return &modes::tempomatMode; } };
struct BluetoothModeGetter { static auto getValue() { return &modes::bluetoothMode; } };

template<typename Tscreen>
class SelectModeMenu final : public MenuDisplay<
    TEXT_SELECTMODE,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, DefaultModeGetter, Tscreen, TEXT_DEFAULT>,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, TempomatModeGetter, Tscreen, TEXT_TEMPOMAT>,
    SetDynamicValueMenuItem<ModeBase*, ModeAccessor, BluetoothModeGetter, Tscreen, TEXT_BLUETOOTH>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{
    using Base = MenuDisplay<
        TEXT_SELECTMODE,
        SetDynamicValueMenuItem<ModeBase*, ModeAccessor, DefaultModeGetter, Tscreen, TEXT_DEFAULT>,
        SetDynamicValueMenuItem<ModeBase*, ModeAccessor, TempomatModeGetter, Tscreen, TEXT_TEMPOMAT>,
        SetDynamicValueMenuItem<ModeBase*, ModeAccessor, BluetoothModeGetter, Tscreen, TEXT_BLUETOOTH>,
        SwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >;
public:
    void start() override;
};

template<typename Tscreen>
void SelectModeMenu<Tscreen>::start()
{
    Base::start();

    if (ModeAccessor::getRef() == DefaultModeGetter::getValue())
        Base::setSelectedItem(Base::begin() + 0);
    else if (ModeAccessor::getRef() == TempomatModeGetter::getValue())
        Base::setSelectedItem(Base::begin() + 1);
    else if (ModeAccessor::getRef() == BluetoothModeGetter::getValue())
        Base::setSelectedItem(Base::begin() + 2);
    else
        Base::setSelectedItem(Base::begin() + 3);
}
}