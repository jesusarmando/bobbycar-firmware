#pragma once

#include <WiFiGeneric.h>

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/backmenuitem.h"
#include "menuitems/setvaluemenuitem.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_power_t> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_WIFI_POWER_19_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_19dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_18_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_17dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_15dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_13dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_11dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_8_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_7dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_2dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_MINUS_1dBm>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<wifi_power_t>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_WIFI_POWER_19_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_19dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_18_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_17dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_15dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_13dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_11dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_8_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_7dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_5dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_2dBm>,
        StaticDummyMenuItem<TEXT_WIFI_POWER_MINUS_1dBm>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<wifi_power_t>::start()
{
    Base::start();

    if (getValue() == WIFI_POWER_19_5dBm)
        Base::setSelectedIndex(0);
    else if (getValue() == WIFI_POWER_19dBm)
        Base::setSelectedIndex(1);
    else if (getValue() == WIFI_POWER_18_5dBm)
        Base::setSelectedIndex(2);
    else if (getValue() == WIFI_POWER_17dBm)
        Base::setSelectedIndex(3);
    else if (getValue() == WIFI_POWER_15dBm)
        Base::setSelectedIndex(4);
    else if (getValue() == WIFI_POWER_13dBm)
        Base::setSelectedIndex(5);
    else if (getValue() == WIFI_POWER_11dBm)
        Base::setSelectedIndex(6);
    else if (getValue() == WIFI_POWER_8_5dBm)
        Base::setSelectedIndex(7);
    else if (getValue() == WIFI_POWER_7dBm)
        Base::setSelectedIndex(8);
    else if (getValue() == WIFI_POWER_5dBm)
        Base::setSelectedIndex(9);
    else if (getValue() == WIFI_POWER_2dBm)
        Base::setSelectedIndex(10);
    else if (getValue() == WIFI_POWER_MINUS_1dBm)
        Base::setSelectedIndex(11);
    else
    {
        Serial.printf("Unknown wifi_power_t: %i", int(getValue()));
        Base::setSelectedIndex(12);
    }
}

void ChangeValueDisplay<wifi_power_t>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
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
