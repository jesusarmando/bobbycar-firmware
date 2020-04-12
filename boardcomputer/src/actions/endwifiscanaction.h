#pragma once

#include "actioninterface.h"

namespace {
class EndWifiScanMenuItem : public virtual ActionInterface
{
public:
    void triggered() override
    {
        WiFi.scanDelete();
    }
};
}
