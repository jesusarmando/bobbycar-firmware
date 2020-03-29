#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "demodisplay.h"

#include "modebase.h"
#include "globals.h"
#include "utils.h"
#include "label.h"
#include "progressbar.h"

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

    Label<45, 0, 40, 15, 2> m_labelRawGas;
    Label<90, 0, 60, 15, 2> m_labelGas;
    ProgressBar<150, 0, 90, 15, 0, 1000> m_progressBarGas;

    Label<45, 15, 40, 15, 2> m_labelRawBrems;
    Label<90, 15, 60, 15, 2> m_labelBrems;
    ProgressBar<150, 15, 90, 15, 0, 1000> m_progressBarBrems;

    template<int y>
    class BoardStatus
    {
    public:
        void start();
        void redraw(Controller &controller);

    private:
        Label<65, y, 80, 25, 4> m_labelLeftPwm;
        Label<155, y, 80, 25, 4> m_labelRightPwm;
    };

    BoardStatus<42> m_frontStatus;
    BoardStatus<142> m_backStatus;

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
    m_labelRawGas.start();
    m_labelGas.start();
    m_progressBarGas.start();
    tft.drawString("brems", 0, 15, 2);
    m_labelRawBrems.start();
    m_labelBrems.start();
    m_progressBarBrems.start();

    m_frontStatus.start();
    m_backStatus.start();

    tft.drawString("WiFi:", 0, 266, 2);
    m_labelWifiStatus.start();
    tft.drawString("Limit0:", 160, 266, 2);
    m_labelLimit0.start();
    tft.drawString("IP:", 0, 281, 2);
    m_labelIpAddress.start();
    tft.drawString("Limit1:", 160, 281, 2);
    m_labelLimit1.start();
    tft.drawString("Performance:", 0, 296, 2);
    m_labelPerformance.start();
    tft.drawString("Mode:", 125, 296, 2);
    m_labelMode.start();
}

template<typename Tscreen>
void StatusDisplay<Tscreen>::update()
{
    const auto now = millis();
    if (!m_lastRedraw || now-m_lastRedraw >= 1000/20)
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
    m_progressBarGas.repaint(gas);
    m_labelRawBrems.repaint(String{raw_brems});
    m_labelBrems.repaint(String{brems});
    m_progressBarBrems.repaint(brems);

    m_frontStatus.redraw(front);
    m_backStatus.redraw(back);

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

template<typename Tscreen> template<int y>
void StatusDisplay<Tscreen>::BoardStatus<y>::start()
{
    tft.drawString("pwm:", 0, y, 4);
    m_labelLeftPwm.start();
    m_labelRightPwm.start();
}

template<typename Tscreen> template<int y>
void StatusDisplay<Tscreen>::BoardStatus<y>::redraw(Controller &controller)
{
    m_labelLeftPwm.repaint(String{controller.command.left.pwm});
    m_labelRightPwm.repaint(String{controller.command.right.pwm});
}
