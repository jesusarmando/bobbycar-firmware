#include <Arduino.h>

#include <HardwareSerial.h>
#include <WiFi.h>

#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

#include "../../common.h"

#include "globals.h"
#include "rotary.h"
#include "webhandler.h"
#include "displays/menus/mainmenu.h"
#include "modes/defaultmode.h"

namespace {
struct {
    AsyncWebServer server{80};
    WebHandler handler;
} web;

MainMenu mainMenu;

ModeBase *lastMode{};
Display *lastDisplay{};

void handleDebugSerial()
{
    const auto status = WiFi.status();
    if (last_status != status)
    {
        Serial.print("Status changed to: ");
        Serial.println(toString(status));
        last_status = status;
    }

    const auto ip = WiFi.localIP();
    if (last_ip != ip)
    {
        Serial.print("IP changed to: ");
        Serial.println(ip.toString());
        last_ip = ip;
    }

    while(Serial.available())
    {
        const auto c = Serial.read();

        switch (c)
        {
        case 't':
        case 'T':
            power_toggle = !power_toggle;
            Serial.printf("power: %d\n", power_toggle);
            for (auto &controller : controllers)
                controller.command.poweroff = power_toggle;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            for (auto &controller : controllers)
                controller.command.buzzer.freq = c-'0';
            break;
        case 'A':
            if (currentDisplay)
                currentDisplay->rotate(-1);
            break;
        case 'B':
            if (currentDisplay)
                currentDisplay->rotate(1);
            break;
        case ' ':
            if (currentDisplay)
            {
                currentDisplay->button(true);
                currentDisplay->button(false);
            }
            break;
        }
    }
}

class InputDispatcher {
public:
    void rotate(int offset) { if (currentDisplay) currentDisplay->rotate(offset); }
    void button(bool pressed) { if (currentDisplay) currentDisplay->button(pressed); }
};

Rotary<InputDispatcher, rotaryClkPin, rotaryDtPin, rotarySwPin> rotary;

void updateRotate() { rotary.updateRotate(); }
void updateSwitch() { rotary.updateSwitch(); }
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setRotation(0);
    tft.drawString("Booting...", 32, 64, 4);

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    bluetoothSerial.begin("bobbycar");

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

    controllers[0].serial.begin(38400, SERIAL_8N1, rxPin1, txPin1);
    controllers[1].serial.begin(38400, SERIAL_8N1, rxPin2, txPin2);

    settings.iMotMax = defaultIMotMax;
    settings.iDcMax = defaultIDcMax;
    settings.nMotMax = defaultNMotMax;
    settings.fieldWeakMax = defaultFieldWeakMax;
    settings.phaseAdvMax = defaultPhaseAdvMax;

    for (auto &controller : controllers)
        controller.command.buzzer = {};

    modes::defaultMode.gas1_wert = defaultDefaultModeGas1Wert;
    modes::defaultMode.gas2_wert = defaultDefaultModeGas2Wert;
    modes::defaultMode.brems1_wert = defaultDefaultModeBrems1Wert;
    modes::defaultMode.brems2_wert = defaultDefaultModeBrems2Wert;

    currentMode = &modes::defaultMode;
    currentDisplay = &mainMenu.m_statusDisplay;

    Serial.print("The size of the main menu is: ");
    Serial.println(sizeof(mainMenu));

    web.server.addHandler(&web.handler);
    web.server.begin();

    attachInterrupt(decltype(rotary)::ClkPin, updateRotate, CHANGE);
    attachInterrupt(decltype(rotary)::SwPin, updateSwitch, CHANGE);
}

void loop()
{
    const auto now = millis();
    if (now - lastUpdate >= 1000/50)
    {
        constexpr auto times = 100;
        const auto read_n_times = [](int pin){
            analogRead(pin);
            double sum{};
            for (int i = 0; i < times; i++)
                sum += analogRead(pin);
            return sum/times;
        };

        raw_gas = read_n_times(gasPin);
        gas = scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);

        raw_brems = read_n_times(bremsPin);
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

    if (lastDisplay != currentDisplay)
    {
        if (lastDisplay)
            lastDisplay->stop();
        lastDisplay = currentDisplay;
        if (currentDisplay)
        {
            currentDisplay->start();
            currentDisplay->redraw();
        }
    }

    if (currentDisplay && now - lastRedraw >= 1000/currentDisplay->framerate())
    {
        currentDisplay->redraw();
        lastRedraw = now;
    }

    if (now - performance.lastTime >= 1000)
    {
        performance.last = performance.current;
        performance.current = 0;
        performance.lastTime = now;
    }

    for (auto &controller : controllers)
        controller.parser.update();

    handleDebugSerial();
}
