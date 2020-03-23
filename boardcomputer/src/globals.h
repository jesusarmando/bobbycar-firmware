#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "modebase.h"
#include "display.h"
#include "settings.h"

namespace {
uint16_t raw_gas, raw_brems;
float gas, brems;
uint16_t gasMin, gasMax, bremsMin, bremsMax;

bool power_toggle{false};
bool led_toggle{false};

unsigned long lastUpdate = millis();
unsigned long lastRedraw = millis();
unsigned long lastDebug = millis();

wl_status_t last_status;
IPAddress last_ip;

struct {
    int iMotMax = defaultIMotMax;           // [A] Maximum motor current limit
    int iDcMax = defaultIDcMax;             // [A] Maximum DC Link current limit (This is the final current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A)
    int nMotMax = defaultNMotMax;           // [rpm] Maximum motor speed limit
    int fieldWeakMax = defaultFieldWeakMax; // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed.
    int phaseAdvMax = defaultPhaseAdvMax;   // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed.
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
}
