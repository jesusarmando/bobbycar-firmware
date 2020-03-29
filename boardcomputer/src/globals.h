#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "display.h"
#include "modebase.h"
#include "settings.h"

namespace {
using pin_t = int;

uint16_t raw_gas, raw_brems;
float gas, brems;
int16_t gasMin, gasMax, bremsMin, bremsMax;

struct {
    int16_t iMotMax = defaultIMotMax;           // [A] Maximum motor current limit
    int16_t iDcMax = defaultIDcMax;             // [A] Maximum DC Link current limit (This is the final current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A)
    int16_t nMotMax = defaultNMotMax;           // [rpm] Maximum motor speed limit
    int16_t fieldWeakMax = defaultFieldWeakMax; // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed.
    int16_t phaseAdvMax = defaultPhaseAdvMax;   // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed.
} settings;

std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};
Controller &front = controllers[0], &back = controllers[1];

struct {
    unsigned long lastTime = millis();
    int current{0};
    int last{0};
} performance;

BluetoothSerial bluetoothSerial;

TFT_eSPI tft = TFT_eSPI();

ModeBase *currentMode{};

Display *currentDisplay{};

class InputDispatcher {
public:
    static void rotate(int offset) { if (currentDisplay) currentDisplay->rotate(offset); }
    static void button(bool pressed) { if (currentDisplay) currentDisplay->button(pressed); }
};

void applyDefaultSettings()
{
    gasMin = defaultGasMin;
    gasMax = defaultGasMax;
    bremsMin = defaultBremsMin;
    bremsMax = defaultBremsMax;

    front.command.left.enable = defaultEnableFrontLeft;
    front.command.right.enable = defaultEnableFrontRight;
    back.command.left.enable = defaultEnableBackLeft;
    back.command.right.enable = defaultEnableBackRight;

    front.invertLeft = defaultInvertFrontLeft;
    front.invertRight = defaultInvertFrontRight;
    back.invertLeft = defaultInvertBackLeft;
    back.invertRight = defaultInvertBackRight;

    settings.iMotMax = defaultIMotMax;
    settings.iDcMax = defaultIDcMax;
    settings.nMotMax = defaultNMotMax;
    settings.fieldWeakMax = defaultFieldWeakMax;
    settings.phaseAdvMax = defaultPhaseAdvMax;

    for (auto &controller : controllers)
        controller.command.buzzer = {};
}
}
