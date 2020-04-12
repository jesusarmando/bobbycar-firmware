#pragma once

#include "menuitems/menuitem.h"
#include "titleinterface.h"
#include "texts.h"
#include "globals.h"

namespace {
class BluetoothEndMenuItem final : public MenuItem, public StaticTitle<TEXT_BLUETOOTHEND>
{
public:
    void triggered() override;
};

void BluetoothEndMenuItem::triggered()
{
    bluetoothSerial.end();
}
}
