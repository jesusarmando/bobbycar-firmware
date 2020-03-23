#pragma once

#include "display.h"
#include "globals.h"

namespace {
class ChangeNumberDisplay : public Display
{
public:
    ChangeNumberDisplay(const char *title, int &value, Display &prevDisplay);

    void start() override;
    void redraw() override;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const { return m_title; }

private:
    void redrawMenu() const;

    const char * const m_title;
    int &m_value;
    int m_tempValue{};
    Display &m_prevDisplay;
    bool m_needsRedraw{};
};

ChangeNumberDisplay::ChangeNumberDisplay(const char *title, int &value, Display &prevDisplay) :
    m_title{title},
    m_value{value},
    m_prevDisplay{prevDisplay}
{
}

void ChangeNumberDisplay::start()
{
    Display::start();

    tft.setRotation(0);

    m_tempValue = m_value;
    m_needsRedraw = true;
}

void ChangeNumberDisplay::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

void ChangeNumberDisplay::rotate(int offset)
{
    m_tempValue += offset;
    m_needsRedraw = true;
}

void ChangeNumberDisplay::button(bool pressed)
{
    m_value = m_tempValue;
    if (!pressed)
        currentDisplay = &m_prevDisplay;
}

void ChangeNumberDisplay::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title, 5, 5, 4);

    tft.drawNumber(m_tempValue, 50, 50, 7);
}
}
