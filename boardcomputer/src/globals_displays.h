#pragma once

#include "displays/statusdisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"

namespace {
struct {
    StatusDisplay status;
    StarfieldDisplay starfield;
    PingPongDisplay pingPong;
    SpiroDisplay spiro;
} display;
}
