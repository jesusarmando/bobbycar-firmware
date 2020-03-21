#pragma once

#include <cstdint>

#include "display.h"
#include "globals.h"

namespace {
class StarfieldDisplay final : public Display
{
public:
    StarfieldDisplay();

    void start() override;
    void update() override;
    void stop() override;
    int framerate() const override { return 30; }

    const char *displayName() const override { return "Starfield"; }

    // Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
    uint8_t rng();

    static constexpr auto NSTARS = 1024;

    uint8_t sx[NSTARS] = {};
    uint8_t sy[NSTARS] = {};
    uint8_t sz[NSTARS] = {};

    uint8_t za, zb, zc, zx;
};

namespace displays {
StarfieldDisplay starfield;
}

StarfieldDisplay::StarfieldDisplay() :
    za(random(256)),
    zb(random(256)),
    zc(random(256)),
    zx(random(256))
{
}

void StarfieldDisplay::start()
{
    Serial.println("StarfieldDisplay::start()");
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);

    // fastSetup() must be used immediately before fastPixel() to prepare screen
    // It must be called after any other graphics drawing function call if fastPixel()
    // is to be called again
    //tft.fastSetup(); // Prepare plot window range for fast pixel plotting
}

void StarfieldDisplay::update()
{
    uint8_t spawnDepthVariation = 255;

    for(int i = 0; i < NSTARS; ++i)
    {
      if (sz[i] <= 1)
      {
        sx[i] = 160 - 120 + rng();
        sy[i] = rng();
        sz[i] = spawnDepthVariation--;
      }
      else
      {
        int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;

        // This is a faster pixel drawing function for occassions where many single pixels must be drawn
        tft.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

        sz[i] -= 2;
        if (sz[i] > 1)
        {
          int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
          int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;

          if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240)
          {
            uint8_t r, g, b;
            r = g = b = 255 - sz[i];
            tft.drawPixel(screen_x, screen_y, tft.color565(r,g,b));
          }
          else
            sz[i] = 0; // Out of screen, die.
        }
      }
    }
}

void StarfieldDisplay::stop()
{
    Serial.println("StarfieldDisplay::stop()");
}

uint8_t StarfieldDisplay::rng()
{
    zx++;
    za = (za^zc^zx);
    zb = (zb+za);
    zc = (zc+(zb>>1)^za);
    return zc;
}
}