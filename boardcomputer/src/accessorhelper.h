#pragma once

namespace {
template<typename Taccessor>
struct AccessorHelper
{
    static auto getValue() { return Taccessor::getRef(); }

    template<typename T>
    static void setValue(const T &value) { Taccessor::getRef() = value; }
};
}
