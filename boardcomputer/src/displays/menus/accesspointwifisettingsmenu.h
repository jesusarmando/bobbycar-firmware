#pragma once

#include "staticmenudisplay.h"
#include "menuitems/smalllivestatusmenuitem.h"
#include "menuitems/wifisoftapenableipv6menuitem.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
struct WifiSoftApGetStationNumLiveStatus { static String getText() { return String{"softAPgetStationNum: "} + WiFi.softAPgetStationNum(); } };
struct WifiSoftApIpLiveStatus { static String getText() { return String{"softAPIP: "} + WiFi.softAPIP().toString(); } };
struct WifiSoftApBroadcastIpLiveStatus { static String getText() { return String{"softAPBroadcastIP: "} + WiFi.softAPBroadcastIP().toString(); } };
struct WifiSoftApNetworkIdLiveStatus { static String getText() { return String{"softAPNetworkID: "} + WiFi.softAPNetworkID().toString(); } };
struct WifiSoftApSubnetCidrLiveStatus { static String getText() { return String{"softAPSubnetCIDR: "} + WiFi.softAPSubnetCIDR(); } };
struct WifiSoftApIpV6LiveStatus { static String getText() { return String{"softAPIPv6: "} + WiFi.softAPIPv6().toString(); } };
struct WifiSoftApHostnameLiveStatus { static String getText() { return String{"softAPgetHostname: "} + WiFi.softAPgetHostname(); } };
struct WifiSoftApMacAddressLiveStatus { static String getText() { return String{"softAPmacAddress: "} + WiFi.softAPmacAddress(); } };

template<typename Tscreen>
class AccessPointWifiSettingsMenu final :
    public StaticTitle<TEXT_ACCESSPOINTWIFISETTINGS>,
    public StaticMenuDisplay<
        SmallLiveStatusMenuItem<WifiSoftApGetStationNumLiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApBroadcastIpLiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApNetworkIdLiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApSubnetCidrLiveStatus>,
        WifiSoftApEnableIpV6MenuItem<TEXT_WIFISOFTAPENABLEIPV6>,
        SmallLiveStatusMenuItem<WifiSoftApIpV6LiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApHostnameLiveStatus>,
        SmallLiveStatusMenuItem<WifiSoftApMacAddressLiveStatus>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
