#pragma once

#include "actioninterface.h"
#include "settingsutils.h"

using namespace espgui;

namespace bobby {

template<uint8_t index>
class SwitchProfileAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        settingsutils::switchProfile(index);
    }
};

} // namespace bobby
