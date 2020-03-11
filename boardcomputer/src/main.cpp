#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <ESPAsyncWebServer.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

#include "../../common.h"

#include "settings.h"
#include "utils.h"
#include "modebase.h"
#include "defaultmode.h"
#include "manualmode.h"
#include "bluetoothmode.h"
#include "controller.h"
#include "htmltag.h"
#include "webhandler.h"
#include "htmlutils.h"
#include "statusdisplay.h"
#include "starfielddisplay.h"
#include "pingpongdisplay.h"
#include "spirodisplay.h"

namespace {
uint16_t raw_gas, raw_brems;
float gas, brems;
uint16_t gasMin, gasMax, bremsMin, bremsMax;

bool power_toggle{false};
bool led_toggle{false};

unsigned long lastUpdate = millis();
unsigned long lastRedraw = millis();
unsigned long lastScreenSwitch = millis();
unsigned long lastDebug = millis();

wl_status_t last_status;
IPAddress last_ip;

struct {
    unsigned long lastTime = millis();
    int current{0};
    int last{0};
} performance;

std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};
struct {
    Controller &controller;

    struct {
        bool invert, enable;
    } left, right;
} front{controllers[0]}, back{controllers[1]};
bool enableFrontLeft, enableFrontRight, enableBackLeft, enableBackRight;

struct {
    DefaultMode defaultMode;
    ManualMode manualMode;
    BluetoothMode bluetoothMode;

    std::reference_wrapper<ModeBase> currentMode{defaultMode};
} modes;

struct {
    BluetoothSerial serial;
    std::array<uint8_t, 256> buffer;
    std::array<uint8_t, 256>::iterator pos{buffer.begin()};
} bluetooth;

struct {
    AsyncWebServer server{80};
    WebHandler handler;
} web;

struct {
    TFT_eSPI tft = TFT_eSPI();

    StatusDisplay status;
    StarfieldDisplay starfield;
    PingPongDisplay pingPong;
    SpiroDisplay spiro;

    std::reference_wrapper<Display> currentDisplay{status};
} display;

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

void nextDisplay()
{
    display.currentDisplay.get().stop();

    if (&display.currentDisplay.get() == &display.status)
        display.currentDisplay = display.starfield;
    else if (&display.currentDisplay.get() == &display.starfield)
        display.currentDisplay = display.pingPong;
    else if (&display.currentDisplay.get() == &display.pingPong)
        display.currentDisplay = display.spiro;
    else if (&display.currentDisplay.get() == &display.spiro)
        display.currentDisplay = display.status;

    display.currentDisplay.get().start();
}

void fixCommonParams()
{
    front.controller.command.left.enable = enableFrontLeft;
    front.controller.command.right.enable = enableFrontRight;
    back.controller.command.left.enable = enableBackLeft;
    back.controller.command.right.enable = enableBackRight;

    if (front.left.invert)
        front.controller.command.left.pwm = -front.controller.command.left.pwm;
    if (front.right.invert)
        front.controller.command.right.pwm = -front.controller.command.right.pwm;
    if (back.left.invert)
        back.controller.command.left.pwm = -back.controller.command.left.pwm;
    if (back.right.invert)
        back.controller.command.right.pwm = -back.controller.command.right.pwm;
}

void sendCommands()
{
    for (auto &controller : controllers)
    {
        controller.command.start = Command::VALID_HEADER;
        controller.command.checksum = calculateChecksum(controller.command);
        controller.serial.write((uint8_t *) &controller.command, sizeof(controller.command));
    }
}

void DefaultMode::update()
{
    if (waitForGasLoslass)
    {
        if (gas < 50)
            waitForGasLoslass = false;
        else
            gas = 0;
    }
    const auto gas_squared = (gas * gas) / 1000;

    if (waitForBremsLoslass)
    {
        if (brems < 50)
            waitForBremsLoslass = false;
        else
            brems = 0;
    }
    const auto brems_squared = (brems * brems) / 1000;

    const auto now = millis();

    float pwm;
    if (gas_squared >= add_schwelle)
    {
        pwm = (gas_squared/1000.*gas1_wert) + (brems_squared/1000.*brems1_wert);

        if (enableWeakeningSmoothening && (pwm > 1000. || lastPwm > 1000.))
        {
            if (lastPwm < pwm)
            {
                pwm = std::min(pwm, lastPwm+(weakeningSmoothening*(now-lastTime)/100.f));
                if (pwm < 1000.)
                    pwm = 1000.;
            }
            else if (lastPwm > pwm)
            {
                pwm = std::max(pwm, lastPwm-(weakeningSmoothening*(now-lastTime)/100.f));
            }
        }
    }
    else
        pwm = (gas_squared/1000.*gas2_wert) - (brems_squared/1000.*brems2_wert);

    lastPwm = pwm;
    lastTime = now;

    for (Controller &controller : controllers)
    {
        Command &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm / 100. * (&controller == &controllers[0] ? frontPercentage : backPercentage);
        }
    }

    fixCommonParams();

    sendCommands();
}

void ManualMode::update()
{
    if (potiControl)
    {
        if (gas > 500. && brems > 500.)
        {
            pwm = 0;
            modes.defaultMode.waitForGasLoslass = true;
            modes.defaultMode.waitForBremsLoslass = true;
            modes.currentMode = modes.defaultMode;
            modes.currentMode.get().update();
            return;
        }

        pwm += (gas/1000.) - (brems/1000.);
    }

    for (auto &controller : controllers)
    {
        auto &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm;
        }
    }
    fixCommonParams();

    sendCommands();
}

void BluetoothMode::start()
{
    // clear buffer
    while (bluetooth.serial.available())
        bluetooth.serial.read();
}

void BluetoothMode::update()
{
    bool newLine{false};
    while (bluetooth.serial.available())
    {
        *bluetooth.pos = bluetooth.serial.read();
        if (*bluetooth.pos == '\n')
            newLine = true;
        bluetooth.pos++;
        if (newLine)
            break;
    }

    if (!newLine)
        return;

    StaticJsonDocument<256> doc;
    const auto error = deserializeJson(doc, &(*bluetooth.buffer.begin()), std::distance(bluetooth.buffer.begin(), bluetooth.pos));

    bluetooth.pos = bluetooth.buffer.begin();

    if (error)
    {
        bluetooth.serial.println(error.c_str());
        return;
    }

    if (!doc.containsKey("frontLeft"))
    {
        bluetooth.serial.print("no frontLeft");
        return;
    }
    if (!doc.containsKey("frontRight"))
    {
        bluetooth.serial.print("no frontRight");
        return;
    }
    if (!doc.containsKey("backLeft"))
    {
        bluetooth.serial.print("no backLeft");
        return;
    }
    if (!doc.containsKey("backRight"))
    {
        bluetooth.serial.print("no backRight");
        return;
    }

    controllers[0].command.left.pwm = doc["frontLeft"].as<int16_t>();
    controllers[0].command.right.pwm = doc["frontRight"].as<int16_t>();
    controllers[1].command.left.pwm = doc["backLeft"].as<int16_t>();
    controllers[1].command.right.pwm = doc["backRight"].as<int16_t>();

    for (Controller &controller : controllers)
    {
        Command &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->enable = true;
            motor->ctrlTyp = ControlType::FieldOrientedControl;
            motor->ctrlMod = ControlMode::Torque;
        }
    }
    fixCommonParams();

    sendCommands();
}

void renderLiveData(AsyncResponseStream &response)
{
    HtmlTag fieldset(response, "fieldset");

    {
        HtmlTag legend(response, "legend");
        response.print("Live data:");
    }

    {
        HtmlTag p(response, "p");
        response.print("raw_gas=");
        response.print(raw_gas);
        response.print(" raw_brems=");
        response.print(raw_brems);
        response.print(" gasPin=");
        response.print(gasPin);
        response.print(" bremsPin=");
        response.print(bremsPin);
        response.print(" gas=");
        response.print(gas);
        response.print(" brems=");
        response.print(brems);
        response.print(" mainLoop=");
        response.print(performance.last);
    }

    for (const Controller &controller : controllers)
    {
        HtmlTag fieldset(response, "fieldset");

        {
            HtmlTag legend(response, "legend");
            response.print("Board:");
        }

        {
            HtmlTag p(response, "p");
            response.print("left: ");
            response.print(controller.command.left.pwm);
            response.print(", right: ");
            response.print(controller.command.right.pwm);
            response.print(", beeper: (");
            response.print(controller.command.buzzer.freq);
            response.print(", ");
            response.print(controller.command.buzzer.pattern);
            response.print("), led: ");
            response.print(controller.command.led ? "true" : "false ");
        }

        if (millis() - controller.lastFeedback > 1000)
        {
            HtmlTag span(response, "span", " style=\"color: red;\"");
            response.print("Dead!");
            continue;
        }

        {
            HtmlTag p(response, "p");
            response.print(controller.feedback.batVoltage/100.);
            response.print("V, ");
            response.print(controller.feedback.boardTemp/100.);
            response.print("°C");
        }

        for (const MotorFeedback &motor : {controller.feedback.left, controller.feedback.right})
        {
            HtmlTag fieldset(response, "fieldset");

            {
                HtmlTag legend(response, "legend");
                response.print("Motor:");
            }

            {
                String color, text;
                switch (motor.error)
                {
                case 0: color="green"; text="Ok"; break;
                case 1: color="red"; text="hall sensor not connected"; break;
                case 2: color="red"; text="hall sensor short curcuit"; break;
                case 4: color="red"; text="motors not able to spin"; break;
                default: color="red"; text="Unknown "; text += motor.error; break;
                }

                {
                    HtmlTag span(response, "span", " style=\"color: " + color + ";\"");
                    response.print(text);
                }

                if (motor.chops)
                {
                    response.print(", chopping (");
                    response.print(motor.chops);
                    response.print(")");
                }
            }

            {
                HtmlTag p(response, "p");
                response.print(motor.speed);
                response.print("Rpm, ");
                response.print(motor.current);
                response.print("A");
            }

            {
                HtmlTag table(response, "table", " border=\"1\"");
                HtmlTag tr(response, "tr");

                {
                    HtmlTag td(response, "td", " style=\"width: 50px;\"");
                    response.print(motor.angle);
                }

                const auto printCell = [&response](bool active, const char *text){
                    String str;
                    if (active)
                        str = " style=\"background-color: grey;\"";
                    HtmlTag td(response, "td", str);
                    response.print(text);
                };

                printCell(motor.hallA, "A");
                printCell(motor.hallB, "B");
                printCell(motor.hallC, "C");
            }
        }
    }
}

void handleIndex(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            HtmlTag ul(response, "ul");

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"live\"");
                response.print("Live");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"screenParams\"");
                response.print("Screen params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"commonParams\"");
                response.print("Common params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"defaultModeParams\"");
                response.print("Default mode params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"manualModeParams\"");
                response.print("Manual mode params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"potiParams\"");
                response.print("Poti params");
            }
        }
    }

    request->send(&response);
}

void handleLive(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");
            response.print("<meta http-equiv=\"refresh\" content=\"1\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            renderLiveData(response);
        }
    }

    request->send(&response);
}

void handleScreenParams(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            response.print(" - ");

            {
                HtmlTag a(response, "a", " href=\"nextScreen\"");
                response.print("Next screen");
            }

            {
                HtmlTag form(response, "form", " action=\"/setScreenParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Screen params:");
                }

                numberInput(response, display.status.framerate(), "framerate", "Status framerate:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void handleSetScreenParams(AsyncWebServerRequest *request)
{
    if (!request->hasParam("framerate"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no framerate specified");
        request->send(&response);
        return;
    }



    {
        AsyncWebParameter* p = request->getParam("framerate");

        display.status.setFramerate(strtol(p->value().c_str(), nullptr, 10));
    }

    request->redirect("/screenParams");
}

void handleNextScreen(AsyncWebServerRequest *request)
{
    nextDisplay();

    request->redirect("/screenParams");
}

void handleCommonParams(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            {
                HtmlTag form(response, "form", " action=\"/setCommonParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Common params:");
                }

                label(response, "mode", "Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"mode\" name=\"mode\" required");
                    selectOption(response, "defaultMode", "Default", &modes.currentMode.get()==&modes.defaultMode);
                    selectOption(response, "manualMode", "Manual", &modes.currentMode.get()==&modes.manualMode);
                    selectOption(response, "bluetoothMode", "Bluetooth", &modes.currentMode.get()==&modes.bluetoothMode);
                }

                breakLine(response);

                numberInput(response, controllers[0].command.left.iMotMax, "iMotMax", "Maximum current:");

                breakLine(response);

                numberInput(response, controllers[0].command.left.iDcMax, "iDcMax", "Maximum link current:");

                breakLine(response);

                numberInput(response, controllers[0].command.left.nMotMax, "nMotMax", "Maximum speed:");

                breakLine(response);

                numberInput(response, controllers[0].command.left.fieldWeakMax, "fieldWeakMax", "Maximum field weakening current:");

                breakLine(response);

                numberInput(response, controllers[0].command.left.phaseAdvMax, "phaseAdvMax", "Maximum phase adv angle:");

                breakLine(response);

                checkboxInput(response, enableFrontLeft, "enableFrontLeft", "Enable front left:");

                breakLine(response);

                checkboxInput(response, enableFrontRight, "enableFrontRight", "Enable front right:");

                breakLine(response);

                checkboxInput(response, enableBackLeft, "enableBackLeft", "Enable back left:");

                breakLine(response);

                checkboxInput(response, enableBackRight, "enableBackRight", "Enable back right:");

                breakLine(response);

                checkboxInput(response, front.left.invert, "invertFrontLeft", "Invert front left:");

                breakLine(response);

                checkboxInput(response, front.right.invert, "invertFrontRight", "Invert front right:");

                breakLine(response);

                checkboxInput(response, back.left.invert, "invertBackLeft", "Invert back left:");

                breakLine(response);

                checkboxInput(response, back.right.invert, "invertBackRight", "Invert back right:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void handleDefaultModeParams(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            {
                HtmlTag form(response, "form", " action=\"/setDefaultModeParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Default Mode:");
                }

                label(response, "ctrlTyp1", "Control Type:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp1\" name=\"ctrlTyp\" required");
                    selectOption(response, "Commutation", "Commutation", modes.defaultMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", modes.defaultMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", modes.defaultMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod1", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod1\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", modes.defaultMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", modes.defaultMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", modes.defaultMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", modes.defaultMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                checkboxInput(response, modes.defaultMode.enableWeakeningSmoothening, "enableWeakeningSmoothening", "Enable Weakening Smoothening:");

                breakLine(response);

                numberInput(response, modes.defaultMode.weakeningSmoothening, "weakeningSmoothening", "Weakening Smoothening:");

                breakLine(response);

                numberInput(response, modes.defaultMode.frontPercentage, "frontPercentage", "Front percentage:");

                breakLine(response);

                numberInput(response, modes.defaultMode.backPercentage, "backPercentage", "Back percentage:");

                breakLine(response);

                numberInput(response, modes.defaultMode.add_schwelle, "add_schwelle", "add_schwelle:");

                breakLine(response);

                numberInput(response, modes.defaultMode.gas1_wert, "gas1_wert", "gas1_wert:");

                breakLine(response);

                numberInput(response, modes.defaultMode.gas2_wert, "gas2_wert", "gas2_wert:");

                breakLine(response);

                numberInput(response, modes.defaultMode.brems1_wert, "brems1_wert", "brems1_wert:");

                breakLine(response);

                numberInput(response, modes.defaultMode.brems2_wert, "brems2_wert", "brems2_wert:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void handleManualModeParams(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            {
                HtmlTag form(response, "form", " action=\"/setManualModeParams\"");

                HtmlTag fieldset(response, "fieldset");


                {
                    HtmlTag legend(response, "legend");
                    response.print("Manual Mode:");
                }

                checkboxInput(response, modes.manualMode.potiControl, "potiControl", "Poti control:");

                breakLine(response);

                numberInput(response, modes.manualMode.pwm, "pwm", "Pwm:");

                breakLine(response);

                label(response, "ctrlTyp2", "Control Type:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp2\" name=\"ctrlTyp\" required");
                    selectOption(response, "Commutation", "Commutation", modes.manualMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", modes.manualMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", modes.manualMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod2", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod2\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", modes.manualMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", modes.manualMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", modes.manualMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", modes.manualMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void handlePotiParams(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/html");

    response.print("<!doctype html>");

    {
        HtmlTag html(response, "html");

        {
            HtmlTag head(response, "head");

            response.print("<meta charset=\"utf-8\" />");
            response.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");

            {
                HtmlTag title(response, "title");
                response.print("Bobbycar remote");
            }
        }

        {
            HtmlTag body(response, "body");

            {
                HtmlTag h1(response, "h1");
                response.print("Bobbycar remote");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }

            {
                HtmlTag form(response, "form", " action=\"/setPotiParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Poti calibration:");
                }

                numberInput(response, gasMin, "gasMin", "gasMin:");

                breakLine(response);

                numberInput(response, gasMax, "gasMax", "gasMax:");

                breakLine(response);

                numberInput(response, bremsMin, "bremsMin", "bremsMin:");

                breakLine(response);

                numberInput(response, bremsMax, "bremsMax", "bremsMax:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void handleSetCommonParams(AsyncWebServerRequest *request)
{
    if (!request->hasParam("mode"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no mode specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("iMotMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no iMotMax specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("iDcMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no iDcMax specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("nMotMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no nMotMax specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("fieldWeakMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no fieldWeakMax specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("phaseAdvMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no phaseAdvMax specified");
        request->send(&response);
        return;
    }



    {
        AsyncWebParameter* p = request->getParam("mode");

        if (p->value() == "defaultMode")
        {
            modes.currentMode.get().start();
            modes.currentMode = modes.defaultMode;
            modes.currentMode.get().stop();
        }
        else if (p->value() == "manualMode")
        {
            modes.currentMode.get().start();
            modes.currentMode = modes.manualMode;
            modes.currentMode.get().stop();
        }
        else if (p->value() == "bluetoothMode")
        {
            modes.currentMode.get().start();
            modes.currentMode = modes.bluetoothMode;
            modes.currentMode.get().stop();
        }
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid mode");
            request->send(&response);
            return;
        }
    }

    {
        AsyncWebParameter* p = request->getParam("iMotMax");

        for (auto &controller : controllers)
            controller.command.left.iMotMax = controller.command.right.iMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("iDcMax");

        for (auto &controller : controllers)
            controller.command.left.iDcMax = controller.command.right.iDcMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("nMotMax");

        for (auto &controller : controllers)
            controller.command.left.nMotMax = controller.command.right.nMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("fieldWeakMax");

        for (auto &controller : controllers)
            controller.command.left.fieldWeakMax = controller.command.right.fieldWeakMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("phaseAdvMax");

        for (auto &controller : controllers)
            controller.command.left.phaseAdvMax = controller.command.right.phaseAdvMax = strtol(p->value().c_str(), nullptr, 10);
    }

    enableFrontLeft = request->hasParam("enableFrontLeft") && request->getParam("enableFrontLeft")->value() == "on";
    enableFrontRight = request->hasParam("enableFrontRight") && request->getParam("enableFrontRight")->value() == "on";
    enableBackLeft = request->hasParam("enableBackLeft") && request->getParam("enableBackLeft")->value() == "on";
    enableBackRight = request->hasParam("enableBackRight") && request->getParam("enableBackRight")->value() == "on";

    front.left.invert = request->hasParam("invertFrontLeft") && request->getParam("invertFrontLeft")->value() == "on";
    front.right.invert = request->hasParam("invertFrontRight") && request->getParam("invertFrontRight")->value() == "on";
    back.left.invert = request->hasParam("invertBackLeft") && request->getParam("invertBackLeft")->value() == "on";
    back.right.invert = request->hasParam("invertBackRight") && request->getParam("invertBackRight")->value() == "on";

    request->redirect("/commonParams");
}

void handleSetDefaultModeParams(AsyncWebServerRequest *request)
{
    if (!request->hasParam("ctrlTyp"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no ctrlTyp specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("ctrlMod"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no ctrlMod specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("weakeningSmoothening"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no weakeningSmoothening specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("frontPercentage"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no frontPercentage specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("backPercentage"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no backPercentage specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("add_schwelle"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no add_schwelle specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("gas1_wert"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no gas1_wert specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("gas2_wert"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no gas2_wert specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("brems1_wert"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no brems1_wert specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("brems2_wert"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no brems2_wert specified");
        request->send(&response);
        return;
    }



    {
        AsyncWebParameter* p = request->getParam("ctrlTyp");

        if (p->value() == "Commutation")
            modes.defaultMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            modes.defaultMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            modes.defaultMode.ctrlTyp = ControlType::FieldOrientedControl;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlTyp");
            request->send(&response);
            return;
        }
    }

    {
        AsyncWebParameter* p = request->getParam("ctrlMod");

        if (p->value() == "OpenMode")
            modes.defaultMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            modes.defaultMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            modes.defaultMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            modes.defaultMode.ctrlMod = ControlMode::Torque;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlMod");
            request->send(&response);
            return;
        }
    }

    modes.defaultMode.enableWeakeningSmoothening = request->hasParam("enableWeakeningSmoothening") && request->getParam("enableWeakeningSmoothening")->value() == "on";

    {
        AsyncWebParameter* p = request->getParam("weakeningSmoothening");

        modes.defaultMode.weakeningSmoothening = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("frontPercentage");

        modes.defaultMode.frontPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("backPercentage");

        modes.defaultMode.backPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("add_schwelle");

        modes.defaultMode.add_schwelle = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas1_wert");

        modes.defaultMode.gas1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas2_wert");

        modes.defaultMode.gas2_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems1_wert");

        modes.defaultMode.brems1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems2_wert");

        modes.defaultMode.brems2_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    request->redirect("/defaultModeParams");
}

void handleSetManualModeParams(AsyncWebServerRequest *request)
{
    if (!request->hasParam("pwm"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no mode specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("ctrlTyp"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no ctrlTyp specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("ctrlMod"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no ctrlMod specified");
        request->send(&response);
        return;
    }



    modes.manualMode.potiControl = request->hasParam("potiControl") && request->getParam("potiControl")->value() == "on";

    {
        AsyncWebParameter* p = request->getParam("pwm");

        modes.manualMode.pwm = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("ctrlTyp");

        if (p->value() == "Commutation")
            modes.manualMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            modes.manualMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            modes.manualMode.ctrlTyp = ControlType::FieldOrientedControl;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlTyp");
            request->send(&response);
            return;
        }
    }

    {
        AsyncWebParameter* p = request->getParam("ctrlMod");

        if (p->value() == "OpenMode")
            modes.manualMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            modes.manualMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            modes.manualMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            modes.manualMode.ctrlMod = ControlMode::Torque;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlMod");
            request->send(&response);
            return;
        }
    }

    request->redirect("/manualModeParams");
}

void handleSetPotiParams(AsyncWebServerRequest *request)
{
    if (!request->hasParam("gasMin"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no gasMin specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("gasMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no gasMax specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("bremsMin"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no bremsMin specified");
        request->send(&response);
        return;
    }

    if (!request->hasParam("bremsMax"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no bremsMax specified");
        request->send(&response);
        return;
    }



    {
        AsyncWebParameter* p = request->getParam("gasMin");

        gasMin = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gasMax");

        gasMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("bremsMin");

        bremsMin = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("bremsMax");

        bremsMax = strtol(p->value().c_str(), nullptr, 10);
    }
}

bool WebHandler::canHandle(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        return true;
    else if (request->url() == "/live")
        return true;
    else if (request->url() == "/screenParams")
        return true;
    else if (request->url() == "/setScreenParams")
        return true;
    else if (request->url() == "/nextScreen")
        return true;
    else if (request->url() == "/commonParams")
        return true;
    else if (request->url() == "/setCommonParams")
        return true;
    else if (request->url() == "/defaultModeParams")
        return true;
    else if (request->url() == "/setDefaultModeParams")
        return true;
    else if (request->url() == "/manualModeParams")
        return true;
    else if (request->url() == "/setManualModeParams")
        return true;
    else if (request->url() == "/potiParams")
        return true;
    else if (request->url() == "/setPotiParams")
        return true;

    return false;
}

void WebHandler::handleRequest(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        handleIndex(request);
    else if (request->url() == "/live")
        handleLive(request);
    else if (request->url() == "/screenParams")
        handleScreenParams(request);
    else if (request->url() == "/setScreenParams")
        handleSetScreenParams(request);
    else if (request->url() == "/nextScreen")
        handleNextScreen(request);
    else if (request->url() == "/commonParams")
        handleCommonParams(request);
    else if (request->url() == "/setCommonParams")
        handleSetCommonParams(request);
    else if (request->url() == "/defaultModeParams")
        handleDefaultModeParams(request);
    else if (request->url() == "/setDefaultModeParams")
        handleSetDefaultModeParams(request);
    else if (request->url() == "/manualModeParams")
        handleManualModeParams(request);
    else if (request->url() == "/setManualModeParams")
        handleSetManualModeParams(request);
    else if (request->url() == "/potiParams")
        handlePotiParams(request);
    else if (request->url() == "/setPotiParams")
        handleSetPotiParams(request);
}

void StatusDisplay::start()
{
    Serial.println("StatusDisplay::start()");
    display.tft.setRotation(0);
    display.tft.fillScreen(TFT_BLACK);
    display.tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void StatusDisplay::update()
{
    int y = 0;

    display.tft.drawString(String("gas=") + raw_gas + " -> " + gas + "                                                ",0,y,2); y+=15;
    display.tft.drawString(String("brems=") + raw_brems + " -> " + brems + "                                                ",0,y,2); y+=15;

    y+=12;

    const auto print_controller = [&](const Controller &controller)
    {
        display.tft.drawString(String("pwm: ") + controller.command.left.pwm + ", " + controller.command.right.pwm + "                                                ", 0,y,4); y+=25;
        if (millis() - controller.lastFeedback > 1000)
        {
            display.tft.setTextColor(TFT_RED, TFT_BLACK);
            display.tft.drawString("Dead!                                                ",0,y,4); y+=25;
            display.tft.drawString("                                                     ",0,y,4); y+=25;
            display.tft.drawString("                                                     ",0,y,4); y+=25;
            display.tft.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        else
        {
            display.tft.drawString(String("U=") + (controller.feedback.batVoltage/100.) + "V, T=" + (controller.feedback.boardTemp/10.) + "C                                                 ",0,y,4); y+=25;
            const auto print_motor = [&](const char *pre, const MotorFeedback &motor)
            {
                display.tft.drawString(pre, 0, y, 4);
                if (motor.error)
                    display.tft.setTextColor(TFT_RED, TFT_BLACK);
                else
                    display.tft.setTextColor(TFT_GREEN, TFT_BLACK);
                display.tft.drawString(String() + motor.error + "   ", 15, y, 4);
                display.tft.setTextColor(TFT_WHITE, TFT_BLACK);
                display.tft.drawString(String("") + std::abs(motor.current/50.) + "A"
                                       "    " +
                                       (motor.speed/32.133) +
                                       "                                                ",45,y,4);

                display.tft.drawString(String("") +
                                       (motor.hallA ? '1' : '0') + (motor.hallB ? '1' : '0') + (motor.hallC ? '1' : '0')
                                       , 215, y, 2);
                y+=25;
            };

            print_motor("l: ", controller.feedback.left);
            print_motor("r: ", controller.feedback.right);
        }
    };

    for (const auto &controller : controllers)
    {
        print_controller(controller);
        y+=12;
    }

    String modeStr;
    if (&modes.currentMode.get() == &modes.defaultMode) modeStr = "Default";
    else if (&modes.currentMode.get() == &modes.manualMode) modeStr = "Manual";
    else if (&modes.currentMode.get() == &modes.bluetoothMode) modeStr = "Bluetooth";
    else modeStr = "Unknown";

    display.tft.drawString("WiFi: " + toString(WiFi.status()) + "                                                ",0,y,2);
    display.tft.drawString(String("Limit0: ") + front.controller.command.left.iMotMax + "A", 160, y, 2); y+=15;
    display.tft.drawString("IP: " + WiFi.localIP().toString() + "                                                ",0,y,2);
    display.tft.drawString(String("Limit1: ") + front.controller.command.left.iDcMax + "A", 160, y, 2); y+=15;
    display.tft.drawString(String("Performance: ") + performance.last + "                                                ",0,y,2);
    display.tft.drawString("Mode: " + modeStr, 125, y, 2); y+=15;
}

void StatusDisplay::stop()
{
    Serial.println("StatusDisplay::stop()");
}

StarfieldDisplay::StarfieldDisplay()
{
    za = random(256);
    zb = random(256);
    zc = random(256);
    zx = random(256);
}

void StarfieldDisplay::start()
{
    Serial.println("StarfieldDisplay::start()");
    display.tft.setRotation(1);
    display.tft.fillScreen(TFT_BLACK);

    // fastSetup() must be used immediately before fastPixel() to prepare screen
    // It must be called after any other graphics drawing function call if fastPixel()
    // is to be called again
    //tft.fastSetup(); // Prepare plot window range for fast pixel plotting
}

void StarfieldDisplay::update()
{
    uint8_t spawnDepthVariation = 255;

    for(int i = 0; i < NSTARS; ++i)
    {
      if (sz[i] <= 1)
      {
        sx[i] = 160 - 120 + rng();
        sy[i] = rng();
        sz[i] = spawnDepthVariation--;
      }
      else
      {
        int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;

        // This is a faster pixel drawing function for occassions where many single pixels must be drawn
        display.tft.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

        sz[i] -= 2;
        if (sz[i] > 1)
        {
          int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
          int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;

          if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240)
          {
            uint8_t r, g, b;
            r = g = b = 255 - sz[i];
            display.tft.drawPixel(screen_x, screen_y, display.tft.color565(r,g,b));
          }
          else
            sz[i] = 0; // Out of screen, die.
        }
      }
    }
}

void StarfieldDisplay::stop()
{
    Serial.println("StarfieldDisplay::stop()");
}

PingPongDisplay::PingPongDisplay()
{
    lpaddle_y = random(0, h - paddle_h);
    rpaddle_y = random(0, h - paddle_h);

    // ball is placed on the center of the left paddle
    ball_y = lpaddle_y + (paddle_h / 2);

    calc_target_y();
}

void PingPongDisplay::start()
{
    Serial.println("PingPongDisplay::start()");

    display.tft.setRotation(1);

    display.tft.fillScreen(BLACK);

    midline();
}

void PingPongDisplay::update()
{
    lpaddle();
    rpaddle();

    midline();

    ball();
}

void PingPongDisplay::stop()
{
    Serial.println("PingPongDisplay::stop()");
}

SpiroDisplay::SpiroDisplay()
{
}

void SpiroDisplay::start()
{
    Serial.println("SpiroDisplay::start()");
    display.tft.setRotation(3);
}

void SpiroDisplay::update()
{
    for (int i = 0; i < std::max(1, n); i++)
        render();
}

void SpiroDisplay::stop()
{
    Serial.println("SpiroDisplay::stop()");
}

void SpiroDisplay::render()
{
    auto &tft = display.tft;

    if (i == 0)
    {
        tft.fillScreen(TFT_BLACK);
        n = random(2, 23);
        r = random(20, 100);
        colour = 0; //rainbow();
    }

    if (i < (360 * n))
    {
        sx = cos((i / n - 90) * DEG2RAD);
        sy = sin((i / n - 90) * DEG2RAD);
        x0 = sx * (120 - r) + 159;
        yy0 = sy * (120 - r) + 119;


        sy = cos(((i % 360) - 90) * DEG2RAD);
        sx = sin(((i % 360) - 90) * DEG2RAD);
        x1 = sx * r + x0;
        yy1 = sy * r + yy0;
        tft.drawPixel(x1, yy1, rainbow(map(i%360,0,360,0,127))); //colour);
    }

    if (i == (360 * n))
    {
        r = random(20, 100);//r = r / random(2,4);
    }

    if (i >= (360 * n))
    {
        auto new_i = i - (360 * n);

        sx = cos((new_i / n - 90) * DEG2RAD);
        sy = sin((new_i / n - 90) * DEG2RAD);
        x0 = sx * (120 - r) + 159;
        yy0 = sy * (120 - r) + 119;


        sy = cos(((new_i % 360) - 90) * DEG2RAD);
        sx = sin(((new_i % 360) - 90) * DEG2RAD);
        x1 = sx * r + x0;
        yy1 = sy * r + yy0;
        tft.drawPixel(x1, yy1, rainbow(map(new_i%360,0,360,0,127))); //colour);
    }

    i++;
    if (i == 2* (360 * n))
        i = 0;
}

void PingPongDisplay::midline()
{
    // If the ball is not on the line then don't redraw the line
    if ((ball_x<dashline_x-ball_w) && (ball_x > dashline_x+dashline_w)) return;

    display.tft.startWrite();

    // Quick way to draw a dashed line
    display.tft.setAddrWindow(dashline_x, 0, dashline_w, h);

    for(int16_t i = 0; i < dashline_n; i+=2) {
        display.tft.pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
        display.tft.pushColor(BLACK, dashline_w*dashline_h); // push gap pixels
    }

    display.tft.endWrite();
}

void PingPongDisplay::lpaddle()
{
    if (lpaddle_d == 1)
    {
        display.tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, 1, BLACK);
    }
    else if (lpaddle_d == -1)
    {
        display.tft.fillRect(lpaddle_x, lpaddle_y + paddle_h - 1, paddle_w, 1, BLACK);
    }

    lpaddle_y = lpaddle_y + lpaddle_d;

    if (ball_dx == 1)
        lpaddle_d = 0;
    else
    {
        if (lpaddle_y + paddle_h / 2 == target_y) lpaddle_d = 0;
        else if (lpaddle_y + paddle_h / 2 > target_y) lpaddle_d = -1;
        else lpaddle_d = 1;
    }

    if (lpaddle_y + paddle_h >= h && lpaddle_d == 1) lpaddle_d = 0;
    else if (lpaddle_y <= 0 && lpaddle_d == -1) lpaddle_d = 0;

    display.tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, paddle_h, WHITE);
}

void PingPongDisplay::rpaddle()
{
    if (rpaddle_d == 1) {
        display.tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, 1, BLACK);
    }
    else if (rpaddle_d == -1) {
        display.tft.fillRect(rpaddle_x, rpaddle_y + paddle_h - 1, paddle_w, 1, BLACK);
    }

    rpaddle_y = rpaddle_y + rpaddle_d;

    if (ball_dx == -1) rpaddle_d = 0;
    else {
        if (rpaddle_y + paddle_h / 2 == target_y) rpaddle_d = 0;
        else if (rpaddle_y + paddle_h / 2 > target_y) rpaddle_d = -1;
        else rpaddle_d = 1;
    }

    if (rpaddle_y + paddle_h >= h && rpaddle_d == 1) rpaddle_d = 0;
    else if (rpaddle_y <= 0 && rpaddle_d == -1) rpaddle_d = 0;

    display.tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, WHITE);
}

void PingPongDisplay::calc_target_y()
{
    int16_t target_x;
    int16_t reflections;
    int16_t y;

    if (ball_dx == 1) {
        target_x = w - ball_w;
    }
    else {
        target_x = -1 * (w - ball_w);
    }

    y = abs(target_x * (ball_dy / ball_dx) + ball_y);

    reflections = floor(y / h);

    if (reflections % 2 == 0) {
        target_y = y % h;
    }
    else {
        target_y = h - (y % h);
    }
}

void PingPongDisplay::ball()
{
    ball_x = ball_x + ball_dx;
    ball_y = ball_y + ball_dy;

    if (ball_dx == -1 && ball_x == paddle_w && ball_y + ball_h >= lpaddle_y && ball_y <= lpaddle_y + paddle_h) {
        ball_dx = ball_dx * -1;
        dly = random(5); // change speed of ball after paddle contact
        calc_target_y();
    } else if (ball_dx == 1 && ball_x + ball_w == w - paddle_w && ball_y + ball_h >= rpaddle_y && ball_y <= rpaddle_y + paddle_h) {
        ball_dx = ball_dx * -1;
        dly = random(5); // change speed of ball after paddle contact
        calc_target_y();
    } else if ((ball_dx == 1 && ball_x >= w) || (ball_dx == -1 && ball_x + ball_w < 0)) {
        dly = 5;
    }

    if (ball_y > h - ball_w || ball_y < 0) {
        ball_dy = ball_dy * -1;
        ball_y += ball_dy; // Keep in bounds
    }

    //tft.fillRect(oldball_x, oldball_y, ball_w, ball_h, BLACK);
    display.tft.drawRect(oldball_x, oldball_y, ball_w, ball_h, BLACK); // Less TFT refresh aliasing than line above for large balls
    display.tft.fillRect(   ball_x,    ball_y, ball_w, ball_h, WHITE);
    oldball_x = ball_x;
    oldball_y = ball_y;
}
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    bluetooth.serial.begin("bobbycar");

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    WiFi.begin("realraum", "r3alraum");

    gasMin = defaultGasMin;
    gasMax = defaultGasMax;
    bremsMin = defaultBremsMin;
    bremsMax = defaultBremsMax;

    enableFrontLeft = defaultEnableFrontLeft;
    enableFrontRight = defaultEnableFrontRight;
    enableBackLeft = defaultEnableBackLeft;
    enableBackRight = defaultEnableBackRight;

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

    modes.defaultMode.gas1_wert = defaultDefaultModeGas1Wert;
    modes.defaultMode.gas2_wert = defaultDefaultModeGas2Wert;
    modes.defaultMode.brems1_wert = defaultDefaultModeBrems1Wert;
    modes.defaultMode.brems2_wert = defaultDefaultModeBrems2Wert;

    modes.currentMode.get().start();

    web.server.addHandler(&web.handler);
    web.server.begin();

    display.tft.init();

    display.currentDisplay.get().start();
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

        modes.currentMode.get().update();

        lastUpdate = now;

        performance.current++;
    }

    if (now - lastRedraw >= 1000/display.currentDisplay.get().framerate())
    {
        display.currentDisplay.get().update();

        lastRedraw = now;
    }

    if (false)
    if (now - lastScreenSwitch >= 1000*5)
    {
        nextDisplay();

        lastScreenSwitch = now;
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
