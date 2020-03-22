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
#include "displays/statusdisplay.h"
#include "modes/defaultmode.h"

namespace {
struct {
    AsyncWebServer server{80};
    WebHandler handler;
} web;

ModeBase *lastMode{};
Display *lastDisplay{};

// To solve circular dependencies between headers:

void StatusDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

void StarfieldDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

void PingPongDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

void SpiroDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

void GameOfLifeDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

void MetersDisplay::button(bool pressed)
{
    if (!pressed)
        currentDisplay = &displays::mainMenu;
}

SettingsMenu::SettingsMenu() :
    item5{displays::mainMenu, "Back"}
{}

CommonSettingsMenu::CommonSettingsMenu() :
    item0{displays::settingsMenu, "Back"}
{}

DefaultModeSettingsMenu::DefaultModeSettingsMenu() :
    item0{displays::settingsMenu, "Back"}
{}

ManualModeSettingsMenu::ManualModeSettingsMenu() :
    item0{displays::settingsMenu, "Back"}
{}

BluetoothModeSettingsMenu::BluetoothModeSettingsMenu() :
    item0{displays::settingsMenu, "Back"}
{}

PotiSettingsMenu::PotiSettingsMenu() :
    item0{displays::settingsMenu, "Back"}
{}

DemosMenu::DemosMenu() :
    item5{displays::mainMenu, "Back"}
{}

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

    const auto now = millis();
    if (false)
    if (now - lastDebug >= 50)
    {
        Serial.print("pwm: ");
        Serial.println(front.command.left.pwm);

        lastDebug = now;
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
        case 'l':
        case 'L':
            led_toggle = !led_toggle;
            Serial.printf("led: %d\n", led_toggle);
            for (auto &controller : controllers)
                controller.command.led = led_toggle;
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

    WiFi.mode(WIFI_AP);
    WiFi.softAP("bobbycar", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    //WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

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

    for (auto &controller : controllers)
    {
        controller.command.buzzer = {};
        controller.command.left.phaseAdvMax = controller.command.right.phaseAdvMax = 25;
        controller.command.left.iMotMax = controller.command.right.iMotMax = defaultIMotMax;
        controller.command.left.iDcMax = controller.command.right.iDcMax = defaultIDcMax;
        controller.command.left.fieldWeakMax = controller.command.right.fieldWeakMax = defaultFieldWeakMax;
    }

    modes::defaultMode.gas1_wert = defaultDefaultModeGas1Wert;
    modes::defaultMode.gas2_wert = defaultDefaultModeGas2Wert;
    modes::defaultMode.brems1_wert = defaultDefaultModeBrems1Wert;
    modes::defaultMode.brems2_wert = defaultDefaultModeBrems2Wert;

    currentMode = &modes::defaultMode;
    currentDisplay = &displays::status;

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
