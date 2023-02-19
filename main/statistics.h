#pragma once

// 3rdparty lib includes
#include "graphdisplay.h"
#include <espwifistack.h>

// local includes
#include "globals.h"
#include "bmsutils.h"
#include "utils.h"

namespace bobby::statistics {
using ContainerType = ring_buffer<float, 200>;
extern ContainerType raw_gas, raw_brems, gas, brems, avgSpeed, avgSpeedKmh, sumCurrent, frontVoltage, backVoltage, frontLeftCurrent, frontRightCurrent, backLeftCurrent, backRightCurrent,
#ifdef FEATURE_BMS
    bmsVoltage, bmsCurrent, bmsPower,
#endif
    rssi;

void pushStats();

class StatisticsAccessorInterface
{
public:
    virtual const statistics::ContainerType &getBuffer() const = 0;
};

template<const statistics::ContainerType &T>
class BufferAccessorImpl : public virtual StatisticsAccessorInterface
{
public:
    const statistics::ContainerType &getBuffer() const override { return T; }
};

using RawGasStatistics = BufferAccessorImpl<statistics::raw_gas>;
using RawBremsStatistics = BufferAccessorImpl<statistics::raw_brems>;
using GasStatistics = BufferAccessorImpl<statistics::gas>;
using BremsStatistics = BufferAccessorImpl<statistics::brems>;
using AvgSpeedStatistics = BufferAccessorImpl<statistics::avgSpeed>;
using AvgSpeedKmhStatistics = BufferAccessorImpl<statistics::avgSpeedKmh>;
using SumCurrentStatistics = BufferAccessorImpl<statistics::sumCurrent>;
using FrontVoltageStatistics = BufferAccessorImpl<statistics::frontVoltage>;
using BackVoltageStatistics = BufferAccessorImpl<statistics::backVoltage>;
#ifdef FEATURE_BMS
using BmsVoltageStatistics = BufferAccessorImpl<statistics::bmsVoltage>;
using BmsCurrentStatistics = BufferAccessorImpl<statistics::bmsCurrent>;
using BmsPowerStatistics = BufferAccessorImpl<statistics::bmsPower>;
#endif
using FrontLeftCurrentStatistics = BufferAccessorImpl<statistics::frontLeftCurrent>;
using FrontRightCurrentStatistics = BufferAccessorImpl<statistics::frontRightCurrent>;
using BackLeftCurrentStatistics = BufferAccessorImpl<statistics::backLeftCurrent>;
using BackRightCurrentStatistics = BufferAccessorImpl<statistics::backRightCurrent>;
using RssiStatistics = BufferAccessorImpl<statistics::rssi>;

} // namespace bobby::statistics
