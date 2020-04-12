#pragma once

#include "menuitems/menuitem.h"
#include "titleinterface.h"
#include "texts.h"
#include "globals.h"

namespace {
class BluetoothFlushMenuItem final : public MenuItem, public StaticTitle<TEXT_BLUETOOTHFLUSH>
{
public:
    void triggered() override;
};

void BluetoothFlushMenuItem::triggered()
{
    bluetoothSerial.flush();
}
}
