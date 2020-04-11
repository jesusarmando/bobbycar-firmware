#pragma once

#include <esp_wifi_types.h>

#include "changevaluedisplay.h"

namespace {
template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<wifi_mode_t, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_NULL, Tdisplay, TEXT_WIFI_MODE_NULL>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_STA, Tdisplay, TEXT_WIFI_MODE_STA>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_AP, Tdisplay, TEXT_WIFI_MODE_AP>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_APSTA, Tdisplay, TEXT_WIFI_MODE_APSTA>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_NULL, Tdisplay, TEXT_WIFI_MODE_NULL>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_STA, Tdisplay, TEXT_WIFI_MODE_STA>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_AP, Tdisplay, TEXT_WIFI_MODE_AP>,
        SetValueMenuItem<wifi_mode_t, Taccessor, WIFI_MODE_APSTA, Tdisplay, TEXT_WIFI_MODE_APSTA>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<wifi_mode_t, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == WIFI_MODE_NULL)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == WIFI_MODE_STA)
        Base::setSelectedIndex(1);
    else if (Taccessor::getValue() == WIFI_MODE_AP)
        Base::setSelectedIndex(2);
    else if (Taccessor::getValue() == WIFI_MODE_APSTA)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown wifi_mode_t: %i", int(Taccessor::getValue()));
        Base::setSelectedIndex(4);
    }
}
}
