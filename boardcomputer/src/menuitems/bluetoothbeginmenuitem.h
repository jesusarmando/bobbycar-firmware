#pragma once

#include "menuitem.h"
#include "titleinterface.h"
#include "globals.h"

namespace {
template<const char *Ttext>
class BluetoothBeginMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void BluetoothBeginMenuItem<Ttext>::triggered()
{
    bluetoothSerial.begin("bobbyquad");
}
}
