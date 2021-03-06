#pragma once

#include <WiFi.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/wifireconnectaction.h"
#include "actions/wifidisconnectaction.h"
#include "actions/toggleboolaction.h"
#include "actions/wifienableipv6action.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class WifiSettingsMenu;
}

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

class StationWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_STATIONWIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_WIFIRECONNECT>,           WifiReconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIDISCONNECT>,          WifiDisconnectAction>,
        makeComponent<MenuItem, WifiIsConnectedText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTOCONNECT>,   ToggleBoolAction, CheckboxIcon, WifiAutoConnectAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTORECONNECT>, ToggleBoolAction, CheckboxIcon, WifiAutoReconnectAccessor>,
        makeComponent<MenuItem, WifiLocalIpText,                          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiMacAddressText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetMaskText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiGatewayIpText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiDnsIpText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBroadcastIpText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiNetworkIdText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetCIDRText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIENABLEIPV6>,          WifiEnableIpV6Action>,
        makeComponent<MenuItem, WifiLocalIpV6Text,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiHostnameText,                         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiStatusText,                           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSsidText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiPskText,                              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBssidText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiRssiText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
