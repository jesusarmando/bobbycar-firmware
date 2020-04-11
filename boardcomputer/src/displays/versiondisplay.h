#pragma once

#include "demodisplay.h"
#include "globals.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class VersionDisplay final : public DemoDisplay<Tscreen>
{
    using Base = DemoDisplay<Tscreen>;

public:
    void start() override;
    void redraw() override {}
};

template<typename Tscreen>
void VersionDisplay<Tscreen>::start()
{
    Base::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_VERSION, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Boardcomputer: 1.0", 0, 50, 4);
    tft.drawString("Front controller:", 0, 75, 4);
    tft.drawString("Back controller:", 0, 100, 4);
    tft.drawString("Made by: feedc0de", 0, 125, 4);
    tft.drawString("Press any button", 0, 200, 4);
    tft.drawString("to go back", 0, 225, 4);
}
}
