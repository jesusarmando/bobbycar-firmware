#pragma once

#include "actioninterface.h"
#include "display.h"

namespace {
class DemoDisplay : public Display, public virtual ActionInterface
{
public:
    void start() override;
    void update() override;

    void button(bool pressed) override;

private:
    bool m_pressed;
};

void DemoDisplay::start()
{
    m_pressed = false;
}

void DemoDisplay::update()
{
    if (m_pressed)
        triggered();
}

void DemoDisplay::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}
}
