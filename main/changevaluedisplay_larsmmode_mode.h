#pragma once

// 3rdparty lib inclues
#include <changevaluedisplay.h>
#include <menudisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>

// local includes
#include "modes/larsmmode.h"

namespace espgui {

template<>
class ChangeValueDisplay<LarsmModeMode> :
    public MenuDisplay,
    public virtual AccessorInterface<LarsmModeMode>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
