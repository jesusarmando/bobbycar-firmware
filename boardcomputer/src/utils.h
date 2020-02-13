#pragma once

#include <algorithm>

namespace {
template<typename T>
T scaleBetween(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x < std::min(in_min, in_max))
        x = std::min(in_min, in_max);
    else if (x > std::max(in_min, in_max))
        x = std::max(in_min, in_max);

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
};
}
