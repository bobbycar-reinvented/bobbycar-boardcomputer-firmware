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
class ChangeValueDisplay<bobbycar::protocol::ControlType> :
    public MenuDisplay,
    public virtual AccessorInterface<bobbycar::protocol::ControlType>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
