#pragma once

#include <functional>

#include "display.h"
#include "menuitem.h"

namespace {
class MenuDisplay : public Display
{
public:
    void start() override;
    void redraw() override;
    void stop() override;
    int framerate() const override { return 60; }

    virtual const std::reference_wrapper<MenuItem> *begin() = 0;
    virtual const std::reference_wrapper<MenuItem> *end() = 0;
    virtual const std::reference_wrapper<const MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<const MenuItem> *end() const = 0;

    void redrawMenu() const;

private:
    bool m_needsRedraw;
};

void MenuDisplay::start()
{
    Serial.println("MenuDisplay::start()");
    tft.setRotation(0);
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

void MenuDisplay::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    int y = 25;
    for (auto iter = begin(); iter != end(); iter++)
        y += (*iter).get().draw(y, false);
}
}
