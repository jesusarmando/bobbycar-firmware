#pragma once

#include "actioninterface.h"

namespace {
class EndWifiScanAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        WiFi.scanDelete();
    }
};
}
