#pragma once

// 3rdparty lib includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"

// local includes
#include "unifiedmodelmode.h"

namespace espgui {
template<>
class ChangeValueDisplay<UnifiedModelMode> :
    public MenuDisplay,
    public virtual AccessorInterface<UnifiedModelMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};
} // namespace espgui
