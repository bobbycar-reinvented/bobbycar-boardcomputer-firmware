#pragma once

// local includes
#include "accessorinterface.h"
#include "globals.h"
#include "modes/defaultmode.h"

namespace {

struct AvgSpeedAccessor : public RefAccessor<float> { float &getRef() const override { return avgSpeed; } };
struct AvgSpeedKmhAccessor : public RefAccessor<float> { float &getRef() const override { return avgSpeedKmh; } };
struct SumCurrentAccessor : public RefAccessor<float> { float &getRef() const override { return sumCurrent; } };

struct DefaultModeCruiseCtrlEnaAccessor : public RefAccessor<bool> { bool &getRef() const override { return modes::defaultMode.cruiseCtrlEna; } };
struct DefaultModenCruiseMotTgtAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::defaultMode.nCruiseMotTgt; } };

} // namespace
