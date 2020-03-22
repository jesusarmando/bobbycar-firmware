#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "modebase.h"
#include "display.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

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

std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};
struct {
    Controller &controller;

    struct {
        bool invert, enable;
    } left, right;
} front{controllers[0]}, back{controllers[1]};

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
