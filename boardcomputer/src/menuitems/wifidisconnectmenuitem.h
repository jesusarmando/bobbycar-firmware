#pragma once

#include <WiFi.h>

#include "menuitem.h"

namespace {
template<const char *Ttext>
class WifiDisconnectMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void WifiDisconnectMenuItem<Ttext>::triggered()
{
    if (!WiFi.disconnect())
    {
        Serial.println("Could not disconnect WiFi");
        // TODO: better error handling
    }
}
}
