#pragma once

#include <WiFi.h>

#include "menuitems/menuitem.h"

namespace {
template<const char *Ttext>
class WifiReconnectMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void WifiReconnectMenuItem<Ttext>::triggered()
{
    if (!WiFi.reconnect())
    {
        Serial.println("Could not reconnect WiFi");
        // TODO: better error handling
    }
}
}
