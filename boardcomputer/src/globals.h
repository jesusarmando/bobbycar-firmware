#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "display.h"
#include "modeinterface.h"
#include "settings.h"

namespace {
using pin_t = int;

int16_t raw_gas, raw_brems;
float gas, brems;
int16_t gasMin, gasMax, bremsMin, bremsMax;

struct {
    int16_t iMotMax;      // [A] Maximum motor current limit
    int16_t iDcMax;       // [A] Maximum DC Link current limit (This is the current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A)
    int16_t nMotMax;      // [rpm] Maximum motor speed limit
    int16_t fieldWeakMax; // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed.
    int16_t phaseAdvMax;  // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed.
} settings;

Controller front{Serial1}, back{Serial2};

struct {
    unsigned long lastTime = millis();
    int current{0};
    int last{0};
} performance;

BluetoothSerial bluetoothSerial;

TFT_eSPI tft = TFT_eSPI();

ModeInterface *currentMode{};

Display *currentDisplay{};

class InputDispatcher {
public:
    static void rotate(int offset) { if (currentDisplay) currentDisplay->rotate(offset); }
    static void button(bool pressed) { if (currentDisplay) currentDisplay->button(pressed); }
};
}
