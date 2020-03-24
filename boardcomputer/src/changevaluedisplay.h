#pragma once

#include "display.h"
#include "globals.h"

namespace {
template<typename T>
class ChangeValueDisplay : public Display
{
public:
    ChangeValueDisplay(const char *title, T &value, Display &prevDisplay);

    void start() override;
    void redraw() override;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const { return m_title; }

private:
    void redrawMenu() const;

    const char * const m_title;
    T &m_value;
    T m_tempValue{};
    Display &m_prevDisplay;
    bool m_needsRedraw{};
};

template<typename T>
ChangeValueDisplay<T>::ChangeValueDisplay(const char *title, T &value, Display &prevDisplay) :
    m_title{title},
    m_value{value},
    m_prevDisplay{prevDisplay}
{
}

template<typename T>
void ChangeValueDisplay<T>::start()
{
    Display::start();

    tft.setRotation(0);

    m_tempValue = m_value;
    m_needsRedraw = true;
}

template<typename T>
void ChangeValueDisplay<T>::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

template<typename T>
void ChangeValueDisplay<T>::rotate(int offset)
{
    m_tempValue += offset;
    m_needsRedraw = true;
}

template<typename T>
void ChangeValueDisplay<T>::button(bool pressed)
{
    if (!pressed)
    {
        m_value = m_tempValue;
        currentDisplay = &m_prevDisplay;
    }
}

template<typename T>
void ChangeValueDisplay<T>::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title, 5, 5, 4);

    tft.drawNumber(m_tempValue, 50, 50, 7);
}
}
