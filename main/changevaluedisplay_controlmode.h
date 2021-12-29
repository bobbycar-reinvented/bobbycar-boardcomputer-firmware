#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menudisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>

// local includes
#include "bobbycar-common.h"

namespace espgui {

template<>
class ChangeValueDisplay<bobbycar::protocol::ControlMode> :
    public MenuDisplay,
    public virtual AccessorInterface<bobbycar::protocol::ControlMode>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
