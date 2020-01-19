#pragma once

#include <stdint.h>

#include "config.h"

namespace {

enum class ControlType : uint8_t {
    Commutation,
    Sinusoidal,
    FieldOrientedControl
};

enum class ControlMode : uint8_t {
    OpenMode,
    Voltage,
    Speed, // Only with FieldOrientedControl
    Torque // Only with FieldOrientedControl
};

struct MotorState {
    bool enable = false;
    int16_t pwm = 0;
    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::OpenMode;
    int16_t iMotMax = 15;                  // [A] Maximum motor current limit
    int16_t iDcMax = 17;                   // [A] Maximum DC Link current limit (This is the final current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A)
    int16_t nMotMax = 1000;                // [rpm] Maximum motor speed limit
    int16_t fieldWeakMax = 10;             // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed.
    int16_t phaseAdvMax = 40;              // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed.
};

struct BuzzerState {
    uint8_t freq = 0;
    uint8_t pattern = 0;
};

struct Command {
    static constexpr uint16_t VALID_HEADER = 0xAAAA;
    static constexpr uint16_t INVALID_HEADER = 0xFFFF;

    uint16_t start;

    MotorState left, right;

    BuzzerState buzzer;

    bool poweroff = false;
    bool led = false;

    uint16_t checksum;
};

uint16_t calculateChecksum(Command command) {
    return command.start ^
            command.left.enable ^ uint16_t(command.right.enable) ^
            command.left.pwm ^ command.right.pwm ^
            uint8_t(command.left.ctrlTyp) ^ uint8_t(command.right.ctrlTyp) ^
            uint8_t(command.left.ctrlMod) ^ uint8_t(command.right.ctrlMod) ^
            command.left.iMotMax ^ command.right.iMotMax ^
            command.left.iDcMax ^ command.right.iDcMax ^
            command.left.nMotMax ^ command.right.nMotMax ^
            command.left.phaseAdvMax ^ command.right.phaseAdvMax ^
            command.left.fieldWeakMax ^ command.right.fieldWeakMax ^
            command.buzzer.freq ^ command.buzzer.pattern ^
            command.poweroff ^ command.led;
}

struct MotorFeedback {
    int16_t   angle = 0;
    int16_t   speed = 0;
    uint8_t   error = 0;
    int16_t   current = 0;
    uint32_t  chops = 0;
    bool      hallA = false,
              hallB = false,
              hallC = false;
};

struct Feedback {
    static constexpr uint16_t VALID_HEADER = 0xAAAA;
    static constexpr uint16_t INVALID_HEADER = 0xFFFF;

    uint16_t start;

    MotorFeedback left, right;

    int16_t   batVoltage = 0;
    int16_t   boardTemp = 0;

    uint16_t checksum;
};

uint16_t calculateChecksum(Feedback feedback) {
    return feedback.start ^
            feedback.left.angle ^ feedback.right.angle ^
            feedback.left.speed ^ feedback.right.speed ^
            feedback.left.error ^ feedback.right.error ^
            feedback.left.current ^ feedback.right.current ^
            feedback.left.chops ^ feedback.right.chops ^
            feedback.left.hallA ^ feedback.left.hallB ^ feedback.left.hallC ^
            feedback.right.hallA ^ feedback.right.hallB ^ feedback.right.hallC ^
            feedback.batVoltage ^
            feedback.boardTemp;
}

}
