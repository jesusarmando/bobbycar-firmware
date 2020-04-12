#pragma once

#include <WiFi.h>

#include "menuitems/menuitem.h"

namespace {
template<const char *Ttext>
class WifiEnableIpV6MenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void WifiEnableIpV6MenuItem<Ttext>::triggered()
{
    if (!WiFi.enableIpV6())
    {
        Serial.println("Could not enableIpV6 WiFi");
        // TODO: better error handling
    }
}
}
