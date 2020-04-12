#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
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
class SelectModeMenu :
    public StaticText<TEXT_SELECTMODE>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULT>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMAT>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSM>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTH>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WEBSOCKET>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,      DefaultFont, DefaultColor, DummyAction>
    >,
    public ModeAccessor
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULT>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMAT>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSM>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTH>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WEBSOCKET>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,      DefaultFont, DefaultColor, DummyAction>
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
        setSelectedIndex(0);
    else if (getValue() == TempomatModeAccessor::getValue())
        setSelectedIndex(1);
    else if (getValue() == LarsmModeAccessor::getValue())
        setSelectedIndex(2);
    else if (getValue() == BluetoothModeAccessor::getValue())
        setSelectedIndex(3);
    else if (getValue() == WebsocketModeAccessor::getValue())
        setSelectedIndex(4);
    else
    {
        Serial.printf("Unknown mode: %s", getValue()->displayName());
        setSelectedIndex(5);
    }
}

template<typename Tscreen>
void SelectModeMenu<Tscreen>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
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
