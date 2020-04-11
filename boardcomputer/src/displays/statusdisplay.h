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
template<int y>
class MotorStatus
{
public:
    void start();
    void redraw(const MotorFeedback &motor);

private:
    Label<18, y, 18, 22, 4> m_labelError;
    Label<40, y, 85, 22, 4> m_labelCurrent;
    Label<135, y, 75, 22, 4> m_labelSpeed;
    Label<210, y, 30, 15, 2> m_labelHallSensors;
};

template<int y>
class BoardStatus
{
public:
    void start();
    void redraw(const Controller &controller);

private:
    void drawWarning();

    bool m_lastFeedbackValid{};

    Label<65, y, 80, 22, 4> m_labelLeftPwm;
    Label<155, y, 80, 22, 4> m_labelRightPwm;

    Label<30, y+25, 85, 22, 4> m_labelVoltage;
    Label<150, y+25, 85, 22, 4> m_labelTemperature;

    MotorStatus<y+50> m_leftMotor;
    MotorStatus<y+75> m_rightMotor;
};

template<typename Tscreen>
class StatusDisplay final : public DemoDisplay<Tscreen>
{
    using Base = DemoDisplay<Tscreen>;

public:
    void start() override;
    void redraw() override;

private:
    Label<45, 0, 40, 15, 2> m_labelRawGas;
    Label<90, 0, 60, 15, 2> m_labelGas;
    ProgressBar<150, 0, 90, 15, 0, 1000> m_progressBarGas;

    Label<45, 15, 40, 15, 2> m_labelRawBrems;
    Label<90, 15, 60, 15, 2> m_labelBrems;
    ProgressBar<150, 15, 90, 15, 0, 1000> m_progressBarBrems;

    BoardStatus<42> m_frontStatus;
    BoardStatus<142> m_backStatus;

    Label<35, 266, 120, 15, 2> m_labelWifiStatus;
    Label<205, 266, 35, 15, 2> m_labelLimit0;
    Label<25, 281, 130, 15, 2> m_labelIpAddress;
    Label<205, 281, 35, 15, 2> m_labelLimit1;
    Label<85, 296, 40, 15, 2> m_labelPerformance;
    Label<165, 296, 75, 15, 2> m_labelMode;
};

template<typename Tscreen>
void StatusDisplay<Tscreen>::start()
{
    Base::start();

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);

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

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

template<typename Tscreen>
void StatusDisplay<Tscreen>::redraw()
{
    m_labelRawGas.redraw(String{raw_gas});
    m_labelGas.redraw(String{gas});
    m_progressBarGas.redraw(gas);
    m_labelRawBrems.redraw(String{raw_brems});
    m_labelBrems.redraw(String{brems});
    m_progressBarBrems.redraw(brems);

    m_frontStatus.redraw(front);
    m_backStatus.redraw(back);

    m_labelWifiStatus.redraw(toString(WiFi.status()));
    m_labelLimit0.redraw(String{front.command.left.iMotMax} + "A");
    m_labelIpAddress.redraw(WiFi.localIP().toString());
    m_labelLimit1.redraw(String{front.command.left.iDcMax} + "A");
    m_labelPerformance.redraw(String{performance.last});
    m_labelMode.redraw(currentMode->displayName());
}

template<int y>
void BoardStatus<y>::start()
{
    tft.drawString("pwm:", 0, y, 4);
    m_labelLeftPwm.start();
    m_labelRightPwm.start();
    drawWarning();
}

template<int y>
void BoardStatus<y>::redraw(const Controller &controller)
{
    m_labelLeftPwm.redraw(String{controller.command.left.pwm});
    m_labelRightPwm.redraw(String{controller.command.right.pwm});

    if (controller.feedbackValid != m_lastFeedbackValid)
    {
        tft.fillRect(0, y+25, tft.width(), 75, TFT_BLACK);

        if (controller.feedbackValid)
        {
            tft.setTextColor(TFT_WHITE);

            tft.drawString("U=", 0, y+25, 4);
            m_labelVoltage.start();
            tft.drawString("T=", 120, y+25, 4);
            m_labelTemperature.start();
            tft.drawString("l:", 0, y+50, 4);
            m_leftMotor.start();
            tft.drawString("r:", 0, y+75, 4);
            m_rightMotor.start();

            tft.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        else
            drawWarning();

        m_lastFeedbackValid = controller.feedbackValid;
    }

    if (controller.feedbackValid)
    {
        m_labelVoltage.redraw(String{controller.feedback.batVoltage/100.} + 'V');
        m_labelTemperature.redraw(String{controller.feedback.boardTemp/10.} + 'C');
        m_leftMotor.redraw(controller.feedback.left);
        m_rightMotor.redraw(controller.feedback.right);
    }
}

template<int y>
void BoardStatus<y>::drawWarning()
{
    tft.setTextColor(TFT_RED);
    tft.drawString("No data!", 60, y+50, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setSwapBytes(true);
    tft.pushImage(10, y+40, alertWidth, alertHeight, alert);
    tft.setSwapBytes(false);
}

template<int y>
void MotorStatus<y>::start()
{
    m_labelError.start();
    m_labelCurrent.start();
    m_labelSpeed.start();
    m_labelHallSensors.start();
}

template<int y>
void MotorStatus<y>::redraw(const MotorFeedback &motor)
{
    tft.setTextColor(motor.error?TFT_RED:TFT_GREEN, TFT_BLACK);
    m_labelError.redraw(String{motor.error});
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_labelCurrent.redraw(String{std::abs(motor.current/50.)} + 'A');
    m_labelSpeed.redraw(String{convertToKmh(motor.speed)}); //
    m_labelHallSensors.redraw(String{} + (motor.hallA ? '1' : '0') + (motor.hallB ? '1' : '0') + (motor.hallC ? '1' : '0'));

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}
}
