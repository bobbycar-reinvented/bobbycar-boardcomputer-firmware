#include "bluetooth_bobby.h"

// compilation will be broken as there is no config parameter

// local includes
#ifdef FEATURE_BLUETOOTH
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#ifdef FEATURE_BMS
#include "actions/bluetoothconnectbmsaction.h"
#endif
#include "bluetoothmode.h"
#endif

#ifdef FEATURE_BLUETOOTH
void bluetooth_init()
{
    if (configs.bluetooth.autoBluetoothMode.value == BluetoothMode::Master)
    {
        bootLabel.redraw("bluetooth begin master");
        BluetoothBeginMasterAction{}.triggered();
#ifdef FEATURE_BMS
        if (configs.autoConnectBms.value)
        {
            bootLabel.redraw("connect BMS");
            BluetoothConnectBmsAction{}.triggered();
        }
#endif
    }
    else if (configs.bluetooth.autoBluetoothMode.value == BluetoothMode::Slave)
    {
        bootLabel.redraw("bluetooth begin");
        BluetoothBeginAction{}.triggered();
    }
}

void bluetooth_update()
{
}
#endif
