#pragma once

#include <WString.h>

#include "globals.h"

namespace {
template<int x, int y, int width, int height, int font=4>
class Label
{
public:
    void start();
    void repaint(const String &str);

private:
    int m_lastX{x};
    String m_lastStr;
};

template<int x, int y, int width, int height, int font>
void Label<x, y, width, height, font>::start()
{
    m_lastX = x;
    m_lastStr.clear();
}

template<int x, int y, int width, int height, int font>
void Label<x, y, width, height, font>::repaint(const String &str)
{
    if (m_lastStr == str)
        return;

    const auto renderedX = tft.drawString(str, x, y, font) + x;

    if (renderedX < m_lastX)
        tft.fillRect(renderedX, y, m_lastX - renderedX, height, TFT_BLACK);

    //tft.drawRect(x, y, width, height, TFT_WHITE);

    m_lastX = renderedX;
    m_lastStr = str;
}
}
