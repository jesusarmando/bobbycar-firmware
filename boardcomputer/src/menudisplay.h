#pragma once

#include <functional>
#include <utility>

#include "display.h"
#include "globals.h"
#include "menuitem.h"

namespace {
class MenuDisplay : public Display
{
public:
    void start() override;
    void update() override final;
    void redraw() override final;

    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const char *title() const = 0;

    virtual const std::reference_wrapper<const MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<const MenuItem> *end() const = 0;

protected:
    const std::reference_wrapper<const MenuItem> *m_current {};
    bool m_needsRedraw{};
    bool m_pressed{};

private:
    void redrawMenu() const;
};

void MenuDisplay::start()
{
    Display::start();

    tft.setRotation(0);
    if (!m_current)
        m_current = begin();

    m_needsRedraw = true;
    m_pressed = false;
}

void MenuDisplay::update()
{
    if (m_pressed)
        m_current->get().triggered();
}

void MenuDisplay::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

void MenuDisplay::rotate(int offset)
{
    auto selected = m_current + offset;
    if (selected < begin())
        selected = begin();
    if (selected >= end())
        selected = end() - 1;
    m_current = selected;
    m_needsRedraw = true;
}

void MenuDisplay::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

void MenuDisplay::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(title(), 5, 5, 4);

    int y = 50;
    for (auto iter = begin(); iter != end(); iter++)
    {
        const auto selected = iter == m_current;

        tft.setTextColor(selected ? TFT_ORANGE : TFT_WHITE);

        tft.drawString((*iter).get().text(), 10, y, 4);

        if (selected)
            tft.drawRect(5, y-2, tft.width() - 5, 25, TFT_WHITE);

        y += 25;
    }
}
}
