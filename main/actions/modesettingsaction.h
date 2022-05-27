#pragma once

#include "actioninterface.h"

using namespace espgui;

class ModeSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override;
};
