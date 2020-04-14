#include <Arduino.h>

#include <HardwareSerial.h>
#include <WiFi.h>

#include "../../common.h"

#include "globals.h"
#include "webserver.h"
#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "screens.h"
#include "rotary.h"
#include "serialhandler.h"
#include "presets.h"

namespace {
ModeInterface *lastMode{};
unsigned long lastModeUpdate{};
unsigned long lastDisplayRedraw{};
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    initScreen();
    initRotary();

    settings = presets::defaultSettings;

    if (settingsSaver.init())
        settingsSaver.load(settings);

    updateSwapFrontBack();

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbyquad", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    front.serial.get().begin(38400, SERIAL_8N1, PINS_RX1, PINS_TX1);
    back.serial.get().begin(38400, SERIAL_8N1, PINS_RX2, PINS_TX2);

    raw_gas = 0;
    raw_brems = 0;
    gas = 0;
    brems = 0;

    for (Controller &controller : controllers())
        controller.command.buzzer = {};

    currentMode = &modes::defaultMode;

    initWebserver();
    switchScreen<StatusDisplay>();
}

void loop()
{
    const auto now = millis();

    if (!lastModeUpdate)
        lastModeUpdate = now;
    else if (now - lastModeUpdate >= 1000/50)
    {
        const auto sampleMultipleTimes = [](int pin){
            analogRead(pin);
            double sum{};
            for (int i = 0; i < settings.hardware.poti.sampleCount; i++)
                sum += analogRead(pin);
            return sum/settings.hardware.poti.sampleCount;
        };

        raw_gas = sampleMultipleTimes(PINS_GAS);
        gas = scaleBetween<float>(raw_gas, settings.hardware.poti.gasMin, settings.hardware.poti.gasMax, 0., 1000.);

        raw_brems = sampleMultipleTimes(PINS_BREMS);
        brems = scaleBetween<float>(raw_brems, settings.hardware.poti.bremsMin, settings.hardware.poti.bremsMax, 0., 1000.);

        if (lastMode != currentMode)
        {
            if (lastMode)
                lastMode->stop();
            lastMode = currentMode;
            if (currentMode)
                currentMode->start();
        }

        if (currentMode)
            currentMode->update();

        lastModeUpdate = now;

        performance.current++;
    }

    updateDisplay();

    if (!lastDisplayRedraw || now - lastDisplayRedraw >= 1000/60)
    {
        redrawDisplay();

        lastDisplayRedraw = now;
    }

    if (now - performance.lastTime >= 1000)
    {
        performance.last = performance.current;
        performance.current = 0;
        performance.lastTime = now;
    }

    for (Controller &controller : controllers())
        controller.parser.update();

    handleSerial();
}
