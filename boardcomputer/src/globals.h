#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "modebase.h"
#include "settings.h"

namespace {
uint16_t raw_gas, raw_brems;
float gas, brems;
int16_t gasMin, gasMax, bremsMin, bremsMax;

bool power_toggle{false};

unsigned long lastUpdate = millis();
unsigned long lastRedraw = millis();

wl_status_t last_status;
IPAddress last_ip;

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
}
