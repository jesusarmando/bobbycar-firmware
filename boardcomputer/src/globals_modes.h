#pragma once

#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
struct {
    DefaultMode defaultMode;
    ManualMode manualMode;
    BluetoothMode bluetoothMode;
} modes;
}
