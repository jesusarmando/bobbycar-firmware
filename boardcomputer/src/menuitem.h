#pragma once

#include "globals.h"

namespace {
class MenuItem {
public:
    MenuItem(const char *text) : m_text{text} {}

    virtual void triggered() const = 0;
    virtual int draw(int y, bool selected) const;

private:
    const char *m_text;
};

int MenuItem::draw(int y, bool selected) const
{
    tft.setTextColor(selected ? TFT_ORANGE : TFT_WHITE);

    tft.drawString(m_text, 10, y, 4);

    if (selected)
        tft.drawRect(5, y-2, tft.width() - 5, 25, TFT_WHITE);

    return 25;
}
}
