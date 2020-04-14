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
#include "settingssaver.h"

namespace {
using pin_t = int;

int16_t raw_gas, raw_brems;
float gas, brems;

Settings settings;
SettingsSaver settingsSaver;

Controller front{Serial1, settings.hardware.enableFrontLeft, settings.hardware.enableFrontRight, settings.hardware.invertFrontLeft, settings.hardware.invertFrontRight};
Controller back{Serial2, settings.hardware.enableBackLeft, settings.hardware.enableBackRight, settings.hardware.invertBackLeft, settings.hardware.invertBackRight};

struct {
    unsigned long lastTime = millis();
    int current{0};
    int last{0};
} performance;

BluetoothSerial bluetoothSerial;

TFT_eSPI tft = TFT_eSPI();

ModeInterface *currentMode{};

Display *currentDisplay{};

int rotated{};
bool requestFullRedraw{};
bool buttonLongPressed{};
bool buttonPressed{};

class InputDispatcher
{
public:
    static void rotate(int offset)
    {
        rotated += offset;
    }

    static void button(bool pressed)
    {
        static unsigned long pressBegin = 0;

        const auto now = millis();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 1000)
                buttonPressed = true;
            else if (duration < 3000)
                buttonLongPressed = true;
            else
                requestFullRedraw = true;

            pressBegin = 0;
        }
    }
};
}
