#pragma once

#include <Arduino.h>

#include "display.h"
#include "utils.h"
#include "globals.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class PoweroffDisplay final : public Display
{
public:
    void start() override;
    void update() override;

private:
    unsigned int m_startTime{};
};

template<typename Tscreen>
void PoweroffDisplay<Tscreen>::start()
{
    m_startTime = millis();

    for (auto &controller : controllers)
        controller.command.poweroff = true;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_POWEROFF, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Trying to turn off", 15, 50, 4);
    tft.drawString("both controllers", 25, 75, 4);
    tft.drawString("Please stand still...", 20, 125, 4);
}

template<typename Tscreen>
void PoweroffDisplay<Tscreen>::update()
{
    if (millis() - m_startTime >= 1000)
    {
        for (auto &controller : controllers)
            controller.command.poweroff = false;

        switchScreen<Tscreen>();
    }
}
}
