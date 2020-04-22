#pragma once

#include "globals.h"
#include "ring-buffer.h"
#include "utils.h"

namespace {
namespace statistics {
using ContainerType = ring_buffer<float, 200>;
ContainerType gas, brems, avgSpeed, avgSpeedKmh, sumCurrent, frontVoltage, backVoltage;
}

void pushStats()
{
    statistics::gas.push_back(gas);
    statistics::brems.push_back(brems);
    statistics::avgSpeed.push_back(avgSpeed);
    statistics::avgSpeedKmh.push_back(avgSpeedKmh);
    statistics::sumCurrent.push_back(sumCurrent);
    if (front.feedbackValid)
        statistics::frontVoltage.push_back(fixBatVoltage(front.feedback.batVoltage));
    if (back.feedbackValid)
        statistics::backVoltage.push_back(fixBatVoltage(back.feedback.batVoltage));
}

class StatisticsInterface
{
public:
    virtual const statistics::ContainerType &getBuffer() const = 0;
};

template<const statistics::ContainerType &T>
class StatisticsInterfaceImpl : public virtual StatisticsInterface
{
public:
    const statistics::ContainerType &getBuffer() const override { return T; }
};

using GasStatistics = StatisticsInterfaceImpl<statistics::gas>;
using BremsStatistics = StatisticsInterfaceImpl<statistics::brems>;
using AvgSpeedStatistics = StatisticsInterfaceImpl<statistics::avgSpeed>;
using AvgSpeedKmhStatistics = StatisticsInterfaceImpl<statistics::avgSpeedKmh>;
using SumCurrentStatistics = StatisticsInterfaceImpl<statistics::sumCurrent>;
using FrontVoltageStatistics = StatisticsInterfaceImpl<statistics::frontVoltage>;
using BackVoltageStatistics = StatisticsInterfaceImpl<statistics::backVoltage>;
}
