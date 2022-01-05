#include "sdkconfig.h"

#include "configutils_bobby.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::toString;
#include <configwrapper_priv.h>

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(OtaAnimationModes)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(HandbremseMode)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(LedstripAnimation)
INSTANTIATE_CONFIGWRAPPER_TEMPLATES(BobbyQuickActions)
