#pragma once

#include "globals.h"
#include "utils.h"

namespace {
template<int x, int y, int width, int height, int min, int max, uint32_t color=TFT_YELLOW>
class ProgressBar
{
public:
    void start();
    void redraw(int value);

private:
    int m_lastValue{x+1};
};

template<int x, int y, int width, int height, int min, int max, uint32_t color>
void ProgressBar<x, y, width, height, min, max, color>::start()
{
    tft.drawRect(x, y, width, height, TFT_WHITE);
}

template<int x, int y, int width, int height, int min, int max, uint32_t color>
void ProgressBar<x, y, width, height, min, max, color>::redraw(int value)
{
    value = scaleBetween(value, min, max, x+1, x+width-1);

    if (value < m_lastValue)
        tft.fillRect(value, y+1, m_lastValue-value, height-2, TFT_BLACK);
    else if (value > m_lastValue)
        tft.fillRect(m_lastValue, y+1, value-m_lastValue, height-2, color);

    m_lastValue = value;
}

}
