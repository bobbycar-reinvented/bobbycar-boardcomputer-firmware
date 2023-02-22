#include "switchapppartitionaction.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "guihelpers/bobbyerrorhandler.h"
#include "ota.h"
#include "screens/rebootscreen.h"

namespace bobby {

void SwitchAppPartitionAction::triggered()
{
    if (auto result = ota::switchAppPartition(); !result)
    {
        BobbyErrorHandler{}.errorOccurred(std::move(result).error());
        return;
    }

    espgui::switchScreen<RebootScreen>();
}

} // namespace bobby
