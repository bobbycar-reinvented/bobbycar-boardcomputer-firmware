#pragma once
#include "sdkconfig.h"

// 3rdparty lib includes
#include <configutils_priv_enum.h>

// local includes
#include "battery.h"
#include "bobbyquickactions.h"
#include "cloud.h"
#include "handbremse.h"
#include "ledstrip.h"

IMPLEMENT_NVS_GET_SET_ENUM(BatteryCellType)
IMPLEMENT_NVS_GET_SET_ENUM(BobbyQuickActions)
IMPLEMENT_NVS_GET_SET_ENUM(CloudMode)
IMPLEMENT_NVS_GET_SET_ENUM(HandbremseMode)
IMPLEMENT_NVS_GET_SET_ENUM(LedstripAnimation)
IMPLEMENT_NVS_GET_SET_ENUM(OtaAnimationModes)
