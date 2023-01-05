#pragma once

// 3rdparty lib includes
#include <actioninterface.h>
#include <screenmanager.h>

// local includes
#include "bobbytypesafeenum.h"

#define DefaultStatusDisplayValues(x) \
    x(Default) \
    x(Meters) \
    x(Battery) \
    x(BetterStatus)
DECLARE_BOBBYTYPESAFE_ENUM(DefaultStatusDisplay, : uint8_t, DefaultStatusDisplayValues)

void switchToDefaultStatusDisplay();

class PushDefaultStatusDisplay : public virtual espgui::ActionInterface
{
public:
    void triggered() override;
};
