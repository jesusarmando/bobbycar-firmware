#pragma once

#include <cstdint>

#include "display.h"

namespace {
class PingPongDisplay : public Display
{
public:
    PingPongDisplay();

    void start() override;
    void update() override;
    void stop() override;
    int framerate() const override { return 60; }

    void midline();
    void lpaddle();
    void rpaddle();
    void calc_target_y();
    void ball();

    int16_t h = 240;
    int16_t w = 320;

    int dly = 5;

    int16_t paddle_h = 30;
    int16_t paddle_w = 4;

    int16_t lpaddle_x = 0;
    int16_t rpaddle_x = w - paddle_w;

    int16_t lpaddle_y = 0;
    int16_t rpaddle_y = h - paddle_h;

    int16_t lpaddle_d = 1;
    int16_t rpaddle_d = -1;

    int16_t lpaddle_ball_t = w - w / 4;
    int16_t rpaddle_ball_t = w / 4;

    int16_t target_y = 0;

    int16_t ball_x = 2;
    int16_t ball_y = 2;
    int16_t oldball_x = 2;
    int16_t oldball_y = 2;

    int16_t ball_dx = 1;
    int16_t ball_dy = 1;

    int16_t ball_w = 6;
    int16_t ball_h = 6;

    int16_t dashline_h = 4;
    int16_t dashline_w = 2;
    int16_t dashline_n = h / dashline_h;
    int16_t dashline_x = w / 2 - 1;
    int16_t dashline_y = dashline_h / 2;

    int16_t lscore = 12;
    int16_t rscore = 4;

    static const constexpr auto BLACK = 0x0000;
    static const constexpr auto WHITE = 0xFFFF;
    static const constexpr auto GREY = 0x5AEB;
};
}
