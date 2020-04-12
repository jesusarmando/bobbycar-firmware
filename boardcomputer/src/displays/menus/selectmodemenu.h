#pragma once

#include "staticmenudisplay.h"
#include "changevaluedisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"
#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "modes/larsmmode.h"
#include "modes/bluetoothmode.h"
#include "modes/websocketmode.h"

namespace {
struct ModeAccessor : public RefAccessor<ModeInterface *> { ModeInterface * &getRef() const { return currentMode; } };
struct DefaultModeAccessor { static auto getValue() { return &modes::defaultMode; } };
struct TempomatModeAccessor { static auto getValue() { return &modes::tempomatMode; } };
struct LarsmModeAccessor { static auto getValue() { return &modes::larsmMode; } };
struct BluetoothModeAccessor { static auto getValue() { return &modes::bluetoothMode; } };
struct WebsocketModeAccessor { static auto getValue() { return &modes::websocketMode; } };

template<typename Tscreen>
class SelectModeMenu final :
    public StaticTitle<TEXT_SELECTMODE>,
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_DEFAULT>,
        StaticDummyMenuItem<TEXT_TEMPOMAT>,
        StaticDummyMenuItem<TEXT_LARSM>,
        StaticDummyMenuItem<TEXT_BLUETOOTH>,
        StaticDummyMenuItem<TEXT_WEBSOCKET>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public ModeAccessor
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_DEFAULT>,
        StaticDummyMenuItem<TEXT_TEMPOMAT>,
        StaticDummyMenuItem<TEXT_LARSM>,
        StaticDummyMenuItem<TEXT_BLUETOOTH>,
        StaticDummyMenuItem<TEXT_WEBSOCKET>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

template<typename Tscreen>
void SelectModeMenu<Tscreen>::start()
{
    Base::start();

    if (getValue() == DefaultModeAccessor::getValue())
        Base::setSelectedIndex(0);
    else if (getValue() == TempomatModeAccessor::getValue())
        Base::setSelectedIndex(1);
    else if (getValue() == LarsmModeAccessor::getValue())
        Base::setSelectedIndex(2);
    else if (getValue() == BluetoothModeAccessor::getValue())
        Base::setSelectedIndex(3);
    else if (getValue() == WebsocketModeAccessor::getValue())
        Base::setSelectedIndex(4);
    else
    {
        Serial.printf("Unknown mode: %s", getValue()->displayName());
        Base::setSelectedIndex(5);
    }
}

template<typename Tscreen>
void SelectModeMenu<Tscreen>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(DefaultModeAccessor::getValue()); break;
    case 1: setValue(TempomatModeAccessor::getValue()); break;
    case 2: setValue(LarsmModeAccessor::getValue()); break;
    case 3: setValue(BluetoothModeAccessor::getValue()); break;
    case 4: setValue(WebsocketModeAccessor::getValue()); break;
    }

    switchScreen<Tscreen>();
}
}
