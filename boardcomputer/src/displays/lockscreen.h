#pragma once

#include "display.h"
#include "label.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"
#include "modes/lockscreenmode.h"

namespace {
template<typename Tscreen>
class Lockscreen : public Display
{
    static constexpr auto boxWidth = 35;
    static constexpr auto boxHeight = 50;
    static constexpr auto spacing = 20;

public:
    void start() override;
    void update() override {}
    void redraw() override;

    void button(bool pressed) override;
    void rotate(int offset) override;

private:
    template<int offset, uint32_t color>
    void drawRect(int index) const;

    Label<spacing, 100, boxWidth, boxHeight, 7> m_digit0;
    Label<spacing*2+boxWidth, 100, boxWidth, boxHeight, 7> m_digit1;
    Label<spacing*3+boxWidth*2, 100, boxWidth, boxHeight, 7> m_digit2;
    Label<spacing*4+boxWidth*3, 100, boxWidth, boxHeight, 7> m_digit3;

    std::array<int8_t, 4> m_numbers;

    uint8_t m_currentIndex{};

    bool m_pressed{};
    int m_rotated{};

    ModeBase *m_oldMode{};
    LockscreenMode m_mode;
};

template<typename Tscreen>
void Lockscreen<Tscreen>::start()
{
    m_numbers = {0,0,0,0};
    m_currentIndex = 0;
    m_pressed = false;
    m_rotated = 0;

    m_oldMode = currentMode;
    currentMode = &m_mode;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_LOCKVEHICLE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Enter code to unlock:", 0, 50, 4);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    for(int i = 0; i <= 3; i++)
    {
        drawRect<3, TFT_WHITE>(i);
        drawRect<4, TFT_WHITE>(i);
    }

    m_digit0.start();
    m_digit1.start();
    m_digit2.start();
    m_digit3.start();

    drawRect<1, TFT_YELLOW>(0);
    drawRect<2, TFT_YELLOW>(0);
    m_digit0.redraw(String(m_numbers[0]));
}

template<typename Tscreen>
void Lockscreen<Tscreen>::redraw()
{
    if (m_pressed)
    {
        drawRect<1, TFT_BLACK>(m_currentIndex);
        drawRect<2, TFT_BLACK>(m_currentIndex);

        if (++m_currentIndex>=4)
        {
            if (m_numbers == decltype(m_numbers){1,2,3,4})
            {
                if (currentMode == &m_mode)
                    currentMode = m_oldMode;
                switchScreen<Tscreen>();
                return;
            }

            m_numbers = {0,0,0,0};
            m_currentIndex = 0;
            m_digit1.redraw(String{});
            m_digit2.redraw(String{});
            m_digit3.redraw(String{});
        }

        switch (m_currentIndex)
        {
        case 0: m_digit0.redraw(String{m_numbers[0]}); break;
        case 1: m_digit1.redraw(String{m_numbers[1]}); break;
        case 2: m_digit2.redraw(String{m_numbers[2]}); break;
        case 3: m_digit3.redraw(String{m_numbers[3]}); break;
        }

        drawRect<1, TFT_YELLOW>(m_currentIndex);
        drawRect<2, TFT_YELLOW>(m_currentIndex);

        m_pressed = false;
    }

    if (m_rotated)
    {
        m_numbers[m_currentIndex] += m_rotated;

        if (m_numbers[m_currentIndex] < 0)
            m_numbers[m_currentIndex]+=10;
        else if (m_numbers[m_currentIndex] > 9)
            m_numbers[m_currentIndex]-=10;

        switch (m_currentIndex)
        {
        case 0: m_digit0.redraw(String(m_numbers[0])); break;
        case 1: m_digit1.redraw(String(m_numbers[1])); break;
        case 2: m_digit2.redraw(String(m_numbers[2])); break;
        case 3: m_digit3.redraw(String(m_numbers[3])); break;
        }

        m_rotated = 0;
    }
}

template<typename Tscreen>
void Lockscreen<Tscreen>::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

template<typename Tscreen>
void Lockscreen<Tscreen>::rotate(int offset)
{
    m_rotated += offset;
}

template<typename Tscreen> template<int offset, uint32_t color>
void Lockscreen<Tscreen>::drawRect(int index) const
{
    switch (index) {
    case 0:
        tft.drawRect(m_digit0.X-offset, m_digit0.Y-offset, m_digit0.WIDTH+(offset*2), m_digit0.HEIGHT+(offset*2), color);
        break;
    case 1:
        tft.drawRect(m_digit1.X-offset, m_digit1.Y-offset, m_digit1.WIDTH+(offset*2), m_digit1.HEIGHT+(offset*2), color);
        break;
    case 2:
        tft.drawRect(m_digit2.X-offset, m_digit2.Y-offset, m_digit2.WIDTH+(offset*2), m_digit2.HEIGHT+(offset*2), color);
        break;
    case 3:
        tft.drawRect(m_digit3.X-offset, m_digit3.Y-offset, m_digit3.WIDTH+(offset*2), m_digit3.HEIGHT+(offset*2), color);
        break;
    }
}
}
