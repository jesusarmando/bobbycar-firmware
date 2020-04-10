#pragma once

#include "titleinterface.h"
#include "dynamiclabel.h"

namespace {
class MenuItemInterface : public virtual TitleInterface
{
public:
    void start();
    void redraw(int &y, bool selected);
    void stop() {}

    virtual void triggered() const = 0;

private:
    DynamicLabel<10, 220> m_label;
    bool m_lastSelected;
};

template<const char *T>
class MenuItem : public MenuItemInterface, public TitleImpl<T>
{};

void MenuItemInterface::start()
{
    m_label.start();
    m_lastSelected = false;
}

void MenuItemInterface::redraw(int &y, bool selected)
{
    m_label.repaint(10, y, title());

    if (selected != m_lastSelected)
    {
        tft.drawRect(5, y-2, tft.width() - 5, 25, selected ? TFT_WHITE : TFT_BLACK);
        m_lastSelected = selected;
    }

    y += 25;
}
}
