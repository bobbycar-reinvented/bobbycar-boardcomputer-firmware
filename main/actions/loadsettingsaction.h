#pragma once

#include "actioninterface.h"
#include "utils.h"

using namespace espgui;

namespace bobby {

class LoadSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { loadProfileSettings(); }
};

} // namespace bobby
