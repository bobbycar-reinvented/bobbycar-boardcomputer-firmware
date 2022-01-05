#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menudisplay.h>
#include <confirminterface.h>
#include <errorhandlerinterface.h>

// local includes
#include "bobbyquickactions.h"

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
