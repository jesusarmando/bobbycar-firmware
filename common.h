#pragma once

#include <stdint.h>

#include "config.h"

namespace {

struct MotorConfiguration
{
    int16_t enable = false;
    int16_t pwm = 0;
    int16_t ctrlTyp = CTRL_TYP_SEL;
    int16_t ctrlMod = CTRL_MOD_REQ;
    int16_t iMotMax = I_MOT_MAX;
    int16_t iDcMax = I_DC_MAX;
    int16_t nMotMax = N_MOT_MAX;
    int16_t fieldWeakMax = FIELD_WEAK_MAX;
    int16_t phaseAdvMax = PHASE_ADV_MAX;
};

struct BuzzerConfiguration
{
    uint8_t freq = 0;
    uint8_t pattern = 0;
};

struct Command
{
    static constexpr uint16_t VALID_HEADER = 0xAAAA;
    static constexpr uint16_t INVALID_HEADER = 0xFFFF;

    uint16_t start;

    MotorConfiguration left, right;

    BuzzerConfiguration buzzer;

    int16_t poweroff = 0;

    uint16_t checksum;
};

uint16_t calculateChecksum(Command command)
{
    return command.start ^
            command.left.enable ^ command.right.enable ^
            command.left.pwm ^ command.right.pwm ^
            command.left.ctrlTyp ^ command.right.ctrlTyp ^
            command.left.ctrlMod ^ command.right.ctrlMod ^
            command.left.iMotMax ^ command.right.iMotMax ^
            command.left.iDcMax ^ command.right.iDcMax ^
            command.left.nMotMax ^ command.right.nMotMax ^
            command.left.phaseAdvMax ^ command.right.phaseAdvMax ^
            command.left.fieldWeakMax ^ command.right.fieldWeakMax ^
            command.buzzer.freq ^ command.buzzer.pattern ^
            command.poweroff;
}

}
