#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "demodisplay.h"

#include "modebase.h"
#include "globals.h"
#include "utils.h"
#include "label.h"

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
    void redraw();

    Label<50, 0, 75, 15, 2> m_labelRawGas;
    Label<150, 0, 75, 15, 2> m_labelGas;
    Label<50, 15, 75, 15, 2> m_labelRawBrems;
    Label<150, 15, 75, 15, 2> m_labelBrems;

    Label<65, 42, 80, 25, 4> m_labelFrontLeftPwm;
    Label<155, 42, 80, 25, 4> m_labelFrontRightPwm;

    Label<65, 142, 80, 25, 4> m_labelBackLeftPwm;
    Label<155, 142, 80, 25, 4> m_labelBackRightPwm;

    Label<35, 266, 120, 15, 2> m_labelWifiStatus;
    Label<205, 266, 35, 15, 2> m_labelLimit0;
    Label<25, 281, 130, 15, 2> m_labelIpAddress;
    Label<205, 281, 35, 15, 2> m_labelLimit1;
    Label<85, 296, 40, 15, 2> m_labelPerformance;
    Label<165, 296, 75, 15, 2> m_labelMode;

    unsigned long m_lastRedraw{};
};

template<typename Tscreen>
void StatusDisplay<Tscreen>::start()
{
    DemoDisplay<Tscreen>::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("gas", 0, 0, 2);
    tft.drawString("brems", 0, 15, 2);

    tft.drawString("pwm:", 0, 42, 4);

    tft.drawString("pwm:", 0, 142, 4);

    tft.drawString("WiFi:", 0, 266, 2);
    tft.drawString("Limit0:", 160, 266, 2);
    tft.drawString("IP:", 0, 281, 2);
    tft.drawString("Limit1:", 160, 281, 2);
    tft.drawString("Performance:", 0, 296, 2);
    tft.drawString("Mode:", 125, 296, 2);
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
void StatusDisplay<Tscreen>::redraw()
{
    m_labelRawGas.repaint(String{raw_gas});
    m_labelGas.repaint(String{gas});
    m_labelRawBrems.repaint(String{raw_brems});
    m_labelBrems.repaint(String{brems});

    m_labelFrontLeftPwm.repaint(String{front.command.left.pwm});
    m_labelFrontRightPwm.repaint(String{front.command.right.pwm});
    m_labelBackLeftPwm.repaint(String{back.command.left.pwm});
    m_labelBackRightPwm.repaint(String{back.command.right.pwm});

    auto &renderer = tft;

    int y = 42;
    const auto print_controller = [&](const Controller &controller)
    {
        y+=25;
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

    m_labelWifiStatus.repaint(toString(WiFi.status()));
    m_labelLimit0.repaint(String{front.command.left.iMotMax} + "A");
    m_labelIpAddress.repaint(WiFi.localIP().toString());
    m_labelLimit1.repaint(String{front.command.left.iDcMax} + "A");
    m_labelPerformance.repaint(String{performance.last});
    m_labelMode.repaint(currentMode->displayName());
}
}
