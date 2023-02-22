#pragma once

// 3rdparty lib includes
#include <actioninterface.h>

namespace bobby {

class SwitchAppPartitionAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override;
};

} // namespace bobby
