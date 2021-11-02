#pragma once

// 3rdparty lib includes
#include "actioninterface.h"

using namespace espgui;

class RebootAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override;
};
