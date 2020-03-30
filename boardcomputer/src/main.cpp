#include <Arduino.h>

#include <HardwareSerial.h>
#include <WiFi.h>

#include "../../common.h"

#include "globals.h"
#include "webserver.h"
#include "modes/defaultmode.h"
#include "screens.h"
#include "rotary.h"
#include "serialhandler.h"

namespace {
ModeBase *lastMode{};
unsigned long lastUpdate{};
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    initScreen();

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    WiFi.begin("realraum", "r3alraum");
    //WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    bluetoothSerial.begin("bobbycar");

    controllers[0].serial.begin(38400, SERIAL_8N1, PINS_RX1, PINS_TX1);
    controllers[1].serial.begin(38400, SERIAL_8N1, PINS_RX2, PINS_TX2);

    applyDefaultSettings();

    // applyDefaultSettings is in global, global cannot include default mode, circular dependency
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
    const auto now = millis();
    if (!lastUpdate || now - lastUpdate >= 1000/50)
    {
        constexpr auto times = 100;
        const auto read_n_times = [](int pin){
            analogRead(pin);
            double sum{};
            for (int i = 0; i < times; i++)
                sum += analogRead(pin);
            return sum/times;
        };

        raw_gas = read_n_times(PINS_GAS);
        gas = scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);

        raw_brems = read_n_times(PINS_BREMS);
        brems = scaleBetween<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);

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

        lastUpdate = now;

        performance.current++;
    }
    updateScreen();

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
