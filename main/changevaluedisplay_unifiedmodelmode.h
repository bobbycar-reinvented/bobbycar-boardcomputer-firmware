#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menudisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>

// local includes
#include "unifiedmodelmode.h"

namespace espgui {

template<>
class ChangeValueDisplay<UnifiedModelMode> :
    public MenuDisplay,
    public virtual AccessorInterface<UnifiedModelMode>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
