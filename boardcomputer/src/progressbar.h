#pragma once

#include "globals.h"
#include "utils.h"

namespace {
template<int x, int y, int width, int height, int min, int max>
class ProgressBar
{
public:
    void start();
    void repaint(int value);

private:
    int m_lastValue{x+1};
};

template<int x, int y, int width, int height, int min, int max>
void ProgressBar<x, y, width, height, min, max>::start()
{
    tft.drawRect(x, y, width, height, TFT_WHITE);
}

template<int x, int y, int width, int height, int min, int max>
void ProgressBar<x, y, width, height, min, max>::repaint(int value)
{
    value = scaleBetween(value, min, max, x+1, x+width-1);

    if (value < m_lastValue)
        tft.fillRect(value, y+1, m_lastValue-value, height-2, TFT_BLACK);
    else if (value > m_lastValue)
        tft.fillRect(m_lastValue, y+1, value-m_lastValue, height-2, TFT_YELLOW);

    m_lastValue = value;
}

}
