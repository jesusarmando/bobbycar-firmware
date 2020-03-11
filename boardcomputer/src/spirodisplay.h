#pragma once

#include <cstdint>

#include <Arduino.h>

#include "display.h"

namespace {
class SpiroDisplay : public Display
{
public:
    SpiroDisplay();

    void start() override;
    void update() override;
    void stop() override;
    int framerate() const override { return 100; }

private:
    void render();

    constexpr static auto DEG2RAD = 0.0174532925;

    static unsigned int rainbow(int value)
    {
      // Value is expected to be in range 0-127
      // The value is converted to a spectrum colour from 0 = blue through to red = blue
      //int value = random (128);
      byte red = 0; // Red is the top 5 bits of a 16 bit colour value
      byte green = 0;// Green is the middle 6 bits
      byte blue = 0; // Blue is the bottom 5 bits

      byte quadrant = value / 32;

      if (quadrant == 0) {
        blue = 31;
        green = 2 * (value % 32);
        red = 0;
      }
      if (quadrant == 1) {
        blue = 31 - (value % 32);
        green = 63;
        red = 0;
      }
      if (quadrant == 2) {
        blue = 0;
        green = 63;
        red = value % 32;
      }
      if (quadrant == 3) {
        blue = 0;
        green = 63 - 2 * (value % 32);
        red = 31;
      }
      return (red << 11) + (green << 5) + blue;
    }

    float sx = 0, sy = 0;
    uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

    long i{0};
    int n, r, colour;
};
}
