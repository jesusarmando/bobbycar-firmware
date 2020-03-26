#pragma once

#include <Arduino.h>

namespace {
using pin_t = int;

template<typename HANDLER, pin_t CLK, pin_t DT, pin_t SW>
class Rotary
{
public:
    static constexpr auto ClkPin = CLK;
    static constexpr auto DtPin = DT;
    static constexpr auto SwPin = SW;

    Rotary();

    void updateRotate();
    void updateSwitch();

private:
    int m_lastMillis{};

    bool m_lastClk;
    bool m_lastSw{};
};

template<typename HANDLER, pin_t CLK, pin_t DT, pin_t SW>
Rotary<HANDLER, CLK, DT, SW>::Rotary()
{
    m_lastMillis = millis();

    pinMode(ClkPin, INPUT_PULLUP);
    pinMode(DtPin, INPUT_PULLUP);
    pinMode(SwPin, INPUT_PULLUP);

    m_lastClk = digitalRead(ClkPin);
}

template<typename HANDLER, pin_t CLK, pin_t DT, pin_t SW>
void Rotary<HANDLER, CLK, DT, SW>::updateRotate()
{
    const auto now = millis();
    if (now - m_lastMillis < 1)
        return;
    m_lastMillis = now;

    const bool currentClk = digitalRead(ClkPin);
    if (currentClk != m_lastClk)
    {
        HANDLER::rotate(digitalRead(DtPin) != currentClk ? -1 : 1);
        m_lastClk = currentClk;
    }
}

template<typename HANDLER, pin_t CLK, pin_t DT, pin_t SW>
void Rotary<HANDLER, CLK, DT, SW>::updateSwitch()
{
    const auto now = millis();
    if (now - m_lastMillis < 1)
        return;
    m_lastMillis = now;

    const bool currentSw = digitalRead(SwPin);
    if (currentSw != m_lastSw)
    {
        HANDLER::button(!currentSw);
        m_lastSw = currentSw;
    }
}
}
