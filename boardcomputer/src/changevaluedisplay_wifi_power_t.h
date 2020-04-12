#pragma once

#include <WiFiGeneric.h>

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<>
class ChangeValueDisplay<wifi_power_t> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19_5dBm>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_18_5dBm>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_17dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_15dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_13dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_11dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_8_5dBm>,      DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_7dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_5dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_2dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_MINUS_1dBm>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                   DefaultFont, DefaultColor, DummyAction>
    >,
    public virtual AccessorInterface<wifi_power_t>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19_5dBm>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_19dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_18_5dBm>,     DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_17dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_15dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_13dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_11dBm>,       DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_8_5dBm>,      DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_7dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_5dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_2dBm>,        DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFI_POWER_MINUS_1dBm>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                   DefaultFont, DefaultColor, DummyAction>
    >;

public:
    void start() override;

    void triggered() override;
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

void ChangeValueDisplay<wifi_power_t>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
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
}
}
