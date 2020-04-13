#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/wifisoftapenableipv6action.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class WifiSettingsMenu;
}

namespace {
class WifiSoftApGetStationNumText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPgetStationNum: "} + WiFi.softAPgetStationNum(); }
};
class WifiSoftApIpText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPIP: "} + WiFi.softAPIP().toString(); }
};
class WifiSoftApBroadcastIpText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPBroadcastIP: "} + WiFi.softAPBroadcastIP().toString(); }
};
class WifiSoftApNetworkIdText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPNetworkID: "} + WiFi.softAPNetworkID().toString(); }
};
class WifiSoftApSubnetCidrText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPSubnetCIDR: "} + WiFi.softAPSubnetCIDR(); }
};
class WifiSoftApIpV6Text : public virtual TextInterface {
public:
    String text() const override { return String{"softAPIPv6: "} + WiFi.softAPIPv6().toString(); }
};
class WifiSoftApHostnameText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPgetHostname: "} + WiFi.softAPgetHostname(); }
};
class WifiSoftApMacAddressText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPmacAddress: "} + WiFi.softAPmacAddress(); }
};

class AccessPointWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_ACCESSPOINTWIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, WifiSoftApGetStationNumText,           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApIpText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApBroadcastIpText,             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApNetworkIdText,               StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApSubnetCidrText,              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPENABLEIPV6>, WifiSoftApEnableIpV6Action>,
        makeComponent<MenuItem, WifiSoftApIpV6Text,                    StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApHostnameText,                StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApMacAddressText,              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
