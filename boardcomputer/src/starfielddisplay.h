#pragma once

#include <cstdint>

#include "display.h"

namespace {
class StarfieldDisplay : public Display
{
public:
    StarfieldDisplay();

    void start() override;
    void update() override;
    void stop() override;
    int framerate() const override { return 30; }

    // Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
    uint8_t rng()
    {
        zx++;
        za = (za^zc^zx);
        zb = (zb+za);
        zc = (zc+(zb>>1)^za);
        return zc;
    }

    static constexpr auto NSTARS = 1024;

    uint8_t sx[NSTARS] = {};
    uint8_t sy[NSTARS] = {};
    uint8_t sz[NSTARS] = {};

    uint8_t za, zb, zc, zx;
};
}
