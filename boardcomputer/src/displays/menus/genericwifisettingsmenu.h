#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
struct WifiStatusBitsText : public virtual TextInterface {
public:
    String text() const override { return String{"statusBits: "} + WiFi.getStatusBits(); }
};
struct WifiChannelText : public virtual TextInterface {
public:
    String text() const override { return String{"channel: "} + WiFi.channel(); }
};

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
using WifiModeChangeScreen = makeComponent<ChangeValueDisplay<wifi_mode_t>, StaticText<TEXT_WIFICHANGEMODE>, WifiModeAccessor, SwitchScreenAction<Tscreen>>;

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
using WifiSleepChangeScreen = makeComponent<ChangeValueDisplay<bool>, StaticText<TEXT_WIFICHANGESLEEP>, WifiSleepAccessor, SwitchScreenAction<Tscreen>>;

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
using WifiTxPowerChangeScreen = makeComponent<ChangeValueDisplay<wifi_power_t>, StaticText<TEXT_WIFICHANGETXPOWER>, WifiTxPowerAccessor, SwitchScreenAction<Tscreen>>;

template<typename Tscreen>
class GenericWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_GENERICWIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, WifiStatusBitsText,                 DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiChannelText,                    DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEMODE>,    SwitchScreenAction<WifiModeChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGESLEEP>,   SwitchScreenAction<WifiSleepChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGETXPOWER>, SwitchScreenAction<WifiTxPowerChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
