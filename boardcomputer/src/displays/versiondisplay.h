#pragma once

#include "demodisplay.h"
#include "globals.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class VersionDisplay : public DemoDisplay<Tscreen>
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

    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_VERSION, 5, 5);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Boardcomputer: 1.0", 0, 50);
    tft.drawString("Front controller:", 0, 75);
    tft.drawString("Back controller:", 0, 100);
    tft.drawString("Made by: feedc0de", 0, 125);
    tft.drawString("Press any button", 0, 200);
    tft.drawString("to go back", 0, 225);
}
}
