#pragma once

#include "actioninterface.h"
#include "globals.h"

using namespace espgui;

namespace {
#ifdef FEATURE_BLUETOOTH
class BluetoothFlushAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        bluetoothSerial.flush();
    }
};
#endif
}
