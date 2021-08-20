#pragma once

// local includes
#include "accessorinterface.h"
#include "globals.h"
#include "modes/tempomatmode.h"

using namespace espgui;

namespace {

struct AvgSpeedAccessor : public RefAccessor<float> { float &getRef() const override { return avgSpeed; } };
struct AvgSpeedKmhAccessor : public RefAccessor<float> { float &getRef() const override { return avgSpeedKmh; } };
struct SumCurrentAccessor : public RefAccessor<float> { float &getRef() const override { return sumCurrent; } };

struct TempomatModeCruiseMotTgtAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return modes::tempomatMode.nCruiseMotTgt; } };

} // namespace
