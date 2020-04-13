#pragma once

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "utils.h"
#include "texts.h"

namespace {
class DemosMenu;
}

namespace {
class MatrixDisplay : public DemoDisplay, public SwitchScreenAction<DemosMenu>
{
    using Base = DemoDisplay;

public:
    void start() override;
    void redraw() override;
    void stop() override;

private:
    int scroll_slow(int lines, int wait);

    static constexpr auto TEXT_HEIGHT = 8;     // Height of text to be printed and scrolled
    static constexpr auto BOT_FIXED_AREA = 0;  // Number of lines in bottom fixed area (lines counted from bottom of screen)
    static constexpr auto TOP_FIXED_AREA = 0;  // Number of lines in top fixed area (lines counted from top of screen)

    uint16_t yStart = TOP_FIXED_AREA;
    uint16_t yArea = 320 - TOP_FIXED_AREA - BOT_FIXED_AREA;
    uint16_t yDraw = 320 - BOT_FIXED_AREA - TEXT_HEIGHT;
    byte     pos[42];
    uint16_t xPos = 0;
};

void MatrixDisplay::start()
{
    Base::start();

    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    setupScrollArea(TOP_FIXED_AREA, BOT_FIXED_AREA);

    // First fill the screen with random streaks of characters
    for (int j = 0; j < 600; j += TEXT_HEIGHT)
    {
        for (int i = 0; i < 40; i++)
        {
            if (pos[i] > 20)
                pos[i] -= 3; // Rapid fade initially brightness values

            if (pos[i] > 0)
                pos[i] -= 1; // Slow fade later

            if ((random(20) == 1) && (j<400))
                pos[i] = 63; // ~1 in 20 probability of a new character

            tft.setTextColor(pos[i] << 5, TFT_BLACK); // Set the green character brightness

            if (pos[i] == 63)
                tft.setTextColor(TFT_WHITE, TFT_BLACK); // Draw white character

            xPos += tft.drawChar(random(32, 128), xPos, yDraw, 1); // Draw the character
        }
        yDraw = scroll_slow(TEXT_HEIGHT, 14); // Scroll, 14ms per pixel line
        xPos = 0;
    }
}

void MatrixDisplay::redraw()
{
    yDraw = scroll_slow(320,5);
}

void MatrixDisplay::stop()
{
    Base::stop();
    scrollAddress(0);
    tft.setRotation(0);
}

int MatrixDisplay::scroll_slow(int lines, int wait)
{
    int yTemp = yStart;

    for (int i = 0; i < lines; i++) {
        yStart++;
        if (yStart == 320 - BOT_FIXED_AREA)
            yStart = TOP_FIXED_AREA;
        scrollAddress(yStart);
        delay(wait);
    }

    return yTemp;
}
}
