#include "bluetoothbeginaction.h"

// local includes
#include "globals.h"
#include "newsettings.h"

#ifdef FEATURE_BLUETOOTH
void BluetoothBeginAction::triggered()
{
    if (!bluetoothSerial.begin(configs.bluetoothName.value.c_str()))
    {
        //Serial.println("Could not begin bluetooth");
        // TODO: better error handling
    }
}
#endif
