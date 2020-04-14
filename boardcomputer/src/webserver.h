#pragma once

#include <Esp.h>
#include <ESPAsyncWebServer.h>

#include "htmlutils.h"
#include "globals.h"
#include "menudisplay.h"
#include "changevaluedisplay.h"

#include "displays/statusdisplay.h"

#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "modes/larsmmode.h"
#include "modes/bluetoothmode.h"
#include "modes/websocketmode.h"

namespace {
class WebHandler : public AsyncWebHandler
{
public:
    bool canHandle(AsyncWebServerRequest *request) override;

    void handleRequest(AsyncWebServerRequest *request) override;

private:
    static void renderLiveData(AsyncResponseStream &response);
    static void handleIndex(AsyncWebServerRequest *request);
    static void handleLive(AsyncWebServerRequest *request);
    static void handleCommonParams(AsyncWebServerRequest *request);
    static void handleDefaultModeParams(AsyncWebServerRequest *request);
    static void handleTempomatModeParams(AsyncWebServerRequest *request);
    static void handlePotiParams(AsyncWebServerRequest *request);
    static void handleSetCommonParams(AsyncWebServerRequest *request);
    static void handleSetDefaultModeParams(AsyncWebServerRequest *request);
    static void handleSetTempomatModeParams(AsyncWebServerRequest *request);
    static void handleSetPotiParams(AsyncWebServerRequest *request);
    static void handleDisplay(AsyncWebServerRequest *request);
    static void handleDisplayAction(AsyncWebServerRequest *request);
    static void handleReboot(AsyncWebServerRequest *request);
};

bool WebHandler::canHandle(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        return true;
    else if (request->url() == "/live")
        return true;
    else if (request->url() == "/commonParams")
        return true;
    else if (request->url() == "/setCommonParams")
        return true;
    else if (request->url() == "/defaultModeParams")
        return true;
    else if (request->url() == "/setDefaultModeParams")
        return true;
    else if (request->url() == "/tempomatModeParams")
        return true;
    else if (request->url() == "/setTempomatModeParams")
        return true;
    else if (request->url() == "/potiParams")
        return true;
    else if (request->url() == "/setPotiParams")
        return true;
    else if (request->url() == "/display")
        return true;
    else if (request->url() == "/displayAction")
        return true;
    else if (request->url() == "/reboot")
        return true;

    return false;
}

void WebHandler::handleRequest(AsyncWebServerRequest *request)
{
    if (request->url() == "/")
        handleIndex(request);
    else if (request->url() == "/live")
        handleLive(request);
    else if (request->url() == "/commonParams")
        handleCommonParams(request);
    else if (request->url() == "/setCommonParams")
        handleSetCommonParams(request);
    else if (request->url() == "/defaultModeParams")
        handleDefaultModeParams(request);
    else if (request->url() == "/setDefaultModeParams")
        handleSetDefaultModeParams(request);
    else if (request->url() == "/tempomatModeParams")
        handleTempomatModeParams(request);
    else if (request->url() == "/setTempomatModeParams")
        handleSetTempomatModeParams(request);
    else if (request->url() == "/potiParams")
        handlePotiParams(request);
    else if (request->url() == "/setPotiParams")
        handleSetPotiParams(request);
    else if (request->url() == "/display")
        handleDisplay(request);
    else if (request->url() == "/displayAction")
        handleDisplayAction(request);
    else if (request->url() == "/reboot")
        handleReboot(request);
}

void WebHandler::renderLiveData(AsyncResponseStream &response)
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
        response.print(" gas=");
        response.print(gas);
        response.print(" brems=");
        response.print(brems);
        response.print(" mainLoop=");
        response.print(performance.last);
    }

    for (const Controller &controller : controllers())
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

        if (!controller.feedbackValid)
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

            HtmlTag ul(response, "ul");

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"live\"");
                response.print("Live");
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
                HtmlTag a(response, "a", " href=\"tempomatModeParams\"");
                response.print("Tempomat mode params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"potiParams\"");
                response.print("Poti params");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"display\"");
                response.print("Display");
            }

            {
                HtmlTag li(response, "li");
                HtmlTag a(response, "a", " href=\"reboot\"");
                response.print("Reboot");
            }
        }
    }

    request->send(&response);
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

void WebHandler::handleCommonParams(AsyncWebServerRequest *request)
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
                    selectOption(response, "defaultMode", modes::defaultMode.displayName(), currentMode==&modes::defaultMode);
                    selectOption(response, "tempomatMode", modes::tempomatMode.displayName(), currentMode==&modes::tempomatMode);
                    selectOption(response, "larsmMode", modes::larsmMode.displayName(), currentMode==&modes::larsmMode);
                    selectOption(response, "bluetoothMode", modes::bluetoothMode.displayName(), currentMode==&modes::bluetoothMode);
                    selectOption(response, "websocketMode", modes::websocketMode.displayName(), currentMode==&modes::websocketMode);
                }

                breakLine(response);

                numberInput(response, settings.limits.iMotMax, "iMotMax", "Maximum current:");

                breakLine(response);

                numberInput(response, settings.limits.iDcMax, "iDcMax", "Maximum link current:");

                breakLine(response);

                numberInput(response, settings.limits.nMotMax, "nMotMax", "Maximum speed:");

                breakLine(response);

                numberInput(response, settings.limits.fieldWeakMax, "fieldWeakMax", "Maximum field weakening current:");

                breakLine(response);

                numberInput(response, settings.limits.phaseAdvMax, "phaseAdvMax", "Maximum phase adv angle:");

                breakLine(response);

                checkboxInput(response, settings.hardware.enableFrontLeft, "enableFrontLeft", "Enable front left:");

                breakLine(response);

                checkboxInput(response, settings.hardware.enableFrontRight, "enableFrontRight", "Enable front right:");

                breakLine(response);

                checkboxInput(response, settings.hardware.enableBackLeft, "enableBackLeft", "Enable back left:");

                breakLine(response);

                checkboxInput(response, settings.hardware.enableBackRight, "enableBackRight", "Enable back right:");

                breakLine(response);

                checkboxInput(response, settings.hardware.invertFrontLeft, "invertFrontLeft", "Invert front left:");

                breakLine(response);

                checkboxInput(response, settings.hardware.invertFrontRight, "invertFrontRight", "Invert front right:");

                breakLine(response);

                checkboxInput(response, settings.hardware.invertBackLeft, "invertBackLeft", "Invert back left:");

                breakLine(response);

                checkboxInput(response, settings.hardware.invertBackRight, "invertBackRight", "Invert back right:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void WebHandler::handleDefaultModeParams(AsyncWebServerRequest *request)
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
                    selectOption(response, "Commutation", "Commutation", settings.defaultMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", settings.defaultMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", settings.defaultMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod1", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod1\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", settings.defaultMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", settings.defaultMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", settings.defaultMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", settings.defaultMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                checkboxInput(response, settings.defaultMode.enableSmoothing, "enableSmoothing", "Enable smoothing:");

                breakLine(response);

                numberInput(response, settings.defaultMode.smoothing, "smoothing", "Smoothing:");

                breakLine(response);

                numberInput(response, settings.defaultMode.frontPercentage, "frontPercentage", "Front percentage:");

                breakLine(response);

                numberInput(response, settings.defaultMode.backPercentage, "backPercentage", "Back percentage:");

                breakLine(response);

                numberInput(response, settings.defaultMode.add_schwelle, "add_schwelle", "add_schwelle:");

                breakLine(response);

                numberInput(response, settings.defaultMode.gas1_wert, "gas1_wert", "gas1_wert:");

                breakLine(response);

                numberInput(response, settings.defaultMode.gas2_wert, "gas2_wert", "gas2_wert:");

                breakLine(response);

                numberInput(response, settings.defaultMode.brems1_wert, "brems1_wert", "brems1_wert:");

                breakLine(response);

                numberInput(response, settings.defaultMode.brems2_wert, "brems2_wert", "brems2_wert:");

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void WebHandler::handleTempomatModeParams(AsyncWebServerRequest *request)
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
                HtmlTag form(response, "form", " action=\"/setTempomatModeParams\"");

                HtmlTag fieldset(response, "fieldset");


                {
                    HtmlTag legend(response, "legend");
                    response.print("Tempomat Mode:");
                }

                numberInput(response, modes::tempomatMode.pwm, "pwm", "Pwm:");

                breakLine(response);

                label(response, "ctrlTyp", "Control Type:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp\" name=\"ctrlTyp\" required");
                    selectOption(response, "Commutation", "Commutation", settings.tempomatMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", settings.tempomatMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", settings.tempomatMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", settings.tempomatMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", settings.tempomatMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", settings.tempomatMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", settings.tempomatMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                submitButton(response);
            }
        }
    }

    request->send(&response);
}

void WebHandler::handlePotiParams(AsyncWebServerRequest *request)
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

                numberInput(response, settings.hardware.poti.gasMin, "gasMin", "gasMin:");

                breakLine(response);

                numberInput(response, settings.hardware.poti.gasMax, "gasMax", "gasMax:");

                breakLine(response);

                numberInput(response, settings.hardware.poti.bremsMin, "bremsMin", "bremsMin:");

                breakLine(response);

                numberInput(response, settings.hardware.poti.bremsMax, "bremsMax", "bremsMax:");

                breakLine(response);

                submitButton(response);
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
            currentMode = &modes::defaultMode;
        else if (p->value() == "tempomatMode")
            currentMode = &modes::tempomatMode;
        else if (p->value() == "larsmMode")
            currentMode = &modes::larsmMode;
        else if (p->value() == "bluetoothMode")
            currentMode = &modes::bluetoothMode;
        else if (p->value() == "websocketMode")
            currentMode = &modes::websocketMode;
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
        settings.limits.iMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("iDcMax");
        settings.limits.iDcMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("nMotMax");
        settings.limits.nMotMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("fieldWeakMax");
        settings.limits.fieldWeakMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("phaseAdvMax");
        settings.limits.phaseAdvMax = strtol(p->value().c_str(), nullptr, 10);
    }

    settings.hardware.enableFrontLeft = request->hasParam("enableFrontLeft") && request->getParam("enableFrontLeft")->value() == "on";
    settings.hardware.enableFrontRight = request->hasParam("enableFrontRight") && request->getParam("enableFrontRight")->value() == "on";
    settings.hardware.enableBackLeft = request->hasParam("enableBackLeft") && request->getParam("enableBackLeft")->value() == "on";
    settings.hardware.enableBackRight = request->hasParam("enableBackRight") && request->getParam("enableBackRight")->value() == "on";

    settings.hardware.invertFrontLeft = request->hasParam("invertFrontLeft") && request->getParam("invertFrontLeft")->value() == "on";
    settings.hardware.invertFrontRight = request->hasParam("invertFrontRight") && request->getParam("invertFrontRight")->value() == "on";
    settings.hardware.invertBackLeft = request->hasParam("invertBackLeft") && request->getParam("invertBackLeft")->value() == "on";
    settings.hardware.invertBackRight = request->hasParam("invertBackRight") && request->getParam("invertBackRight")->value() == "on";

    request->redirect("/commonParams");
}

void WebHandler::handleSetDefaultModeParams(AsyncWebServerRequest *request)
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

    if (!request->hasParam("smoothing"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no smoothing specified");
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
            settings.defaultMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            settings.defaultMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            settings.defaultMode.ctrlTyp = ControlType::FieldOrientedControl;
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
            settings.defaultMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            settings.defaultMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            settings.defaultMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            settings.defaultMode.ctrlMod = ControlMode::Torque;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlMod");
            request->send(&response);
            return;
        }
    }

    settings.defaultMode.enableSmoothing = request->hasParam("enableSmoothing") && request->getParam("enableSmoothing")->value() == "on";

    {
        AsyncWebParameter* p = request->getParam("smoothing");

        settings.defaultMode.smoothing = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("frontPercentage");

        settings.defaultMode.frontPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("backPercentage");

        settings.defaultMode.backPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("add_schwelle");

        settings.defaultMode.add_schwelle = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas1_wert");

        settings.defaultMode.gas1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas2_wert");

        settings.defaultMode.gas2_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems1_wert");

        settings.defaultMode.brems1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems2_wert");

        settings.defaultMode.brems2_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    request->redirect("/defaultModeParams");
}

void WebHandler::handleSetTempomatModeParams(AsyncWebServerRequest *request)
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



    {
        AsyncWebParameter* p = request->getParam("pwm");

        modes::tempomatMode.pwm = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("ctrlTyp");

        if (p->value() == "Commutation")
            settings.tempomatMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            settings.tempomatMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            settings.tempomatMode.ctrlTyp = ControlType::FieldOrientedControl;
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
            settings.tempomatMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            settings.tempomatMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            settings.tempomatMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            settings.tempomatMode.ctrlMod = ControlMode::Torque;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlMod");
            request->send(&response);
            return;
        }
    }

    request->redirect("/tempomatModeParams");
}

void WebHandler::handleSetPotiParams(AsyncWebServerRequest *request)
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

        settings.hardware.poti.gasMin = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gasMax");

        settings.hardware.poti.gasMax = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("bremsMin");

        settings.hardware.poti.bremsMin = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("bremsMax");

        settings.hardware.poti.bremsMax = strtol(p->value().c_str(), nullptr, 10);
    }

    request->redirect("/potiParams");
}

void WebHandler::handleDisplay(AsyncWebServerRequest *request)
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
                HtmlTag a(response, "a", " href=\"/displayAction?action=rotaryUp\"");
                response.print("Up");
            }

            response.print(" - ");

            {
                HtmlTag a(response, "a", " href=\"/displayAction?action=rotaryDown\"");
                response.print("Down");
            }

            response.print(" - ");

            {
                HtmlTag a(response, "a", " href=\"/displayAction?action=button\"");
                response.print("Button");
            }

            if (auto menuDisplay = currentDisplay->asMenuDisplay())
            {
                {
                    HtmlTag h2(response, "h2");
                    response.print(menuDisplay->text());
                }

                HtmlTag ul(response, "ul");

                const auto menuBegin = menuDisplay->begin();
                const auto menuEnd = menuDisplay->end();
                const auto selectedIndex = menuDisplay->selectedIndex();
                for (auto iter = menuBegin; iter != menuEnd; iter++)
                {
                    HtmlTag li(response, "li", std::distance(menuBegin, iter)==selectedIndex?" style=\"border: 1px solid black;\"":"");
                    HtmlTag a(response, "a", String(" href=\"/displayAction?action=triggerItem&index=") + std::distance(menuDisplay->begin(), iter) + "\"");
                    response.print(iter->get().text());
                }
            }
            else if (auto changeValueDisplay = currentDisplay->asChangeValueDisplayInterface())
            {
                {
                    HtmlTag h2(response, "h2");
                    response.print(changeValueDisplay->text());
                }

                HtmlTag form(response, "form", " method=\"GET\" action=\"displayAction\"");

                hiddenInput(response, "changeValue", "action");

                numberInput(response, changeValueDisplay->shownValue(), "value", "Value:");

                {
                    HtmlTag button(response, "button", " type=\"submit\" name=\"subAction\" value=\"update\"");
                    response.print("Update");
                }
                {
                    HtmlTag button(response, "button", " type=\"submit\" name=\"subAction\" value=\"confirm\"");
                    response.print("Confirm");
                }
            }
            else
            {
                HtmlTag p(response, "p");
                response.print("No specialized controls available for current display.");
            }

            {
                HtmlTag a(response, "a", " href=\"/\"");
                response.print("Back");
            }
        }
    }

    request->send(&response);
}

void WebHandler::handleDisplayAction(AsyncWebServerRequest *request)
{
    if (!request->hasParam("action"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no action specified");
        request->send(&response);
        return;
    }

    AsyncWebParameter* action = request->getParam("action");
    if (action->value() == "rotaryUp")
    {
        InputDispatcher::rotate(-1);
        request->redirect("/display");
    }
    else if (action->value() == "rotaryDown")
    {
        InputDispatcher::rotate(1);
        request->redirect("/display");
    }
    else if (action->value() == "button")
    {
        InputDispatcher::button(true);
        InputDispatcher::button(false);
        request->redirect("/display");
    }
    else if (action->value() == "triggerItem")
    {
        if (auto menuDisplay = currentDisplay->asMenuDisplay())
        {
            if (!request->hasParam("index"))
            {
                AsyncResponseStream &response = *request->beginResponseStream("text/plain");
                response.setCode(400);
                response.print("no index specified");
                request->send(&response);
                return;
            }

            AsyncWebParameter* p = request->getParam("index");
            const auto index = strtol(p->value().c_str(), nullptr, 10);

            if (index < 0 || index >= std::distance(menuDisplay->begin(), menuDisplay->end()))
            {
                AsyncResponseStream &response = *request->beginResponseStream("text/plain");
                response.setCode(400);
                response.print("index out of range");
                request->send(&response);
                return;
            }

            (menuDisplay->begin() + index)->get().triggered();

            request->redirect("/display");
        }
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("current display isn't a menu display");
            request->send(&response);
            return;
        }
    }
    else if (action->value() == "changeValue")
    {
        if (auto changeDisplay = currentDisplay->asChangeValueDisplayInterface())
        {
            if (!request->hasParam("value"))
            {
                AsyncResponseStream &response = *request->beginResponseStream("text/plain");
                response.setCode(400);
                response.print("no value specified");
                request->send(&response);
                return;
            }
            if (!request->hasParam("subAction"))
            {
                AsyncResponseStream &response = *request->beginResponseStream("text/plain");
                response.setCode(400);
                response.print("no subAction specified");
                request->send(&response);
                return;
            }

            bool confirm;
            {
                AsyncWebParameter* p = request->getParam("subAction");
                if (p->value() == "update")
                    confirm = false;
                else if (p->value() == "confirm")
                    confirm = true;
                else
                {
                    AsyncResponseStream &response = *request->beginResponseStream("text/plain");
                    response.setCode(400);
                    response.print("invalid subAction specified");
                    request->send(&response);
                    return;
                }
            }

            AsyncWebParameter* p = request->getParam("value");
            const auto value = strtol(p->value().c_str(), nullptr, 10);

            changeDisplay->setShownValue(value);

            if (confirm)
                changeDisplay->confirm();

            request->redirect("/display");
        }
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("current display isn't a change display");
            request->send(&response);
            return;
        }
    }
    else
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("invalid action specified");
        request->send(&response);
        return;
    }
}

void WebHandler::handleReboot(AsyncWebServerRequest *request)
{
    AsyncResponseStream &response = *request->beginResponseStream("text/plain");
    response.print("Rebooting now");
    request->send(&response);

    ESP.restart();
}

struct {
    AsyncWebServer server{80};
    WebHandler handler;
} web;

void initWebserver()
{
    web.server.addHandler(&web.handler);
    web.server.begin();
}
}
