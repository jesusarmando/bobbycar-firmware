#pragma once

#include <cstdint>

#include "../../common.h"

#include "modebase.h"
#include "utils.h"
#include "defaultmode.h"

namespace {
class ManualMode final : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override {};
    void update() override;
    void stop() override {};

    const char *displayName() const override { return "Manual"; }

    bool potiControl = true;
    int16_t pwm = 0;
    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Speed;
};

namespace modes {
ManualMode manualMode;
}

void ManualMode::update()
{
    if (potiControl)
    {
        if (gas > 500. && brems > 500.)
        {
            pwm = 0;
            modes::defaultMode.waitForGasLoslass = true;
            modes::defaultMode.waitForBremsLoslass = true;
            currentMode = &modes::defaultMode;
            return;
        }

        pwm += (gas/1000.) - (brems/1000.);
    }

    for (auto &controller : controllers)
    {
        auto &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm;
        }
    }
    fixCommonParams();

    sendCommands();
}
}
