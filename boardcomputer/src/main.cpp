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

namespace {
ModeBase *lastMode{};
unsigned long lastModeUpdate{};
unsigned long lastDisplayUpdate{};
double gasSum, bremsSum;
int16_t sampleCount;
}

void setup()
{
//    pinMode(TFT_MOSI, OUTPUT);
//    pinMode(TFT_SCLK, OUTPUT);
//    pinMode(TFT_CS, OUTPUT);
//    pinMode(TFT_DC, OUTPUT);
//    pinMode(TFT_RST, OUTPUT);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    initScreen();

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    bluetoothSerial.begin("bobbycar");

    controllers[0].serial.begin(38400, SERIAL_8N1, PINS_RX1, PINS_TX1);
    controllers[1].serial.begin(38400, SERIAL_8N1, PINS_RX2, PINS_TX2);

    raw_gas = 0;
    raw_brems = 0;
    gas = 0;
    brems = 0;
    gasSum = 0.;
    bremsSum = 0.;
    sampleCount = 0;

    applyDefaultSettings();

    // applyDefaultSettings is in global, global cannot include default mode, circular dependency
    modes::defaultMode.add_schwelle = defaultDefaultModeAddSchwelle;
    modes::defaultMode.gas1_wert = defaultDefaultModeGas1Wert;
    modes::defaultMode.gas2_wert = defaultDefaultModeGas2Wert;
    modes::defaultMode.brems1_wert = defaultDefaultModeBrems1Wert;
    modes::defaultMode.brems2_wert = defaultDefaultModeBrems2Wert;

    currentMode = &modes::defaultMode;

    initWebserver();
    switchScreen<DefaultScreen>();
    initRotary();
}

void loop()
{
    //digitalWrite(TFT_MOSI, HIGH);
    //digitalWrite(TFT_SCLK, HIGH);
    //digitalWrite(TFT_CS, HIGH);
    //digitalWrite(TFT_DC, HIGH);
    //digitalWrite(TFT_RST, HIGH);
    //delay(1000);
    //digitalWrite(TFT_MOSI, LOW);
    //digitalWrite(TFT_SCLK, LOW);
    //digitalWrite(TFT_CS, LOW);
    //digitalWrite(TFT_DC, LOW);
    //digitalWrite(TFT_RST, LOW);
    //delay(1000);

    performance.current++;

    analogRead(PINS_GAS);
    gasSum += analogRead(PINS_GAS);
    analogRead(PINS_BREMS);
    bremsSum += analogRead(PINS_BREMS);
    sampleCount++;

    const auto now = millis();
    if (!lastModeUpdate)
        lastModeUpdate = now;
    else if (now - lastModeUpdate >= 1000/50)
    {
        raw_gas = gasSum / sampleCount;
        gas = scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);

        raw_brems = bremsSum / sampleCount;
        brems = scaleBetween<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);

        gasSum = 0.;
        bremsSum = 0.;
        sampleCount = 0;

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
    }

    if (!lastDisplayUpdate || now - lastDisplayUpdate >= 1000/60)
    {
        updateDisplay();

        lastDisplayUpdate = now;
    }

    if (now - performance.lastTime >= 1000)
    {
        performance.last = performance.current;
        performance.current = 0;
        performance.lastTime = now;
    }

    for (auto &controller : controllers)
        controller.parser.update();

    handleSerial();
}
