#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "display.h"
#include "modebase.h"
#include "globals.h"
#include "utils.h"

namespace {
#include "sprites/alert.h"
}

namespace {
class StatusDisplay final : public Display
{
public:
    void start() override;
    void redraw() override;
    void stop() override;

    int framerate() const override { return m_framerate; }
    void setFramerate(int framerate) { m_framerate = framerate; }

    const char *displayName() const override { return "Status"; }

    void button(bool pressed) override;

private:
    int m_framerate{2};
};

namespace displays {
StatusDisplay status;
}

void StatusDisplay::start()
{
    Serial.println("StatusDisplay::start()");
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(0);
}

void StatusDisplay::redraw()
{
    int y = 0;

    auto &renderer = tft;

    renderer.drawString(String("gas=") + raw_gas + " -> " + gas + "                                                ",0,y,2); y+=15;
    renderer.drawString(String("brems=") + raw_brems + " -> " + brems + "                                                ",0,y,2); y+=15;

    y+=12;

    const auto print_controller = [&](const Controller &controller)
    {
        renderer.drawString(String("pwm: ") + controller.command.left.pwm + ", " + controller.command.right.pwm + "                                                ", 0,y,4); y+=25;
        renderer.fillRect(0, y, renderer.width(), 75, TFT_BLACK);
        if (!controller.feedbackValid)
        {
            renderer.setTextColor(TFT_RED, TFT_BLACK);
            renderer.drawString("No data!", 60, y+25, 4);
            renderer.setTextColor(TFT_WHITE, TFT_BLACK);

            renderer.setSwapBytes(true);
            renderer.pushImage(10, y+15, alertWidth, alertHeight, alert);
            renderer.setSwapBytes(false);

            y+=75;
        }
        else
        {
            renderer.drawString(String("U=") + (controller.feedback.batVoltage/100.) + "V, T=" + (controller.feedback.boardTemp/10.) + "C",0,y,4); y+=25;
            const auto print_motor = [&](const char *pre, const MotorFeedback &motor)
            {
                renderer.drawString(pre, 0, y, 4);
                if (motor.error)
                    renderer.setTextColor(TFT_RED, TFT_BLACK);
                else
                    renderer.setTextColor(TFT_GREEN, TFT_BLACK);
                renderer.drawString(String() + motor.error + "   ", 15, y, 4);
                renderer.setTextColor(TFT_WHITE, TFT_BLACK);
                renderer.drawString(String("") + std::abs(motor.current/50.) + "A"
                                       "    " +
                                       (motor.speed/32.133),45,y,4);

                renderer.drawString(String("") +
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

    renderer.drawString("WiFi: " + toString(WiFi.status()) + "                                                ",0,y,2);
    renderer.drawString(String("Limit0: ") + front.command.left.iMotMax + "A", 160, y, 2); y+=15;
    renderer.drawString("IP: " + WiFi.localIP().toString() + "                                                ",0,y,2);
    renderer.drawString(String("Limit1: ") + front.command.left.iDcMax + "A", 160, y, 2); y+=15;
    renderer.drawString(String("Performance: ") + performance.last + "                                                ",0,y,2);
    renderer.drawString(String("Mode: ") + currentMode->displayName(), 125, y, 2); y+=15;
}

void StatusDisplay::stop()
{
    Serial.println("StatusDisplay::stop()");
}
}
