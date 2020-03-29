#pragma once

#include <WString.h>

#include "globals.h"

namespace {
template<int x, int y, int width, int height>
class Label
{
public:
    void start(const String &);

    void repaint(long val);
    void repaint(float val);
    void repaint(const String &val);
    void repaint(const char *val);

private:
    int m_lastX{x};

    void refillBlack(int renderedX);
};

template<int x, int y, int width, int height>
void Label<x, y, width, height>::repaint(long val)
{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    refillBlack(tft.drawNumber(val, x, y, 4));
}

template<int x, int y, int width, int height>
void Label<x, y, width, height>::repaint(float val)
{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    refillBlack(tft.drawFloat(val, 2, x, y, 4));
}

template<int x, int y, int width, int height>
void Label<x, y, width, height>::repaint(const String &val)
{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    refillBlack(tft.drawString(val, x, y, 4));
}

template<int x, int y, int width, int height>
void Label<x, y, width, height>::repaint(const char *val)
{
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    refillBlack(tft.drawString(val, x, y, 4));
}

template<int x, int y, int width, int height>
void Label<x, y, width, height>::refillBlack(int renderedX)
{
    renderedX += x;

    if (renderedX < m_lastX)
        tft.fillRect(renderedX, y, m_lastX - renderedX, height, TFT_BLACK);

    m_lastX = renderedX;
}
}
