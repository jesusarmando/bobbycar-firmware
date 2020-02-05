#include <Arduino.h>
#include <HardwareSerial.h>
#include <ESPAsyncWebServer.h>

#include <WiFi.h>

#include <array>
#include <algorithm>
#include <functional>
#include <stdint.h>

#include "../../common.h"

namespace {
constexpr auto gasMin = 800., gasMax = 3700.,
               bremsMin = 1300., bremsMax = 4000.;
constexpr auto gasPin = 33, bremsPin = 35;

template<typename T>
T scaleBetween(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x < std::min(in_min, in_max))
        x = std::min(in_min, in_max);
    else if (x > std::max(in_min, in_max))
        x = std::max(in_min, in_max);

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getGas()
{
    analogRead(gasPin);
    delay(2);
    const auto raw_gas = analogRead(gasPin);

    return scaleBetween<float>(raw_gas, gasMin, gasMax, 0., 1000.);
}

float getBrems()
{
    analogRead(bremsPin);
    delay(2);
    const auto raw_brems = analogRead(bremsPin);

    return scaleBetween<float>(raw_brems, bremsMin, bremsMax, 0., 1000.);
}

class DrivingModes;
class ModeBase {
public:
    virtual void update() = 0;
};

Command command;

class DefaultMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override;

    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};
};

class ManualMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override;

    bool manual = true;
    bool enable = true;
    int16_t pwm = 0;
    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Speed;
};

class DrivingModes
{
public:
    DefaultMode defaultMode;
    ManualMode manualMode;

    std::reference_wrapper<ModeBase> currentMode{defaultMode};
};

struct Controller {
    Controller(HardwareSerial &serial) : serial{serial} {}

    HardwareSerial &serial;
    Feedback feedback, newFeedback;

    unsigned long lastFeedback = 0;

    uint8_t idx = 0;                        // Index for new data pointer
    uint16_t bufStartFrame;                 // Buffer Start Frame
    uint8_t *p;                             // Pointer declaration for the new received data
    uint8_t incomingByte;
    uint8_t incomingBytePrev;
};

class HtmlTag {
public:
    HtmlTag(AsyncResponseStream &stream, const char *tag) :
        stream{stream},
        tag{tag}
    {
        stream.print("<");
        stream.print(tag);
        stream.print(">");
    }

    template<typename T>
    HtmlTag(AsyncResponseStream &stream, const char *tag, const T &x) :
        stream{stream},
        tag{tag}
    {
        stream.print("<");
        stream.print(tag);
        stream.print(x);
        stream.print(">");
    }

    ~HtmlTag()
    {
        stream.print("</");
        stream.print(tag);
        stream.print(">");
    }

private:
    AsyncResponseStream &stream;
    const char * const tag;
};

class WebHandler : public AsyncWebHandler
{
public:
    using AsyncWebHandler::AsyncWebHandler;

    bool canHandle(AsyncWebServerRequest *request) override;

    void handleRequest(AsyncWebServerRequest *request) override;

private:
    void handleIndex(AsyncWebServerRequest *request);
    void handleLive(AsyncWebServerRequest *request);
    void handleSetCommonParams(AsyncWebServerRequest *request);
    void handleSetManualModeSetParams(AsyncWebServerRequest *request);
};

bool power_toggle{false};
bool led_toggle{false};

int lastSendCommand = millis();
int lastStatus = millis();

enum { ScreenA, ScreenB, ScreenC } screen { ScreenA };
unsigned long lastScreenSwitch = 0;

std::array<Controller, 2> controllers{Controller{Serial1}, Controller{Serial2}};
Controller &first{controllers[0]},
           &second{controllers[1]};

DrivingModes modes;

AsyncWebServer server(80);
WebHandler handler;

void sendCommand()
{
    command.start = Command::VALID_HEADER;
    command.checksum = calculateChecksum(command);
    Serial1.write((uint8_t *) &command, sizeof(command));
    Serial2.write((uint8_t *) &command, sizeof(command));
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
        switch (Serial.read())
        {
        case 't':
        case 'T':
            power_toggle = !power_toggle;
            Serial.printf("power: %d\n", power_toggle);
            command.poweroff = power_toggle;
            break;
        case 'l':
        case 'L':
            led_toggle = !led_toggle;
            Serial.printf("led: %d\n", led_toggle);
            command.led = led_toggle;
            break;
        case '0': command.buzzer.freq = 0; break;
        case '1': command.buzzer.freq = 1; break;
        case '2': command.buzzer.freq = 2; break;
        case '3': command.buzzer.freq = 3; break;
        case '4': command.buzzer.freq = 4; break;
        case '5': command.buzzer.freq = 5; break;
        case '6': command.buzzer.freq = 6; break;
        case '7': command.buzzer.freq = 7; break;
        case '8': command.buzzer.freq = 8; break;
        case '9': command.buzzer.freq = 9; break;
        }
    }

    const auto now = millis();
    if (now - lastStatus > 500)
    {
        lastStatus = now;

        Serial.print("Status: ");
        Serial.println(WiFi.status());
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    }
}

void DefaultMode::update()
{
    auto gas_hebel = getGas();
    if (waitForGasLoslass)
    {
        if (gas_hebel < 50)
            waitForGasLoslass = false;
        else
            gas_hebel = 0;
    }
    gas_hebel = (gas_hebel * gas_hebel) / 1000;

    auto brems_hebel = getBrems();
    if (waitForBremsLoslass)
    {
        if (brems_hebel < 50)
            waitForBremsLoslass = false;
        else
            brems_hebel = 0;
    }
    brems_hebel = (brems_hebel * brems_hebel) / 1000;

    int16_t pwm;
    if (gas_hebel >= 950.)
        pwm = gas_hebel + (brems_hebel/2.);
    else
        pwm = gas_hebel - (brems_hebel*0.75);

    command.left.enable = command.right.enable = true;
    command.left.ctrlTyp = command.right.ctrlTyp = ControlType::FieldOrientedControl;
    command.left.ctrlMod = command.right.ctrlMod = ControlMode::Torque;
    command.left.pwm=pwm;
    command.right.pwm=-pwm;
}

void ManualMode::update()
{
    if (manual)
    {
        auto gas_hebel = getGas();
        auto brems_hebel = getBrems();

        if (gas_hebel > 500 && brems_hebel > 500)
        {
            pwm = 0;
            modes.defaultMode.waitForGasLoslass = true;
            modes.defaultMode.waitForBremsLoslass = true;
            modes.currentMode = modes.defaultMode;
            modes.currentMode.get().update();
            return;
        }

        pwm += (gas_hebel/1000) - (brems_hebel/1000);
    }

    command.left.enable = command.right.enable = enable;
    command.left.ctrlTyp = command.right.ctrlTyp = ctrlTyp;
    command.left.ctrlMod = command.right.ctrlMod = ctrlMod;
    command.left.pwm=pwm;
    command.right.pwm=-pwm;
}

bool WebHandler::canHandle(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        return true;
    else if (request->url() == "/live")
        return true;
    else if (request->url() == "/setCommonParams")
        return true;
    else if (request->url() == "/setManualModeParams")
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
    else if (request->url() == "/setManualModeParams")
        handleSetManualModeSetParams(request);
}

void renderLiveData(AsyncResponseStream &response)
{
    HtmlTag fieldset(response, "fieldset");

    {
        HtmlTag legend(response, "legend");
        response.print("Live data:");
    }

    for (const Controller &controller : controllers)
    {
        HtmlTag fieldset(response, "fieldset");

        {
            HtmlTag legend(response, "legend");
            response.print("Board:");
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

                {
                    String str;
                    if (motor.hallA)
                        str = " style=\"background-color: grey;\"";
                    HtmlTag td(response, "td", str);
                    response.print("A");
                }

                {
                    String str;
                    if (motor.hallB)
                        str = " style=\"background-color: grey;\"";
                    HtmlTag td(response, "td", str);
                    response.print("B");
                }

                {
                    String str;
                    if (motor.hallC)
                        str = " style=\"background-color: grey;\"";
                    HtmlTag td(response, "td", str);
                    response.print("C");
                }
            }
        }
    }
}

void WebHandler::handleLive(AsyncWebServerRequest *request)
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

void WebHandler::handleIndex(AsyncWebServerRequest *request)
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

            renderLiveData(response);

            {
                HtmlTag form(response, "form", " action=\"/setCommonParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Common params:");
                }

                {
                    HtmlTag label(response, "label", " for=\"mode\"");
                    response.print("Mode:");
                }

                response.print("<br/>");

                {
                    HtmlTag select(response, "select", " id=\"mode\" name=\"mode\"");
                    {
                        String str{" value=\"defaultMode\""};
                        if (&modes.currentMode.get()==&modes.defaultMode)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Default");
                    }
                    {
                        String str{" value=\"manualMode\""};
                        if (&modes.currentMode.get()==&modes.manualMode)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Manual");
                    }
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"iMotMax\"");
                    response.print("Maximum current:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"iMotMax\" name=\"iMotMax\" value=\"");
                    response.print(command.left.iMotMax);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"iDcMax\"");
                    response.print("Maximum link current:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"iDcMax\" name=\"iDcMax\" value=\"");
                    response.print(command.left.iDcMax);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"nMotMax\"");
                    response.print("Maximum speed:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"nMotMax\" name=\"nMotMax\" value=\"");
                    response.print(command.left.nMotMax);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"fieldWeakMax\"");
                    response.print("Maximum field weakening current:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"fieldWeakMax\" name=\"fieldWeakMax\" value=\"");
                    response.print(command.left.fieldWeakMax);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"phaseAdvMax\"");
                    response.print("Maximum phase adv angle:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"phaseAdvMax\" name=\"phaseAdvMax\" value=\"");
                    response.print(command.left.phaseAdvMax);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag button(response, "button", " type=\"submit\"");
                    response.print("Submit");
                }
            }

            {

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Default Mode:");
                }
            }

            {
                HtmlTag form(response, "form", " action=\"/setManualModeParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "legend");
                    response.print("Manual Mode:");
                }

                {
                    HtmlTag label(response, "label", " for=\"manual\"");
                    response.print("Manual Control:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"checkbox\" id=\"manual\" name=\"manual\" value=\"on\"");
                    if (modes.manualMode.manual)
                        response.print(" checked");
                    response.print(" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"enable\"");
                    response.print("enable:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"checkbox\" id=\"enable\" name=\"enable\" value=\"on\"");
                    if (modes.manualMode.enable)
                        response.print(" checked");
                    response.print(" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"pwm\"");
                    response.print("Pwm:");
                }

                response.print("<br/>");

                {
                    response.print("<input type=\"number\" id=\"pwm\" name=\"pwm\" value=\"");
                    response.print(modes.manualMode.pwm);
                    response.print("\" />");
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"ctrlTyp\"");
                    response.print("Control Type:");
                }

                response.print("<br/>");

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp\" name=\"ctrlTyp\"");

                    {
                        String str{" value=\"Commutation\""};
                        if (modes.manualMode.ctrlTyp == ControlType::Commutation)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Commutation");
                    }

                    {
                        String str{" value=\"Sinusoidal\""};
                        if (modes.manualMode.ctrlTyp == ControlType::Sinusoidal)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Sinusoidal");
                    }

                    {
                        String str{" value=\"FieldOrientedControl\""};
                        if (modes.manualMode.ctrlTyp == ControlType::FieldOrientedControl)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Field Oriented Control");
                    }
                }

                response.print("<br/>");

                {
                    HtmlTag label(response, "label", " for=\"ctrlMod\"");
                    response.print("Control Mode:");
                }

                response.print("<br/>");

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod\" name=\"ctrlMod\"");

                    {
                        String str{" value=\"OpenMode\""};
                        if (modes.manualMode.ctrlMod == ControlMode::OpenMode)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Open Mode");
                    }

                    {
                        String str{" value=\"Voltage\""};
                        if (modes.manualMode.ctrlMod == ControlMode::Voltage)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Voltage");
                    }

                    {
                        String str{" value=\"Speed\""};
                        if (modes.manualMode.ctrlMod == ControlMode::Speed)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Speed");
                    }

                    {
                        String str{" value=\"Torque\""};
                        if (modes.manualMode.ctrlMod == ControlMode::Torque)
                            str += " selected";
                        HtmlTag option(response, "option", str);
                        response.print("Torque");
                    }
                }

                response.print("<br/>");

                {
                    HtmlTag button(response, "button", " type=\"submit\"");
                    response.print("Submit");
                }
            }
        }
    }

    request->send(&response);
}

void WebHandler::handleSetCommonParams(AsyncWebServerRequest *request)
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
            modes.currentMode = modes.defaultMode;
        }
        else if (p->value() == "manualMode")
        {
            modes.currentMode = modes.manualMode;
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

        command.left.iMotMax = command.right.iMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("iDcMax");

        command.left.iDcMax = command.right.iDcMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("nMotMax");

        command.left.nMotMax = command.right.nMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("fieldWeakMax");

        command.left.fieldWeakMax = command.right.fieldWeakMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("phaseAdvMax");

        command.left.phaseAdvMax = command.right.phaseAdvMax = strtol(p->value().c_str(), nullptr, 10);
    }

    request->redirect("/");
}

void WebHandler::handleSetManualModeSetParams(AsyncWebServerRequest *request)
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
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println("setup()");

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("bobbycar", "Passwort_123");
    WiFi.begin("realraum", "r3alraum");

    command.buzzer = {};

    Serial1.begin(38400, SERIAL_8N1, 25, 27);

    Serial2.begin(38400, SERIAL_8N1, 13, 15);

    server.addHandler(&handler);
    server.begin();
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

    modes.currentMode.get().update();

    handleDebugSerial();

    const auto now = millis();
    if (now - lastSendCommand > 50)
    {
        lastSendCommand = now;
        sendCommand();
    }

    if (now - lastScreenSwitch > (screen==ScreenA?10000:5000))
    {
        lastScreenSwitch = now;
        switch(screen)
        {
        case ScreenA: screen = ScreenB; break;
        case ScreenB: screen = ScreenC; break;
        case ScreenC: screen = ScreenA; break;
        }
    }

    receiveFeedback();
}
