#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "demodisplay.h"
#include "actions/switchscreenaction.h"

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"
#include "label.h"
#include "progressbar.h"
#include "icons/alert.h"

namespace {
class MainMenu;
}

namespace {
class StatusDisplay : public DemoDisplay, public SwitchScreenAction<MainMenu>
{
    using Base = DemoDisplay;

public:
    void start() override;
    void redraw() override;

private:
    class BoardStatus
    {
    public:
        BoardStatus(int y) :
            m_y{y},
            m_labelLeftPwm{65, y}, // 80, 22
            m_labelRightPwm{155, y}, // 80, 22
            m_labelVoltage{30, y+25}, // 85, 22
            m_labelTemperature{150, y+25}, // 85, 22
            m_leftMotor{y+50},
            m_rightMotor{y+75}
        {}

        void start();
        void redraw(const Controller &controller);

    private:
        void drawWarning();

        class MotorStatus
        {
        public:
            MotorStatus(int y) :
                m_labelError{18, y}, // 18, 22,
                m_labelCurrent{40, y}, // 85, 22
                m_labelSpeed{135, y}, // 75, 22
                m_labelHallSensors{210, y} // 30, 15
            {}

            void start();
            void redraw(const MotorFeedback &motor);

        private:
            Label m_labelError;
            Label m_labelCurrent;
            Label m_labelSpeed;
            Label m_labelHallSensors;
        };

        const int m_y;

        bool m_lastFeedbackValid{};

        Label m_labelLeftPwm;
        Label m_labelRightPwm;

        Label m_labelVoltage;
        Label m_labelTemperature;

        MotorStatus m_leftMotor;
        MotorStatus m_rightMotor;
    };

    Label m_labelRawGas{45, 0}; // 40, 15
    Label m_labelGas{90, 0}; // 60, 15
    ProgressBar m_progressBarGas{150, 0, 90, 15, 0, 1000};

    Label m_labelRawBrems{45, 15}; // 40, 15
    Label m_labelBrems{90, 15}; // 60, 15
    ProgressBar m_progressBarBrems{150, 15, 90, 15, 0, 1000};

    BoardStatus m_frontStatus{42};
    BoardStatus m_backStatus{142};

    Label m_labelWifiStatus{35, 266}; // 120, 15
    Label m_labelLimit0{205, 266}; // 35, 15
    Label m_labelIpAddress{25, 281}; // 130, 15
    Label m_labelLimit1{205, 281}; // 35, 15
    Label m_labelPerformance{85, 296}; // 40, 15
    Label m_labelMode{165, 296}; // 75, 15
};

void StatusDisplay::start()
{
    Base::start();

    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(2);
    tft.setTextColor(TFT_WHITE);

    tft.drawString("gas", 0, 0);
    m_labelRawGas.start();
    m_labelGas.start();
    m_progressBarGas.start();
    tft.drawString("brems", 0, 15);
    m_labelRawBrems.start();
    m_labelBrems.start();
    m_progressBarBrems.start();

    m_frontStatus.start();
    m_backStatus.start();

    tft.setTextFont(2);
    tft.drawString("WiFi:", 0, 266);
    m_labelWifiStatus.start();
    tft.drawString("Limit0:", 160, 266);
    m_labelLimit0.start();
    tft.drawString("IP:", 0, 281);
    m_labelIpAddress.start();
    tft.drawString("Limit1:", 160, 281);
    m_labelLimit1.start();
    tft.drawString("Performance:", 0, 296);
    m_labelPerformance.start();
    tft.drawString("Mode:", 125, 296);
    m_labelMode.start();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void StatusDisplay::redraw()
{
    tft.setTextFont(2);
    m_labelRawGas.redraw(String{raw_gas});
    m_labelGas.redraw(String{gas});
    m_progressBarGas.redraw(gas);
    m_labelRawBrems.redraw(String{raw_brems});
    m_labelBrems.redraw(String{brems});
    m_progressBarBrems.redraw(brems);

    m_frontStatus.redraw(front);
    m_backStatus.redraw(back);

    tft.setTextFont(2);
    m_labelWifiStatus.redraw(toString(WiFi.status()));
    m_labelLimit0.redraw(String{front.command.left.iMotMax} + "A");
    m_labelIpAddress.redraw(WiFi.localIP().toString());
    m_labelLimit1.redraw(String{front.command.left.iDcMax} + "A");
    m_labelPerformance.redraw(String{performance.last});
    m_labelMode.redraw(currentMode->displayName());
}

void StatusDisplay::BoardStatus::start()
{
    tft.setTextFont(4);
    tft.drawString("pwm:", 0, m_y);
    m_labelLeftPwm.start();
    m_labelRightPwm.start();
    drawWarning();
}

void StatusDisplay::BoardStatus::redraw(const Controller &controller)
{
    tft.setTextFont(4);

    m_labelLeftPwm.redraw(String{controller.command.left.pwm});
    m_labelRightPwm.redraw(String{controller.command.right.pwm});

    if (controller.feedbackValid != m_lastFeedbackValid)
    {
        tft.fillRect(0, m_y+25, tft.width(), 75, TFT_BLACK);

        if (controller.feedbackValid)
        {
            tft.setTextColor(TFT_WHITE);

            tft.drawString("U=", 0, m_y+25, 4);
            m_labelVoltage.start();
            tft.drawString("T=", 120, m_y+25, 4);
            m_labelTemperature.start();
            tft.drawString("l:", 0, m_y+50, 4);
            m_leftMotor.start();
            tft.drawString("r:", 0, m_y+75, 4);
            m_rightMotor.start();

            tft.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        else
            drawWarning();

        m_lastFeedbackValid = controller.feedbackValid;
    }

    if (controller.feedbackValid)
    {
        m_labelVoltage.redraw(String{fixBatVoltage(controller.feedback.batVoltage)} + 'V');
        m_labelTemperature.redraw(String{fixBoardTemp(controller.feedback.boardTemp)} + 'C');
        m_leftMotor.redraw(controller.feedback.left);
        m_rightMotor.redraw(controller.feedback.right);
    }
}

void StatusDisplay::BoardStatus::drawWarning()
{
    tft.setTextColor(TFT_RED);
    tft.drawString("No data!", 60, m_y+50, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setSwapBytes(true);
    tft.pushImage(10, m_y+40, icons::alert.WIDTH, icons::alert.HEIGHT, icons::alert.buffer);
    tft.setSwapBytes(false);
}

void StatusDisplay::BoardStatus::MotorStatus::start()
{
    m_labelError.start();
    m_labelCurrent.start();
    m_labelSpeed.start();
    m_labelHallSensors.start();
}

void StatusDisplay::BoardStatus::MotorStatus::redraw(const MotorFeedback &motor)
{
    tft.setTextFont(4);
    tft.setTextColor(motor.error?TFT_RED:TFT_GREEN, TFT_BLACK);
    m_labelError.redraw(String{motor.error});
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_labelCurrent.redraw(String{fixCurrent(motor.current)} + 'A');
    m_labelSpeed.redraw(String{convertToKmh(motor.speed)});

    tft.setTextFont(2);
    m_labelHallSensors.redraw(hallString(motor));

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}
}
