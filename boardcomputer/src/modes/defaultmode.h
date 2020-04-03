#pragma once

#include <cstdint>

#include <Arduino.h>

#include "modebase.h"
#include "../../common.h"
#include "globals.h"
#include "utils.h"

namespace {
class DefaultMode final : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override;

    const char *displayName() const override { return "Default"; }

    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Torque;
    bool enableWeakeningSmoothening{true};
    int16_t weakeningSmoothening{20};
    int16_t frontPercentage{100}, backPercentage{100};

    int16_t add_schwelle;
    int16_t gas1_wert;
    int16_t gas2_wert;
    int16_t brems1_wert;
    int16_t brems2_wert;

    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};
    unsigned long lastTime{millis()};
    float lastPwm{0};
};

namespace modes {
DefaultMode defaultMode;
}

void DefaultMode::update()
{
    if (waitForGasLoslass)
    {
        if (gas < 50)
            waitForGasLoslass = false;
        else
            gas = 0;
    }
    const auto gas_squared = (gas * gas) / 1000;

    if (waitForBremsLoslass)
    {
        if (brems < 50)
            waitForBremsLoslass = false;
        else
            brems = 0;
    }
    const auto brems_squared = (brems * brems) / 1000;

    const auto now = millis();

    float pwm;
    if (gas_squared >= add_schwelle)
    {
        pwm = (gas_squared/1000.*gas1_wert) + (brems_squared/1000.*brems1_wert);

        if (enableWeakeningSmoothening && (pwm > 1000. || lastPwm > 1000.))
        {
            if (lastPwm < pwm)
            {
                pwm = std::min(pwm, lastPwm+(weakeningSmoothening*(now-lastTime)/100.f));
                if (pwm < 1000.)
                    pwm = 1000.;
            }
            else if (lastPwm > pwm)
            {
                pwm = std::max(pwm, lastPwm-(weakeningSmoothening*(now-lastTime)/100.f));
            }
        }
    }
    else
        pwm = (gas_squared/1000.*gas2_wert) - (brems_squared/1000.*brems2_wert);

    lastPwm = pwm;
    lastTime = now;

    for (Controller &controller : controllers)
    {
        Command &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm / 100. * (&controller == &controllers[0] ? frontPercentage : backPercentage);
        }
    }

    fixCommonParams();

    sendCommands();
}
}
