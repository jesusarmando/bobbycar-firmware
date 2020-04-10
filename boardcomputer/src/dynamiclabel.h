#pragma once

#include <WString.h>

#include "globals.h"

namespace {
template<int width, int height, int font=4>
class DynamicLabel
{
public:
    static constexpr auto WIDTH = width;
    static constexpr auto HEIGHT = height;

    void start();
    void repaint(int x, int y, const String &str);

private:
    int m_lastX;
    int m_lastY;
    int m_lastWidth;
    String m_lastStr;
};

template<int width, int height, int font>
void DynamicLabel<width, height, font>::start()
{
    m_lastX = -1;
    m_lastY = -1;
    m_lastWidth = -1;
    m_lastStr.clear();
}

template<int width, int height, int font>
void DynamicLabel<width, height, font>::repaint(int x, int y, const String &str)
{
    if (m_lastStr == str && m_lastX == x && m_lastY == y)
        return;

    if (m_lastX != x || m_lastY != y)
        m_lastWidth = -1;

    const auto renderedX = tft.drawString(str, x, y, font) + x;

    if (m_lastWidth != -1 && renderedX < m_lastWidth)
        tft.fillRect(renderedX, y, m_lastWidth - renderedX, height, TFT_BLACK);

    //tft.drawRect(x, y, width, height, TFT_WHITE);

    m_lastX = x;
    m_lastY = y;
    m_lastWidth = renderedX;
    m_lastStr = str;
}
}
