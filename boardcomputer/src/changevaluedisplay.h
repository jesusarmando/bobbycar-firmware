#pragma once

#include "display.h"
#include "globals.h"
#include "utils.h"

namespace {
template<typename Tvalue, typename TnextDisplay>
class ChangeValueDisplay : public Display
{
public:
    ChangeValueDisplay(const char *title, Tvalue &value);

    void start() override;
    void redraw() override;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    const char *title() const { return m_title; }

private:
    void redrawMenu() const;

    const char * const m_title;
    Tvalue &m_value;
    Tvalue m_tempValue{};
    Display &m_prevDisplay;
    bool m_needsRedraw{};
};

template<typename Tvalue, typename TnextDisplay>
ChangeValueDisplay<Tvalue, TnextDisplay>::ChangeValueDisplay(const char *title, Tvalue &value) :
    m_title{title},
    m_value{value}
{
}

template<typename Tvalue, typename TnextDisplay>
void ChangeValueDisplay<Tvalue, TnextDisplay>::start()
{
    Display::start();

    tft.setRotation(0);

    m_tempValue = m_value;
    m_needsRedraw = true;
}

template<typename Tvalue, typename TnextDisplay>
void ChangeValueDisplay<Tvalue, TnextDisplay>::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

template<typename Tvalue, typename TnextDisplay>
void ChangeValueDisplay<Tvalue, TnextDisplay>::rotate(int offset)
{
    m_tempValue += offset;
    m_needsRedraw = true;
}

template<typename Tvalue, typename TnextDisplay>
void ChangeValueDisplay<Tvalue, TnextDisplay>::button(bool pressed)
{
    if (!pressed)
    {
        m_value = m_tempValue;
        switchScreen<TnextDisplay>();
    }
}

template<typename Tvalue, typename TnextDisplay>
void ChangeValueDisplay<Tvalue, TnextDisplay>::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title, 5, 5, 4);

    tft.drawNumber(m_tempValue, 50, 50, 7);
}
}
