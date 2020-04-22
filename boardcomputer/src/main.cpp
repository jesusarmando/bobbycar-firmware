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
#include "statistics.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothconnectbmsaction.h"

namespace {
ModeInterface *lastMode{};
unsigned long lastModeUpdate{};
unsigned long lastStatsUpdate{};
unsigned long lastDisplayRedraw{};

constexpr auto modeUpdateRate = 50;
constexpr auto statsUpdateRate = 50;
constexpr auto displayRedrawRate = 50;
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
        loadSettings();

    updateSwapFrontBack();

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbyquad", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    BluetoothBeginMasterAction{}.triggered();
    if (settings.autoConnectBms)
        BluetoothConnectBmsAction{}.triggered();

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

    readPotis();

    if (gas > 200.f || brems > 200.f)
        switchScreen<CalibrateDisplay>(true);
    else
        switchScreen<StatusDisplay>();
}

void loop()
{
    const auto now = millis();

    if (!lastModeUpdate)
        lastModeUpdate = now;
    else if (now - lastModeUpdate >= 1000/modeUpdateRate)
    {
        readPotis();

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

    if (!lastStatsUpdate)
        lastStatsUpdate = now;
    else if (now - lastStatsUpdate >= 1000/statsUpdateRate)
    {
        updateAccumulators();
        pushStats();
        lastStatsUpdate = now;
    }

    updateDisplay();

    if (!lastDisplayRedraw || now - lastDisplayRedraw >= 1000/displayRedrawRate)
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

    bms::update();
}
