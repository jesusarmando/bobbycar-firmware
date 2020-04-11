#pragma once

#include <WString.h>

#include "globals.h"

namespace {
class LabelInterface
{
public:
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual void start() = 0;
    virtual bool redraw(const String &str, bool forceRedraw = false) = 0;
    virtual void clear() = 0;
};

template<int x, int y, int width, int height, int font=4>
class Label : public LabelInterface
{
public:
    static constexpr auto X = x;
    static constexpr auto Y = y;
    static constexpr auto WIDTH = width;
    static constexpr auto HEIGHT = height;

    int getX() const { return x; };
    int getY() const { return y; };
    int getWidth() const { return width; };
    int getHeight() const { return height; };

    void start() override;
    bool redraw(const String &str, bool forceRedraw = false) override;
    void clear() override;

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
bool Label<x, y, width, height, font>::redraw(const String &str, bool forceRedraw)
{
    if (m_lastStr == str && !forceRedraw)
        return false;

    const auto renderedX = tft.drawString(str, x, y, font) + x;

    if (renderedX < m_lastX)
        tft.fillRect(renderedX, y, m_lastX - renderedX, height, TFT_BLACK);

    m_lastX = renderedX;
    m_lastStr = str;

    return true;
}

template<int x, int y, int width, int height, int font>
void Label<x, y, width, height, font>::clear()
{
    m_lastStr.clear();

    if (x < m_lastX)
    {
        tft.fillRect(x, y, m_lastX - x, height, TFT_BLACK);
        m_lastX = x;
    }
}
}
