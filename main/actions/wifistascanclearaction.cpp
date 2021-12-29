#include "wifistascanclearaction.h"

// 3rdparty lib includes
#include <espwifistack.h>

void WifiStaScanClearAction::triggered()
{
    wifi_stack::delete_scan_result();
}
