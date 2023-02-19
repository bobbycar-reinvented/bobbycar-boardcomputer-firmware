#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>
#include <menudisplay.h>

// local includes
#include "enums.h"

namespace espgui {

template<>
class ChangeValueDisplay<BobbyQuickActions> :
    public MenuDisplay,
    public virtual AccessorInterface<BobbyQuickActions>,
    public virtual ConfirmInterface,
    public virtual ErrorHandlerInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

} // namespace espgui
