#pragma once

#include "display.h"
#include "globals.h"

namespace {
class ChangeBoolDisplay : public Display
{
public:
    ChangeBoolDisplay(const char *title, bool &value, Display &prevDisplay);

    void start() override;
    void redraw() override;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const { return m_title; }

private:
    void redrawMenu() const;

    const char * const m_title;
    bool &m_value;
    bool m_tempValue{};
    Display &m_prevDisplay;
    bool m_needsRedraw{};
};

ChangeBoolDisplay::ChangeBoolDisplay(const char *title, bool &value, Display &prevDisplay) :
    m_title{title},
    m_value{value},
    m_prevDisplay{prevDisplay}
{
}

void ChangeBoolDisplay::start()
{
    Display::start();

    tft.setRotation(0);

    m_tempValue = m_value;
    m_needsRedraw = true;
}

void ChangeBoolDisplay::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

void ChangeBoolDisplay::rotate(int offset)
{
    if (offset > 0)
        m_tempValue = true;
    else if (offset < 0)
        m_tempValue = false;

    m_needsRedraw = true;
}

void ChangeBoolDisplay::button(bool pressed)
{
    if (!pressed)
    {
        m_value = m_tempValue;
        currentDisplay = &m_prevDisplay;
    }
}

void ChangeBoolDisplay::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title, 5, 5, 4);

    tft.drawNumber(m_tempValue, 50, 50, 7);
}
}
