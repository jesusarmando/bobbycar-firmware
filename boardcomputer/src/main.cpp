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

void receiveFeedback()
{
    for (Controller &controller : controllers)
    {
        // Check for new data availability in the Serial buffer
        while (controller.serial.available())
        {
            controller.incomingByte    = controller.serial.read();                                // Read the incoming byte
            controller.bufStartFrame = ((uint16_t)(controller.incomingBytePrev) << 8) +  controller.incomingByte; // Construct the start frame

            //Serial.printf("received: %x\r\n", controller.incomingByte);

            // Copy received data
            if (controller.bufStartFrame == Feedback::VALID_HEADER) {                     // Initialize if new data is detected
                controller.p   = (byte *)&controller.newFeedback;
                *controller.p++  = controller.incomingBytePrev;
                *controller.p++  = controller.incomingByte;
                controller.idx  = 2;
            } else if (controller.idx >= 2 && controller.idx < sizeof(controller.feedback)) { // Save the new received data
                *controller.p++  = controller.incomingByte;
                controller.idx++;
            }

            // Check if we reached the end of the package
            if (controller.idx == sizeof(controller.feedback)) {
                uint16_t checksum = calculateChecksum(controller.newFeedback);

                // Check validity of the new data
                if (controller.newFeedback.start == Feedback::VALID_HEADER && checksum == controller.newFeedback.checksum)
                {
                    controller.feedback = controller.newFeedback;
                    controller.lastFeedback = millis();
                }
//                else
//                {
//                    if (controller.newFeedback.start == Feedback::VALID_HEADER)
//                        Serial.println("header matched");
//                    else
//                        Serial.println("header did not match");

//                    if (checksum == controller.newFeedback.checksum)
//                        Serial.println("checksum matched");
//                    else
//                        Serial.println("checksum did not match");
//                }
                controller.idx = 0; // Reset the index (it prevents to enter in this if condition in the next cycle)
            }

            // Update previous states
            controller.incomingBytePrev  = controller.incomingByte;
        }
    }
}

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
        Serial.println(front.controller.command.left.pwm);

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

    gasMin = defaultGasMin;
    gasMax = defaultGasMax;
    bremsMin = defaultBremsMin;
    bremsMax = defaultBremsMax;

    front.left.enable = defaultEnableFrontLeft;
    front.right.enable = defaultEnableFrontRight;
    back.left.enable = defaultEnableBackLeft;
    back.right.enable = defaultEnableBackRight;

    front.left.invert = defaultInvertFrontLeft;
    front.right.invert = defaultInvertFrontRight;
    back.left.invert = defaultInvertBackLeft;
    back.right.invert = defaultInvertBackRight;

    for (auto &controller : controllers)
    {
        controller.command.buzzer = {};
        controller.command.left.phaseAdvMax = controller.command.right.phaseAdvMax = 25;
    }

    controllers[0].serial.begin(38400, SERIAL_8N1, rxPin1, txPin1);
    controllers[1].serial.begin(38400, SERIAL_8N1, rxPin2, txPin2);

    for (auto &controller : controllers)
    {
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

    bluetoothSerial.begin("bobbycar");

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    //WiFi.begin("realraum", "r3alraum");
    WiFi.begin("McDonalds Free WiFi 2.4GHz", "Passwort_123");

    web.server.addHandler(&web.handler);
    web.server.begin();

    attachInterrupt(decltype(rotary)::ClkPin, updateRotate, CHANGE);
    attachInterrupt(decltype(rotary)::SwPin, updateSwitch, CHANGE);
}

void loop()
{
    /*

#define BAT_CELLS               12        // battery number of cells. Normal Hoverboard battery: 10s
#define BAT_LOW_LVL1_ENABLE     0         // to beep or not to beep, 1 or 0
#define BAT_LOW_LVL2_ENABLE     1         // to beep or not to beep, 1 or 0
#define BAT_LOW_LVL1            (360 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // gently beeps at this voltage level. [V*100/cell]. In this case 3.60 V/cell
#define BAT_LOW_LVL2            (350 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // your battery is almost empty. Charge now! [V*100/cell]. In this case 3.50 V/cell
#define BAT_LOW_DEAD            (337 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // undervoltage poweroff. (while not driving) [V*100/cell]. In this case 3.37 V/cell

    // ####### BEEP AND EMERGENCY POWEROFF #######
    if (TEMP_POWEROFF_ENABLE && board_temp_deg_c >= TEMP_POWEROFF) {  // poweroff before mainboard burns OR low bat 3
      poweroff();
    } else if (TEMP_WARNING_ENABLE && board_temp_deg_c >= TEMP_WARNING) {  // beep if mainboard gets hot
      buzzerFreq = 4;
      buzzerPattern = 1;
    } else if (batVoltage < BAT_LOW_LVL1 && batVoltage >= BAT_LOW_LVL2 && BAT_LOW_LVL1_ENABLE) {  // low bat 1: slow beep
      buzzerFreq = 5;
      buzzerPattern = 42;
    } else if (batVoltage < BAT_LOW_LVL2 && batVoltage >= BAT_LOW_DEAD && BAT_LOW_LVL2_ENABLE) {  // low bat 2: fast beep
      buzzerFreq = 5;
      buzzerPattern = 6;
    } else if (errCode_Left || errCode_Right || timeoutFlag) {  // beep in case of Motor error or serial timeout - fast beep
      buzzerFreq = 12;
      buzzerPattern = 1;
    } else if (BEEPS_BACKWARD && speedRL < -50) {  // backward beep
      buzzerFreq = 5;
      buzzerPattern = 1;
    } else {  // do not beep
      buzzerFreq = 0;
      buzzerPattern = 0;
    }

    // ####### INACTIVITY TIMEOUT #######
    if (abs(speedRL) > 50) {
      inactivity_timeout_counter = 0;
    } else {
      inactivity_timeout_counter ++;
    }
    if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1)) {  // rest of main loop needs maybe 1ms
      poweroff();
    }

    */

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

    receiveFeedback();

    handleDebugSerial();
}
