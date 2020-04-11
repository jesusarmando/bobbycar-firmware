#pragma once

#include "menuitems/staticswitchscreenmenuitem.h"

namespace {
template<typename Tscreen, const char *Ttext>
class EndWifiScanMenuItem : public StaticSwitchScreenMenuItem<Tscreen, Ttext>
{
    using Base = StaticSwitchScreenMenuItem<Tscreen, Ttext>;

public:
    using Base::Base;

    void triggered() override;
};

template<typename Tscreen, const char *Ttext>
void EndWifiScanMenuItem<Tscreen, Ttext>::triggered()
{
    WiFi.scanDelete();
    Base::triggered();
}
}
