#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menudisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>

// local includes
#include "handbremse.h"

namespace espgui {

template<>
class ChangeValueDisplay<HandbremseMode> :
    public MenuDisplay,
    public virtual AccessorInterface<HandbremseMode>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
