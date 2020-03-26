#pragma once

#include "display.h"
#include "utils.h"

namespace {
template<typename Tscreen>
class DemoDisplay : public Display
{
public:
    void start() override;
    void update() override;

    void button(bool pressed) override;

private:
    bool m_pressed{};
};

template<typename Tscreen>
void DemoDisplay<Tscreen>::start()
{
    m_pressed = false;
}

template<typename Tscreen>
void DemoDisplay<Tscreen>::update()
{
    if (m_pressed)
        switchScreen<Tscreen>();
}

template<typename Tscreen>
void DemoDisplay<Tscreen>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}
}
