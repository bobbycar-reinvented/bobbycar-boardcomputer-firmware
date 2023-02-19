#pragma once

// 3rdparty lib includes
#include <actioninterface.h>
#include <screenmanager.h>

// local includes
#include "enums.h"

void switchToDefaultStatusDisplay();

class PushDefaultStatusDisplay : public virtual espgui::ActionInterface
{
public:
    void triggered() override;
};
