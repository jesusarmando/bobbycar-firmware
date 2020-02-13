#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <ESPAsyncWebServer.h>
#include <HardwareSerial.h>
#include <WiFi.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <array>
#include <algorithm>
#include <functional>
#include <stdint.h>

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

namespace {
uint16_t raw_gas, raw_brems;
float gas, brems;
uint16_t gasMin, gasMax, bremsMin, bremsMax;
bool invertLeft, invertRight;

bool power_toggle{false};
bool led_toggle{false};

int lastSendCommand = millis();
int lastStatus = millis();

wl_status_t last_wl_status;
IPAddress last_ip_address;

std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};

struct DrivingModes
{
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

void sendCommands()
{
    const auto now = millis();
    if (now - lastSendCommand < 50)
        return;

    lastSendCommand = now;

    for (auto &controller : controllers)
    {
        controller.command.start = Command::VALID_HEADER;
        controller.command.checksum = calculateChecksum(controller.command);
        controller.serial.write((uint8_t *) &controller.command, sizeof(controller.command));
    }
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
                else
                {
                    if (controller.newFeedback.start == Feedback::VALID_HEADER)
                        Serial.println("header matched");
                    else
                        Serial.println("header did not match");

                    if (checksum == controller.newFeedback.checksum)
                        Serial.println("checksum matched");
                    else
                        Serial.println("checksum did not match");
                }
                controller.idx = 0; // Reset the index (it prevents to enter in this if condition in the next cycle)
            }

            // Update previous states
            controller.incomingBytePrev  = controller.incomingByte;
        }
    }
}

void handleDebugSerial()
{
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

    const auto now = millis();
    if (now - lastStatus > 500)
    {
        lastStatus = now;

        const auto wl_status = WiFi.status();
        if (wl_status != last_wl_status)
        {
            Serial.print("Status changed to: ");
            Serial.println(wl_status);
            last_wl_status = wl_status;
        }

        const auto ip_address = WiFi.localIP();
        if (ip_address != last_ip_address)
        {
            Serial.print("IP changed to : ");
            Serial.println(ip_address);
            last_ip_address = ip_address;
        }

        Serial.print("raw_gas=");
        Serial.print(raw_gas);
        Serial.print(" raw_brems=");
        Serial.println(raw_brems);
    }
}

void fixDirections(Command &command)
{
    if (invertLeft)
        command.left.pwm = -command.left.pwm;
    if (invertRight)
        command.right.pwm = -command.right.pwm;
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
    const auto gas_cubed = (gas * gas) / 1000;

    if (waitForBremsLoslass)
    {
        if (brems < 50)
            waitForBremsLoslass = false;
        else
            brems = 0;
    }
    const auto brems_cubed = (brems * brems) / 1000;

    float pwm;
    if (gas_cubed >= 950.)
        pwm = gas_cubed + (brems_cubed/2.);
    else
        pwm = gas_cubed - (brems_cubed*0.75);

    for (Controller &controller : controllers)
    {
        Command &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->enable = true;
            motor->ctrlTyp = ControlType::FieldOrientedControl;
            motor->ctrlMod = ControlMode::Torque;
            motor->pwm = pwm / 100. * (&controller == &controllers[0] ? frontPercentage : backPercentage);
        }
        fixDirections(command);
    }

    sendCommands();
}

void ManualMode::update()
{
    if (manual)
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
            motor->enable = enable;
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm;
        }
        fixDirections(command);
    }

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

    if (error)
    {
        bluetooth.serial.println(error.c_str());
        return;
    }

    bluetooth.pos = bluetooth.buffer.begin();

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
        fixDirections(command);
    }

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

            {
                HtmlTag a(response, "a", " href=\"/live\"");
                response.print("Live");
            }

            //renderLiveData(response);

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

                checkboxInput(response, invertLeft, "invertLeft", "Invert left:");

                breakLine(response);

                checkboxInput(response, invertRight, "invertRight", "Invert right:");

                breakLine(response);

                submitButton(response);
            }

            {
                HtmlTag form(response, "form", " action=\"/setDefaultModeParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Default Mode:");
                }

                numberInput(response, modes.defaultMode.frontPercentage, "frontPercentage", "Front percentage:");

                breakLine(response);

                numberInput(response, modes.defaultMode.backPercentage, "backPercentage", "Back percentage:");

                breakLine(response);

                submitButton(response);
            }

            {
                HtmlTag form(response, "form", " action=\"/setManualModeParams\"");

                HtmlTag fieldset(response, "fieldset");


                {
                    HtmlTag legend(response, "legend");
                    response.print("Manual Mode:");
                }

                checkboxInput(response, modes.manualMode.manual, "manual", "Manual Control:");

                breakLine(response);

                checkboxInput(response, modes.manualMode.enable, "enable", "Enable:");

                breakLine(response);

                numberInput(response, modes.manualMode.pwm, "pwm", "Pwm:");

                breakLine(response);

                label(response, "ctrlTyp", "Control Type:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp\" name=\"ctrlTyp\" required");
                    selectOption(response, "Commutation", "Commutation", modes.manualMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", modes.manualMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", modes.manualMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", modes.manualMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", modes.manualMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", modes.manualMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", modes.manualMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                submitButton(response);
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

    invertLeft = request->hasParam("invertLeft") && request->getParam("invertLeft")->value() == "on";
    invertRight = request->hasParam("invertRight") && request->getParam("invertRight")->value() == "on";

    request->redirect("/");
}

void handleSetDefaultModeSetParams(AsyncWebServerRequest *request)
{
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



    {
        AsyncWebParameter* p = request->getParam("frontPercentage");

        modes.defaultMode.frontPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("backPercentage");

        modes.defaultMode.backPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    request->redirect("/");
}

void handleSetManualModeSetParams(AsyncWebServerRequest *request)
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



    modes.manualMode.manual = request->hasParam("manual") && request->getParam("manual")->value() == "on";
    modes.manualMode.enable = request->hasParam("enable") && request->getParam("enable")->value() == "on";

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

    request->redirect("/");
}

void handleSetPotiParams(AsyncWebServerRequest *request)
{
    // TODO
}

bool WebHandler::canHandle(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        return true;
    else if (request->url() == "/live")
        return true;
    else if (request->url() == "/setCommonParams")
        return true;
    else if (request->url() == "/setDefaultModeParams")
        return true;
    else if (request->url() == "/setManualModeParams")
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
    else if (request->url() == "/setCommonParams")
        handleSetCommonParams(request);
    else if (request->url() == "/setDefaultModeParams")
        handleSetDefaultModeSetParams(request);
    else if (request->url() == "/setManualModeParams")
        handleSetManualModeSetParams(request);
    else if (request->url() == "/setPotiParams")
        handleSetPotiParams(request);
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

    invertLeft = defaultInvertLeft;
    invertRight = defaultInvertRight;

    for (auto &controller : controllers)
        controller.command.buzzer = {};

    controllers[0].serial.begin(38400, SERIAL_8N1, rxPin1, txPin1);
    controllers[1].serial.begin(38400, SERIAL_8N1, rxPin2, txPin2);

    modes.currentMode.get().start();

    web.server.addHandler(&web.handler);
    web.server.begin();
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

    analogRead(gasPin);
    delay(2);
    raw_gas = analogRead(gasPin);
    gas = scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);

    analogRead(bremsPin);
    delay(2);
    raw_brems = analogRead(bremsPin);
    brems = scaleBetween<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);

    modes.currentMode.get().update();

    receiveFeedback();

    handleDebugSerial();
}
