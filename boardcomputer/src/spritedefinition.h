#pragma once

#include <cstdint>

namespace {
struct SpriteDefinition
{
    const uint16_t width;
    const uint16_t height;
    const unsigned short *buffer;
};
}
