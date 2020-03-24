#pragma once

#include "display.h"
#include "utils.h"

namespace {
template<typename TnextScreen>
class DemoDisplay : public Display
{
public:
    void start() override;
    void update() override final;

    void button(bool pressed) override final;

private:
    bool m_pressed{};
};

template<typename TnextScreen>
void DemoDisplay<TnextScreen>::start()
{
    m_pressed = false;
}

template<typename TnextScreen>
void DemoDisplay<TnextScreen>::update()
{
    if (m_pressed)
        switchScreen<TnextScreen>();
}

template<typename TnextScreen>
void DemoDisplay<TnextScreen>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}
}
