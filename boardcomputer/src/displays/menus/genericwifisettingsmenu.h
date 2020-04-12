#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"

namespace {
struct WifiStatusBitsLiveStatus { static String getText() { return String{"statusBits: "} + WiFi.getStatusBits(); } };
struct WifiChannelLiveStatus { static String getText() { return String{"channel: "} + WiFi.channel(); } };

struct WifiModeAccessor : public virtual AccessorInterface<wifi_mode_t>
{
    wifi_mode_t getValue() const override { return WiFi.getMode(); }
    void setValue(wifi_mode_t value) override
    {
        if (!WiFi.mode(value))
            Serial.println("Could not change WiFi mode!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
class WifiModeChangeScreen :
    public virtual StaticTitle<TEXT_WIFICHANGEMODE>,
    public ChangeValueDisplay<wifi_mode_t>,
    public virtual WifiModeAccessor
{
    using Base = ChangeValueDisplay<wifi_mode_t>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct WifiSleepAccessor : public virtual AccessorInterface<bool>
{
    bool getValue() const override { return WiFi.getSleep(); }
    void setValue(bool value) override
    {
        if (!WiFi.setSleep(value))
            Serial.println("Could not set WiFi sleep!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
class WifiSleepChangeScreen :
    public virtual StaticTitle<TEXT_WIFICHANGESLEEP>,
    public ChangeValueDisplay<bool>,
    public virtual WifiSleepAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct WifiTxPowerAccessor : public virtual AccessorInterface<wifi_power_t>
{
    wifi_power_t getValue() const override { return WiFi.getTxPower(); }
    void setValue(wifi_power_t value) override
    {
        if (!WiFi.setTxPower(value))
            Serial.println("Could not set WiFi tx power!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
class WifiTxPowerChangeScreen :
    public virtual StaticTitle<TEXT_WIFICHANGETXPOWER>,
    public ChangeValueDisplay<wifi_power_t>,
    public virtual WifiTxPowerAccessor
{
    using Base = ChangeValueDisplay<wifi_power_t>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class GenericWifiSettingsMenu final :
    public StaticTitle<TEXT_GENERICWIFISETTINGS>,
    public StaticMenuDisplay<
        LiveStatusMenuItem<WifiStatusBitsLiveStatus>,
        LiveStatusMenuItem<WifiChannelLiveStatus>,
        StaticSwitchScreenMenuItem<WifiModeChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGEMODE>,
        StaticSwitchScreenMenuItem<WifiSleepChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGESLEEP>,
        StaticSwitchScreenMenuItem<WifiTxPowerChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGETXPOWER>,
        BackMenuItem<Tscreen>
    >
{};
}
