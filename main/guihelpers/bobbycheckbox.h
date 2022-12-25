#pragma once

// 3rdparty lib includes
#include "../../components/esp-gui-lib/src/actions/toggleboolaction.h"
#include "../../components/esp-gui-lib/src/checkboxicon.h"

// local includes
#include "bobbyerrorhandler.h"

namespace bobby {

class BobbyCheckbox :
    public virtual espgui::ToggleBoolAction,
    public virtual espgui::CheckboxIcon,
    public virtual BobbyErrorHandler
{
};

} // namespace bobby
