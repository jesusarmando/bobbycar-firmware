#pragma once

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"

#include "../../common.h"

namespace {
class IgnoreInputMode : public ModeInterface
{
public:
    IgnoreInputMode(int16_t pwm, ControlType ctrlTyp, ControlMode ctrlMod) :
        m_pwm{pwm}, m_ctrlTyp{ctrlTyp}, m_ctrlMod{ctrlMod}
    {
    }

    void update() override;

    const char *displayName() const override { return "IgnoreInput"; }

private:
    const int16_t m_pwm;
    const ControlType m_ctrlTyp;
    const ControlMode m_ctrlMod;
};

void IgnoreInputMode::update()
{
    for (MotorState &motor : motors())
    {
        motor.ctrlTyp = m_ctrlTyp;
        motor.ctrlMod = m_ctrlMod;
        motor.pwm = m_pwm;
    }

    fixCommonParams();

    sendCommands();
}
}
