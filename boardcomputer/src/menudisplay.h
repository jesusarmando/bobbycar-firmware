#pragma once

#include <functional>
#include <utility>

#include "display.h"
#include "menuitem.h"

namespace {
class MenuDisplay : public Display
{
public:
    void start() override;
    void redraw() override final;
    void stop() override;
    int framerate() const override { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const std::reference_wrapper<const MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<const MenuItem> *end() const = 0;

    void redrawMenu() const;

private:
    const std::reference_wrapper<const MenuItem> *m_current;
    bool m_needsRedraw;
};

void MenuDisplay::start()
{
    Serial.println("MenuDisplay::start()");
    tft.setRotation(0);
    m_current = begin();
    m_needsRedraw = true;
}

void MenuDisplay::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

void MenuDisplay::stop()
{
    Serial.println("MenuDisplay::stop()");
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
        m_current->get().triggered();
}

void MenuDisplay::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    int y = 25;
    for (auto iter = begin(); iter != end(); iter++)
        y += (*iter).get().draw(y, iter == m_current);
}
}
