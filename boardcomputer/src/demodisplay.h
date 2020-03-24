#pragma once

#include "display.h"
#include "utils.h"

namespace {
template<typename TnextScreen>
class DemoDisplay : public Display
{
public:
    void button(bool pressed) override final;
};

template<typename TnextScreen>
void DemoDisplay<TnextScreen>::button(bool pressed)
{
    if (!pressed)
        switchScreen<TnextScreen>();
}
}
