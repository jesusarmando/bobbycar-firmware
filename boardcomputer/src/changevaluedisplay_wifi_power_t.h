#pragma once

#include <WiFiGeneric.h>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_power_t> :
    public MenuDisplay,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19_5dBm>,     DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19dBm>,       DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_18_5dBm>,     DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_17dBm>,       DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_15dBm>,       DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_13dBm>,       DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_11dBm>,       DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_8_5dBm>,      DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_7dBm>,        DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_5dBm>,        DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_2dBm>,        DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_MINUS_1dBm>,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                   DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<wifi_power_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    void itemPressed(int index) override;
};

void ChangeValueDisplay<wifi_power_t>::start()
{
    Base::start();

    if (getValue() == WIFI_POWER_19_5dBm)
        setSelectedIndex(0);
    else if (getValue() == WIFI_POWER_19dBm)
        setSelectedIndex(1);
    else if (getValue() == WIFI_POWER_18_5dBm)
        setSelectedIndex(2);
    else if (getValue() == WIFI_POWER_17dBm)
        setSelectedIndex(3);
    else if (getValue() == WIFI_POWER_15dBm)
        setSelectedIndex(4);
    else if (getValue() == WIFI_POWER_13dBm)
        setSelectedIndex(5);
    else if (getValue() == WIFI_POWER_11dBm)
        setSelectedIndex(6);
    else if (getValue() == WIFI_POWER_8_5dBm)
        setSelectedIndex(7);
    else if (getValue() == WIFI_POWER_7dBm)
        setSelectedIndex(8);
    else if (getValue() == WIFI_POWER_5dBm)
        setSelectedIndex(9);
    else if (getValue() == WIFI_POWER_2dBm)
        setSelectedIndex(10);
    else if (getValue() == WIFI_POWER_MINUS_1dBm)
        setSelectedIndex(11);
    else
    {
        Serial.printf("Unknown wifi_power_t: %i", int(getValue()));
        setSelectedIndex(12);
    }
}

void ChangeValueDisplay<wifi_power_t>::itemPressed(int index)
{
    switch (index)
    {
    case 0: setValue(WIFI_POWER_19_5dBm); break;
    case 1: setValue(WIFI_POWER_19dBm); break;
    case 2: setValue(WIFI_POWER_18_5dBm); break;
    case 3: setValue(WIFI_POWER_17dBm); break;
    case 4: setValue(WIFI_POWER_15dBm); break;
    case 5: setValue(WIFI_POWER_13dBm); break;
    case 6: setValue(WIFI_POWER_11dBm); break;
    case 7: setValue(WIFI_POWER_8_5dBm); break;
    case 8: setValue(WIFI_POWER_7dBm); break;
    case 9: setValue(WIFI_POWER_5dBm); break;
    case 10: setValue(WIFI_POWER_2dBm); break;
    case 11: setValue(WIFI_POWER_MINUS_1dBm); break;
    }

    triggered();
}
}
