#pragma once

#include <WiFiGeneric.h>

#include "changevaluedisplay.h"

namespace {
template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<wifi_power_t, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_19_5dBm, Tdisplay, TEXT_WIFI_POWER_19_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_19dBm, Tdisplay, TEXT_WIFI_POWER_19dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_18_5dBm, Tdisplay, TEXT_WIFI_POWER_18_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_17dBm, Tdisplay, TEXT_WIFI_POWER_17dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_15dBm, Tdisplay, TEXT_WIFI_POWER_15dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_13dBm, Tdisplay, TEXT_WIFI_POWER_13dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_11dBm, Tdisplay, TEXT_WIFI_POWER_11dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_8_5dBm, Tdisplay, TEXT_WIFI_POWER_8_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_7dBm, Tdisplay, TEXT_WIFI_POWER_7dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_5dBm, Tdisplay, TEXT_WIFI_POWER_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_2dBm, Tdisplay, TEXT_WIFI_POWER_2dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_MINUS_1dBm, Tdisplay, TEXT_WIFI_POWER_MINUS_1dBm>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_19_5dBm, Tdisplay, TEXT_WIFI_POWER_19_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_19dBm, Tdisplay, TEXT_WIFI_POWER_19dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_18_5dBm, Tdisplay, TEXT_WIFI_POWER_18_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_17dBm, Tdisplay, TEXT_WIFI_POWER_17dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_15dBm, Tdisplay, TEXT_WIFI_POWER_15dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_13dBm, Tdisplay, TEXT_WIFI_POWER_13dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_11dBm, Tdisplay, TEXT_WIFI_POWER_11dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_8_5dBm, Tdisplay, TEXT_WIFI_POWER_8_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_7dBm, Tdisplay, TEXT_WIFI_POWER_7dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_5dBm, Tdisplay, TEXT_WIFI_POWER_5dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_2dBm, Tdisplay, TEXT_WIFI_POWER_2dBm>,
        SetValueMenuItem<wifi_power_t, Taccessor, WIFI_POWER_MINUS_1dBm, Tdisplay, TEXT_WIFI_POWER_MINUS_1dBm>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<wifi_power_t, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == WIFI_POWER_19_5dBm)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == WIFI_POWER_19dBm)
        Base::setSelectedIndex(1);
    else if (Taccessor::getValue() == WIFI_POWER_18_5dBm)
        Base::setSelectedIndex(2);
    else if (Taccessor::getValue() == WIFI_POWER_17dBm)
        Base::setSelectedIndex(3);
    else if (Taccessor::getValue() == WIFI_POWER_15dBm)
        Base::setSelectedIndex(4);
    else if (Taccessor::getValue() == WIFI_POWER_13dBm)
        Base::setSelectedIndex(5);
    else if (Taccessor::getValue() == WIFI_POWER_11dBm)
        Base::setSelectedIndex(6);
    else if (Taccessor::getValue() == WIFI_POWER_8_5dBm)
        Base::setSelectedIndex(7);
    else if (Taccessor::getValue() == WIFI_POWER_7dBm)
        Base::setSelectedIndex(8);
    else if (Taccessor::getValue() == WIFI_POWER_5dBm)
        Base::setSelectedIndex(9);
    else if (Taccessor::getValue() == WIFI_POWER_2dBm)
        Base::setSelectedIndex(10);
    else if (Taccessor::getValue() == WIFI_POWER_MINUS_1dBm)
        Base::setSelectedIndex(11);
    else
    {
        Serial.printf("Unknown wifi_power_t: %i", int(Taccessor::getValue()));
        Base::setSelectedIndex(12);
    }
}
}
