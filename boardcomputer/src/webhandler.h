#pragma once

#include <ESPAsyncWebServer.h>

#include "htmlutils.h"
#include "globals.h"
#include "settings.h"

#include "displays/statusdisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"

#include "modes/defaultmode.h"
#include "modes/manualmode.h"
#include "modes/bluetoothmode.h"

namespace {
class WebHandler : public AsyncWebHandler
{
public:
    using AsyncWebHandler::AsyncWebHandler;

    bool canHandle(AsyncWebServerRequest *request) override;

    void handleRequest(AsyncWebServerRequest *request) override;
};

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

            {
                HtmlTag form(response, "form", " action=\"/setScreenParams\"");

                HtmlTag fieldset(response, "fieldset");

                {
                    HtmlTag legend(response, "display");
                    response.print("Current display:");
                }

                {
                    HtmlTag select(response, "select", " id=\"display\" name=\"display\" required");
                    selectOption(response, "status", displays::status.displayName(), currentDisplay==&displays::status);
                    selectOption(response, "starfield", displays::starfield.displayName(), currentDisplay==&displays::starfield);
                    selectOption(response, "pingPong", displays::pingPong.displayName(), currentDisplay==&displays::pingPong);
                    selectOption(response, "spiro", displays::spiro.displayName(), currentDisplay==&displays::spiro);
                }

                breakLine(response);

                {
                    HtmlTag legend(response, "legend");
                    response.print("Screen params:");
                }

                numberInput(response, displays::status.framerate(), "framerate", "Status framerate:");

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

    if (!request->hasParam("display"))
    {
        AsyncResponseStream &response = *request->beginResponseStream("text/plain");
        response.setCode(400);
        response.print("no display specified");
        request->send(&response);
        return;
    }



    {
        AsyncWebParameter* p = request->getParam("framerate");

        displays::status.setFramerate(strtol(p->value().c_str(), nullptr, 10));
    }

    {
        AsyncWebParameter* p = request->getParam("display");

        if (p->value() == "status")
        {
            currentDisplay->stop();
            currentDisplay = &displays::status;
            currentDisplay->start();
        }
        else if (p->value() == "starfield")
        {
            currentDisplay->stop();
            currentDisplay = &displays::starfield;
            currentDisplay->start();
        }
        else if (p->value() == "pingPong")
        {
            currentDisplay->stop();
            currentDisplay = &displays::pingPong;
            currentDisplay->start();
        }
        else if (p->value() == "spiro")
        {
            currentDisplay->stop();
            currentDisplay = &displays::spiro;
            currentDisplay->start();
        }
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid display");
            request->send(&response);
            return;
        }
    }

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
                    selectOption(response, "defaultMode", modes::defaultMode.displayName(), currentMode==&modes::defaultMode);
                    selectOption(response, "manualMode", modes::manualMode.displayName(), currentMode==&modes::manualMode);
                    selectOption(response, "bluetoothMode", modes::bluetoothMode.displayName(), currentMode==&modes::bluetoothMode);
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

                checkboxInput(response, front.left.enable, "enableFrontLeft", "Enable front left:");

                breakLine(response);

                checkboxInput(response, front.right.enable, "enableFrontRight", "Enable front right:");

                breakLine(response);

                checkboxInput(response, back.left.enable, "enableBackLeft", "Enable back left:");

                breakLine(response);

                checkboxInput(response, back.right.enable, "enableBackRight", "Enable back right:");

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
                    selectOption(response, "Commutation", "Commutation", modes::defaultMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", modes::defaultMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", modes::defaultMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod1", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod1\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", modes::defaultMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", modes::defaultMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", modes::defaultMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", modes::defaultMode.ctrlMod == ControlMode::Torque);
                }

                breakLine(response);

                checkboxInput(response, modes::defaultMode.enableWeakeningSmoothening, "enableWeakeningSmoothening", "Enable Weakening Smoothening:");

                breakLine(response);

                numberInput(response, modes::defaultMode.weakeningSmoothening, "weakeningSmoothening", "Weakening Smoothening:");

                breakLine(response);

                numberInput(response, modes::defaultMode.frontPercentage, "frontPercentage", "Front percentage:");

                breakLine(response);

                numberInput(response, modes::defaultMode.backPercentage, "backPercentage", "Back percentage:");

                breakLine(response);

                numberInput(response, modes::defaultMode.add_schwelle, "add_schwelle", "add_schwelle:");

                breakLine(response);

                numberInput(response, modes::defaultMode.gas1_wert, "gas1_wert", "gas1_wert:");

                breakLine(response);

                numberInput(response, modes::defaultMode.gas2_wert, "gas2_wert", "gas2_wert:");

                breakLine(response);

                numberInput(response, modes::defaultMode.brems1_wert, "brems1_wert", "brems1_wert:");

                breakLine(response);

                numberInput(response, modes::defaultMode.brems2_wert, "brems2_wert", "brems2_wert:");

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

                checkboxInput(response, modes::manualMode.potiControl, "potiControl", "Poti control:");

                breakLine(response);

                numberInput(response, modes::manualMode.pwm, "pwm", "Pwm:");

                breakLine(response);

                label(response, "ctrlTyp2", "Control Type:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlTyp2\" name=\"ctrlTyp\" required");
                    selectOption(response, "Commutation", "Commutation", modes::manualMode.ctrlTyp == ControlType::Commutation);
                    selectOption(response, "Sinusoidal", "Sinusoidal", modes::manualMode.ctrlTyp == ControlType::Sinusoidal);
                    selectOption(response, "FieldOrientedControl", "Field Oriented Control", modes::manualMode.ctrlTyp == ControlType::FieldOrientedControl);
                }

                breakLine(response);

                label(response, "ctrlMod2", "Control Mode:");

                breakLine(response);

                {
                    HtmlTag select(response, "select", " id=\"ctrlMod2\" name=\"ctrlMod\" required");

                    selectOption(response, "OpenMode", "Open Mode", modes::manualMode.ctrlMod == ControlMode::OpenMode);
                    selectOption(response, "Voltage", "Voltage", modes::manualMode.ctrlMod == ControlMode::Voltage);
                    selectOption(response, "Speed", "Speed", modes::manualMode.ctrlMod == ControlMode::Speed);
                    selectOption(response, "Torque", "Torque", modes::manualMode.ctrlMod == ControlMode::Torque);
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
            currentMode->stop();
            currentMode = &modes::defaultMode;
            currentMode->start();
        }
        else if (p->value() == "manualMode")
        {
            currentMode->stop();
            currentMode = &modes::manualMode;
            currentMode->start();
        }
        else if (p->value() == "bluetoothMode")
        {
            currentMode->stop();
            currentMode = &modes::bluetoothMode;
            currentMode->start();
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

    front.left.enable = request->hasParam("enableFrontLeft") && request->getParam("enableFrontLeft")->value() == "on";
    front.right.enable = request->hasParam("enableFrontRight") && request->getParam("enableFrontRight")->value() == "on";
    back.left.enable = request->hasParam("enableBackLeft") && request->getParam("enableBackLeft")->value() == "on";
    back.right.enable = request->hasParam("enableBackRight") && request->getParam("enableBackRight")->value() == "on";

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
            modes::defaultMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            modes::defaultMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            modes::defaultMode.ctrlTyp = ControlType::FieldOrientedControl;
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
            modes::defaultMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            modes::defaultMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            modes::defaultMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            modes::defaultMode.ctrlMod = ControlMode::Torque;
        else
        {
            AsyncResponseStream &response = *request->beginResponseStream("text/plain");
            response.setCode(400);
            response.print("invalid ctrlMod");
            request->send(&response);
            return;
        }
    }

    modes::defaultMode.enableWeakeningSmoothening = request->hasParam("enableWeakeningSmoothening") && request->getParam("enableWeakeningSmoothening")->value() == "on";

    {
        AsyncWebParameter* p = request->getParam("weakeningSmoothening");

        modes::defaultMode.weakeningSmoothening = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("frontPercentage");

        modes::defaultMode.frontPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("backPercentage");

        modes::defaultMode.backPercentage = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("add_schwelle");

        modes::defaultMode.add_schwelle = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas1_wert");

        modes::defaultMode.gas1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("gas2_wert");

        modes::defaultMode.gas2_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems1_wert");

        modes::defaultMode.brems1_wert = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("brems2_wert");

        modes::defaultMode.brems2_wert = strtol(p->value().c_str(), nullptr, 10);
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



    modes::manualMode.potiControl = request->hasParam("potiControl") && request->getParam("potiControl")->value() == "on";

    {
        AsyncWebParameter* p = request->getParam("pwm");

        modes::manualMode.pwm = strtol(p->value().c_str(), nullptr, 10);
    }

    {
        AsyncWebParameter* p = request->getParam("ctrlTyp");

        if (p->value() == "Commutation")
            modes::manualMode.ctrlTyp = ControlType::Commutation;
        else if (p->value() == "Sinusoidal")
            modes::manualMode.ctrlTyp = ControlType::Sinusoidal;
        else if (p->value() == "FieldOrientedControl")
            modes::manualMode.ctrlTyp = ControlType::FieldOrientedControl;
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
            modes::manualMode.ctrlMod = ControlMode::OpenMode;
        else if (p->value() == "Voltage")
            modes::manualMode.ctrlMod = ControlMode::Voltage;
        else if (p->value() == "Speed")
            modes::manualMode.ctrlMod = ControlMode::Speed;
        else if (p->value() == "Torque")
            modes::manualMode.ctrlMod = ControlMode::Torque;
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
}