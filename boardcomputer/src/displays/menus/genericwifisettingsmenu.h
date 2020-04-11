#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "texts.h"

namespace {
struct WifiStatusBitsLiveStatus { static String getText() { return String{"statusBits: "} + WiFi.getStatusBits(); } };
struct WifiChannelLiveStatus { static String getText() { return String{"channel: "} + WiFi.channel(); } };

struct WifiModeAccessor
{
    static wifi_mode_t getValue() { return WiFi.getMode(); }
    static void setValue(wifi_mode_t value)
    {
        if (!WiFi.mode(value))
            Serial.println("Could not change WiFi mode!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
using WifiModeChangeScreen = ChangeValueDisplay<wifi_mode_t, WifiModeAccessor, Tscreen, TEXT_WIFICHANGEMODE>;

struct WifiSleepAccessor
{
    static bool getValue() { return WiFi.getSleep(); }
    static void setValue(bool value)
    {
        if (!WiFi.setSleep(value))
            Serial.println("Could not set WiFi sleep!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
using WifiSleepChangeScreen = ChangeValueDisplay<bool, WifiSleepAccessor, Tscreen, TEXT_WIFICHANGESLEEP>;

struct WifiTxPowerAccessor
{
    static wifi_power_t getValue() { return WiFi.getTxPower(); }
    static void setValue(wifi_power_t value)
    {
        if (!WiFi.setTxPower(value))
            Serial.println("Could not set WiFi tx power!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
using WifiTxPowerChangeScreen = ChangeValueDisplay<wifi_power_t, WifiTxPowerAccessor, Tscreen, TEXT_WIFICHANGETXPOWER>;

template<typename Tscreen>
class GenericWifiSettingsMenu final :
    public StaticTitle<TEXT_GENERICWIFISETTINGS>,
    public StaticMenuDisplay<
        LiveStatusMenuItem<WifiStatusBitsLiveStatus>,
        LiveStatusMenuItem<WifiChannelLiveStatus>,
        StaticSwitchScreenMenuItem<WifiModeChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGEMODE>,
        StaticSwitchScreenMenuItem<WifiSleepChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGESLEEP>,
        StaticSwitchScreenMenuItem<WifiTxPowerChangeScreen<GenericWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGETXPOWER>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
