#pragma once

#include "display.h"
#include "globals.h"
#include "utils.h"

namespace {
template<typename Tvalue, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay : public Display
{
public:
    ChangeValueDisplay(Tvalue &value);

    void start() override;
    void update() override final;
    void redraw() override final;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

private:
    void redrawMenu() const;

    Tvalue &m_value;
    Tvalue m_tempValue{};
    bool m_needsRedraw{};
    bool m_pressed{};
};

template<typename Tvalue, typename Tdisplay, const char *Ttext>
ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::ChangeValueDisplay(Tvalue &value) :
    m_value{value}
{
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::start()
{
    Display::start();

    tft.setRotation(0);

    m_tempValue = m_value;
    m_needsRedraw = true;
    m_pressed = false;
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::update()
{
    if (m_pressed)
    {
        m_value = m_tempValue;
        switchScreen<Tdisplay>();
    }
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::rotate(int offset)
{
    m_tempValue += offset;
    m_needsRedraw = true;
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

template<typename Tvalue, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<Tvalue, Tdisplay, Ttext>::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(Ttext, 5, 5, 4);

    tft.drawNumber(m_tempValue, 50, 50, 7);
}
}
