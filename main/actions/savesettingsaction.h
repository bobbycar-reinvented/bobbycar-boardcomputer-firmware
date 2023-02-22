#pragma once

#include "actioninterface.h"
#include "utils.h"

using namespace espgui;

namespace bobby {

class SaveSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { saveProfileSettings(); }
};

} // namespace bobby
