#pragma once

#include <WiFi.h>

#include "staticmenudisplay.h"
#include "menuitems/wifireconnectmenuitem.h"
#include "menuitems/wifidisconnectmenuitem.h"
#include "menuitems/smalllivestatusmenuitem.h"
#include "menuitems/wifienableipv6menuitem.h"
#include "changevaluedisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "utils.h"
#include "texts.h"

namespace {
struct WifiIsConnectedLiveStatus { static String getText() { return String{"isConnected: "} + (WiFi.isConnected() ? "true" : "false"); } };

struct WifiAutoConnectAccessor
{
    static bool getValue() { return WiFi.getAutoConnect(); }
    static void setValue(bool value)
    {
        if (!WiFi.setAutoConnect(value))
            Serial.println("Could not set WiFi autoConnect!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
using WifiAutoConnectChangeScreen = ChangeValueDisplay<bool, WifiAutoConnectAccessor, Tscreen, TEXT_WIFICHANGEAUTOCONNECT>;

struct WifiAutoReconnectAccessor
{
    static bool getValue() { return WiFi.getAutoReconnect(); }
    static void setValue(bool value)
    {
        if (!WiFi.setAutoReconnect(value))
            Serial.println("Could not set WiFi autoReconnect!");
        // TODO: better error handling
    }
};
template<typename Tscreen>
using WifiAutoReconnectChangeScreen = ChangeValueDisplay<bool, WifiAutoReconnectAccessor, Tscreen, TEXT_WIFICHANGEAUTORECONNECT>;

struct WifiLocalIpLiveStatus { static String getText() { return String{"localIP: "} + WiFi.localIP().toString(); } };
struct WifiMacAddressLiveStatus { static String getText() { return String{"macAddress: "} + WiFi.macAddress(); } };
struct WifiSubnetMaskLiveStatus { static String getText() { return String{"subnetMask: "} + WiFi.subnetMask().toString(); } };
struct WifiGatewayIpLiveStatus { static String getText() { return String{"gatewayIP: "} + WiFi.gatewayIP().toString(); } };
struct WifiDnsIpLiveStatus { static String getText() { return String{"dnsIP: "} + WiFi.dnsIP().toString(); } };
struct WifiBroadcastIpLiveStatus { static String getText() { return String{"broadcastIP: "} + WiFi.broadcastIP().toString(); } };
struct WifiNetworkIdLiveStatus { static String getText() { return String{"networkID: "} + WiFi.networkID().toString(); } };
struct WifiSubnetCIDRLiveStatus { static String getText() { return String{"subnetCIDR: "} + WiFi.subnetCIDR(); } };
struct WifiLocalIpV6LiveStatus { static String getText() { return String{"localIPv6: "} + WiFi.localIPv6().toString(); } };
struct WifiHostnameLiveStatus { static String getText() { return String{"hostname: "} + WiFi.getHostname(); } };
struct WifiStatusLiveStatus { static String getText() { return String{"status: "} + toString(WiFi.status()); } };
struct WifiSsidLiveStatus { static String getText() { return String{"SSID: "} + WiFi.SSID(); } };
struct WifiPskLiveStatus { static String getText() { return String{"psk: "} + WiFi.psk(); } };
struct WifiBssidLiveStatus { static String getText() { return String{"BSSID: "} + WiFi.BSSIDstr(); } };
struct WifiRssiLiveStatus { static String getText() { return String{"RSSI: "} + WiFi.RSSI(); } };

template<typename Tscreen>
class StationWifiSettingsMenu final :
    public StaticTitle<TEXT_STATIONWIFISETTINGS>,
    public StaticMenuDisplay<
        WifiReconnectMenuItem<TEXT_WIFIRECONNECT>,
        WifiDisconnectMenuItem<TEXT_WIFIDISCONNECT>,
        SmallLiveStatusMenuItem<WifiIsConnectedLiveStatus>,
        StaticSwitchScreenMenuItem<WifiAutoConnectChangeScreen<StationWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGEAUTOCONNECT>,
        StaticSwitchScreenMenuItem<WifiAutoReconnectChangeScreen<StationWifiSettingsMenu<Tscreen>>, TEXT_WIFICHANGEAUTORECONNECT>,
        SmallLiveStatusMenuItem<WifiLocalIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiMacAddressLiveStatus>,
        SmallLiveStatusMenuItem<WifiSubnetMaskLiveStatus>,
        SmallLiveStatusMenuItem<WifiGatewayIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiDnsIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiBroadcastIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiNetworkIdLiveStatus>,
        SmallLiveStatusMenuItem<WifiSubnetCIDRLiveStatus>,
        WifiEnableIpV6MenuItem<TEXT_WIFIENABLEIPV6>,
        SmallLiveStatusMenuItem<WifiLocalIpV6LiveStatus>,
        SmallLiveStatusMenuItem<WifiHostnameLiveStatus>,
        SmallLiveStatusMenuItem<WifiStatusLiveStatus>,
        SmallLiveStatusMenuItem<WifiSsidLiveStatus>,
        SmallLiveStatusMenuItem<WifiPskLiveStatus>,
        SmallLiveStatusMenuItem<WifiBssidLiveStatus>,
        SmallLiveStatusMenuItem<WifiRssiLiveStatus>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
