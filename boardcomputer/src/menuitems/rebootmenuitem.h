#pragma once

#include <Esp.h>

#include "menuitem.h"
#include "globals.h"
#include "texts.h"

namespace {
template<const char *Ttext>
class RebootMenuItem final : public MenuItem<Ttext>
{
public:
    void triggered() const override;
};

template<const char *Ttext>
void RebootMenuItem<Ttext>::triggered() const
{
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_REBOOT, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Rebooting now...", 0, 50, 4);

    ESP.restart();
}
}
