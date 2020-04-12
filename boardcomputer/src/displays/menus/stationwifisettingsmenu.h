#pragma once

#include <WiFi.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/wifireconnectaction.h"
#include "actions/wifidisconnectaction.h"
#include "actions/wifienableipv6action.h"
#include "icons/back.h"
#include "texts.h"

namespace {
struct WifiIsConnectedText : public virtual TextInterface {
public:
    String text() const override { return String{"isConnected: "} + (WiFi.isConnected() ? "true" : "false"); }
};

struct WifiAutoConnectAccessor : public virtual AccessorInterface<bool>
{
    bool getValue() const override { return WiFi.getAutoConnect(); }
    void setValue(bool value) override
    {
        if (!WiFi.setAutoConnect(value))
            Serial.println("Could not set WiFi autoConnect!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
class WifiAutoConnectChangeScreen :
    public virtual StaticText<TEXT_WIFICHANGEAUTOCONNECT>,
    public ChangeValueDisplay<bool>,
    public virtual WifiAutoConnectAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct WifiAutoReconnectAccessor : public virtual AccessorInterface<bool>
{
    bool getValue() const override { return WiFi.getAutoReconnect(); }
    void setValue(bool value) override
    {
        if (!WiFi.setAutoReconnect(value))
            Serial.println("Could not set WiFi autoReconnect!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
class WifiAutoReconnectChangeScreen :
    public StaticText<TEXT_WIFICHANGEAUTORECONNECT>,
    public ChangeValueDisplay<bool>,
    public virtual WifiAutoReconnectAccessor
{
    using Base = ChangeValueDisplay<bool>;

public:
    void triggered() override { Base::triggered(); switchScreen<Tscreen>(); }
};

struct WifiLocalIpText : public virtual TextInterface {
public:
    String text() const override { return String{"localIP: "} + WiFi.localIP().toString(); }
};
struct WifiMacAddressText : public virtual TextInterface {
public:
    String text() const override { return String{"macAddress: "} + WiFi.macAddress(); }
};
struct WifiSubnetMaskText : public virtual TextInterface {
public:
    String text() const override { return String{"subnetMask: "} + WiFi.subnetMask().toString(); }
};
struct WifiGatewayIpText : public virtual TextInterface {
public:
    String text() const override { return String{"gatewayIP: "} + WiFi.gatewayIP().toString(); }
};
struct WifiDnsIpText : public virtual TextInterface {
public:
    String text() const override { return String{"dnsIP: "} + WiFi.dnsIP().toString(); }
};
struct WifiBroadcastIpText : public virtual TextInterface {
public:
    String text() const override { return String{"broadcastIP: "} + WiFi.broadcastIP().toString(); }
};
struct WifiNetworkIdText : public virtual TextInterface {
public:
    String text() const override { return String{"networkID: "} + WiFi.networkID().toString(); }
};
struct WifiSubnetCIDRText : public virtual TextInterface {
public:
    String text() const override { return String{"subnetCIDR: "} + WiFi.subnetCIDR(); }
};
struct WifiLocalIpV6Text : public virtual TextInterface {
public:
    String text() const override { return String{"localIPv6: "} + WiFi.localIPv6().toString(); }
};
struct WifiHostnameText : public virtual TextInterface {
public:
    String text() const override { return String{"hostname: "} + WiFi.getHostname(); }
};
struct WifiStatusText : public virtual TextInterface {
public:
    String text() const override { return String{"status: "} + toString(WiFi.status()); }
};
struct WifiSsidText : public virtual TextInterface {
public:
    String text() const override { return String{"SSID: "} + WiFi.SSID(); }
};
struct WifiPskText : public virtual TextInterface {
public:
    String text() const override { return String{"psk: "} + WiFi.psk(); }
};
struct WifiBssidText : public virtual TextInterface {
public:
    String text() const override { return String{"BSSID: "} + WiFi.BSSIDstr(); }
};
struct WifiRssiText : public virtual TextInterface {
public:
    String text() const override { return String{"RSSI: "} + WiFi.RSSI(); }
};

template<typename Tscreen>
class StationWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_STATIONWIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_WIFIRECONNECT>,           DefaultFont,   DefaultColor,  WifiReconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIDISCONNECT>,          DefaultFont,   DefaultColor,  WifiDisconnectAction>,
        makeComponent<MenuItem, WifiIsConnectedText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTOCONNECT>,   DefaultFont,   DefaultColor,  SwitchScreenAction<WifiAutoConnectChangeScreen<StationWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTORECONNECT>, DefaultFont,   DefaultColor,  SwitchScreenAction<WifiAutoReconnectChangeScreen<StationWifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, WifiLocalIpText,                          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiMacAddressText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetMaskText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiGatewayIpText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiDnsIpText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBroadcastIpText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiNetworkIdText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetCIDRText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIENABLEIPV6>,          DefaultFont,   DefaultColor,  WifiEnableIpV6Action>,
        makeComponent<MenuItem, WifiLocalIpV6Text,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiHostnameText,                         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiStatusText,                           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSsidText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiPskText,                              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBssidText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiRssiText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    DefaultFont,   DefaultColor,  SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
