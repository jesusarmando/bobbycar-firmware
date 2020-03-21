#pragma once

#include "globals.h"

namespace {
class MenuItem {
public:
    MenuItem(const char *text) : m_text{text} {}

    virtual void triggered() = 0;
    virtual int draw(int y, bool selected) const;

private:
    const char *m_text;
};

int MenuItem::draw(int y, bool selected) const
{
    tft.drawString(m_text, 10, y, 4);
    return 25;
}
}
