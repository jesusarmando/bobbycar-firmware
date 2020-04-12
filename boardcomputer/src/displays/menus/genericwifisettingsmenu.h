#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "staticmenudisplay.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
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
class WifiModeChangeScreen :
    public virtual StaticText<TEXT_WIFICHANGEMODE>,
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
    public virtual StaticText<TEXT_WIFICHANGESLEEP>,
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
    public virtual StaticText<TEXT_WIFICHANGETXPOWER>,
    public ChangeValueDisplay<wifi_power_t>,
    public virtual WifiTxPowerAccessor
{
    using Base = ChangeValueDisplay<wifi_power_t>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

template<typename Tscreen>
class GenericWifiSettingsMenu :
    public StaticText<TEXT_GENERICWIFISETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, WifiStatusBitsText,                 DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiChannelText,                    DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEMODE>,    DefaultFont, DefaultColor,              SwitchScreenAction<WifiModeChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGESLEEP>,   DefaultFont, DefaultColor,              SwitchScreenAction<WifiSleepChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGETXPOWER>, DefaultFont, DefaultColor,              SwitchScreenAction<WifiTxPowerChangeScreen<GenericWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              DefaultFont, DefaultColor,              SwitchScreenAction<Tscreen>>
    >
{};
}
