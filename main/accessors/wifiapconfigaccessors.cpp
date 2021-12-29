#include "wifiapconfigaccessors.h"

// local includes
#include "newsettings.h"

using namespace espgui;

bool WifiApEnabledAccessor::getValue() const { return configs.wifiApEnabled.value; }
void WifiApEnabledAccessor::setValue(bool value) { configs.write_config(configs.wifiApEnabled, value); }

//bool WifiApDisableWhenOnlineAccessor::getValue() const { return configs.wifiDisableApWhenOnline.value; }
//void WifiApDisableWhenOnlineAccessor::setValue(bool value) { configs.write_config(configs.wifiDisableApWhenOnline, value); }
