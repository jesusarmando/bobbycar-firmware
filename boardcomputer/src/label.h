#pragma once

#include <WString.h>

#include "globals.h"

namespace {
class Label
{
public:
    Label(int x, int y, int width, int height) : m_x{x}, m_y{y}, m_width{width}, m_height{height} {}

    int x() const { return m_x; };
    int y() const { return m_y; };
    int width() const { return m_width; };
    int height() const { return m_height; };

    void start();
    bool redraw(const String &str, bool forceRedraw = false);
    void clear();

private:
    const int m_x;
    const int m_y;
    const int m_width;
    const int m_height;

    int m_lastX;
    String m_lastStr;
    int m_lastFont;
    int m_lastColor;
};

void Label::start()
{
    m_lastX = m_x;
    m_lastStr.clear();
    m_lastFont = -1;
    m_lastColor = -1;
}

bool Label::redraw(const String &str, bool forceRedraw)
{
    if (m_lastStr == str &&
        m_lastFont == tft.textfont &&
        m_lastColor == tft.textcolor &&
        !forceRedraw)
        return false;

    const auto renderedX = tft.drawString(str, m_x, m_y) + m_x;

    if (renderedX < m_lastX)
        tft.fillRect(renderedX, m_y, m_lastX - renderedX, m_height, tft.textbgcolor);

    if (m_lastFont != -1 && m_lastFont != tft.textfont)
    {
        const auto newHeight = tft.fontHeight(tft.textfont);
        const auto oldHeight = tft.fontHeight(m_lastFont);

        if (newHeight < oldHeight)
            tft.fillRect(m_x, m_y + newHeight, renderedX - m_x, oldHeight - newHeight, tft.textbgcolor);
    }

    m_lastX = renderedX;
    m_lastStr = str;
    m_lastFont = tft.textfont;
    m_lastColor = tft.textcolor;

    return true;
}

void Label::clear()
{
    m_lastStr.clear();

    if (m_x < m_lastX)
    {
        tft.fillRect(m_x, m_y, m_lastX - m_x, m_height, TFT_BLACK);
        m_lastX = m_x;
    }
}
}
