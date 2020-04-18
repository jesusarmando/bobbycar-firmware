#pragma once

#include "actioninterface.h"
#include "display.h"

namespace {
class DemoDisplay : public Display, public virtual ActionInterface
{
public:
    void button() override;
};

void DemoDisplay::button()
{
    triggered();
}
}
