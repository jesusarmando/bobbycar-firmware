#pragma once

#include "menuitem.h"
#include "titleinterface.h"
#include "globals.h"

namespace {
template<const char *Ttext>
class BluetoothBeginMasterMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void BluetoothBeginMasterMenuItem<Ttext>::triggered()
{
    bluetoothSerial.begin("bobbyquad", true);
}
}
