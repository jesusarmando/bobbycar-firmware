#pragma once

#include "display.h"
#include "globals.h"

namespace {
class DemoDisplay : public Display
{
public:
    DemoDisplay(Display &prevDisplay) :
        m_prevDisplay{prevDisplay}
    {
    }

    void button(bool pressed) override final;

private:
    Display &m_prevDisplay;
};

void DemoDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &m_prevDisplay;
}
}
