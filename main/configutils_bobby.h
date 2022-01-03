#pragma once
#include "sdkconfig.h"

// 3rdparty lib includes
#include <configutils_priv_enum.h>

// local includes
#include "ledstrip.h"
#include "handbremse.h"

IMPLEMENT_NVS_GET_SET_ENUM(OtaAnimationModes)
IMPLEMENT_NVS_GET_SET_ENUM(HandbremseMode)
