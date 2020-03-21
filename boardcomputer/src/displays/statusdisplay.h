#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "display.h"
#include "modebase.h"
#include "globals.h"
#include "utils.h"

namespace {
class StatusDisplay : public Display
{
public:
    void start() override;
    void update() override;
    void stop() override;

    int framerate() const override { return m_framerate; }
    void setFramerate(int framerate) { m_framerate = framerate; }

private:
    int m_framerate{2};
};

void StatusDisplay::start()
{
    Serial.println("StatusDisplay::start()");
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void StatusDisplay::update()
{
    Serial.println("StatusDisplay::update()");
    int y = 0;

    tft.drawString(String("gas=") + raw_gas + " -> " + gas + "                                                ",0,y,2); y+=15;
    tft.drawString(String("brems=") + raw_brems + " -> " + brems + "                                                ",0,y,2); y+=15;

    y+=12;

    const auto print_controller = [&](const Controller &controller)
    {
        tft.drawString(String("pwm: ") + controller.command.left.pwm + ", " + controller.command.right.pwm + "                                                ", 0,y,4); y+=25;
        if (millis() - controller.lastFeedback > 1000)
        {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.drawString("Dead!                                                ",0,y,4); y+=25;
            tft.drawString("                                                     ",0,y,4); y+=25;
            tft.drawString("                                                     ",0,y,4); y+=25;
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        else
        {
            tft.drawString(String("U=") + (controller.feedback.batVoltage/100.) + "V, T=" + (controller.feedback.boardTemp/10.) + "C                                                 ",0,y,4); y+=25;
            const auto print_motor = [&](const char *pre, const MotorFeedback &motor)
            {
                tft.drawString(pre, 0, y, 4);
                if (motor.error)
                    tft.setTextColor(TFT_RED, TFT_BLACK);
                else
                    tft.setTextColor(TFT_GREEN, TFT_BLACK);
                tft.drawString(String() + motor.error + "   ", 15, y, 4);
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
                tft.drawString(String("") + std::abs(motor.current/50.) + "A"
                                       "    " +
                                       (motor.speed/32.133) +
                                       "                                                ",45,y,4);

                tft.drawString(String("") +
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

    tft.drawString("WiFi: " + toString(WiFi.status()) + "                                                ",0,y,2);
    tft.drawString(String("Limit0: ") + front.controller.command.left.iMotMax + "A", 160, y, 2); y+=15;
    tft.drawString("IP: " + WiFi.localIP().toString() + "                                                ",0,y,2);
    tft.drawString(String("Limit1: ") + front.controller.command.left.iDcMax + "A", 160, y, 2); y+=15;
    tft.drawString(String("Performance: ") + performance.last + "                                                ",0,y,2);
    tft.drawString("Mode: " + currentMode->displayName(), 125, y, 2); y+=15;
}

void StatusDisplay::stop()
{
    Serial.println("StatusDisplay::stop()");
}
}
