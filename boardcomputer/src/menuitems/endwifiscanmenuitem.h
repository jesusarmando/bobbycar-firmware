#pragma once

#include "menuitems/backmenuitem.h"

namespace {
template<typename Tscreen>
class EndWifiScanMenuItem : public BackMenuItem<Tscreen>
{
    using Base = BackMenuItem<Tscreen>;

public:
    using Base::Base;

    void triggered() override;
};

template<typename Tscreen>
void EndWifiScanMenuItem<Tscreen>::triggered()
{
    WiFi.scanDelete();
    Base::triggered();
}
}
