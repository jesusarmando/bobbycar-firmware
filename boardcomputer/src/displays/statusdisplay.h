#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "demodisplay.h"

#include "modebase.h"
#include "globals.h"
#include "utils.h"

namespace {
#include "sprites/alert.h"
}

namespace {
template<typename Tscreen>
class StatusDisplay final : public DemoDisplay<Tscreen>
{
public:
    void start() override;
    void update() override;

private:
    void redraw() const;

    unsigned long m_lastRedraw{};
};

template<typename Tscreen>
void StatusDisplay<Tscreen>::start()
{
    DemoDisplay<Tscreen>::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

template<typename Tscreen>
void StatusDisplay<Tscreen>::update()
{
    const auto now = millis();
    if (!m_lastRedraw || now-m_lastRedraw >= 1000/2)
    {
        redraw();
        m_lastRedraw = now;
    }

    DemoDisplay<Tscreen>::update();
}

template<typename Tscreen>
void StatusDisplay<Tscreen>::redraw() const
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
}
