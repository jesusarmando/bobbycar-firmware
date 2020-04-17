#pragma once

#include <algorithm>

#include <WString.h>
#include <WiFi.h>

#include "display.h"
#include "globals.h"

namespace {
template<typename ...T>
class makeComponent : public T...
{};

template<typename T>
T scaleBetween(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x < std::min(in_min, in_max))
        x = std::min(in_min, in_max);
    else if (x > std::max(in_min, in_max))
        x = std::max(in_min, in_max);

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
};

float convertToKmh(float val)
{
    return val /* / settings.hardware.numMagnetPoles */ / 60.f * settings.hardware.wheelDiameter / 1000.f * 3.14159265359f * 3.6f;
}

float convertFromKmh(float val)
{
    return val /* * settings.hardware.numMagnetPoles */ * 60.f / settings.hardware.wheelDiameter * 1000.f / 3.14159265359f / 3.6f;
}

float convertToInch(float val)
{
    return val / 25.4f;
}

float convertFromInch(float val)
{
    return val * 25.4f;
}

float fixCurrent(int16_t value)
{
    return std::abs(value/50.);
}

float fixBatVoltage(int16_t value)
{
    return value/100.;
}

float fixBoardTemp(int16_t value)
{
    return value/10.;
}

String hallString(const MotorFeedback &motor)
{
    return String{} + (motor.hallA ? '1' : '0') + (motor.hallB ? '1' : '0') + (motor.hallC ? '1' : '0');
}

template<typename T>
String toString(T value)
{
    return String{} + value;
}

template<>
String toString<bool>(bool value)
{
    return value ? "true" : "false";
}

template<>
String toString<ControlType>(ControlType value)
{
    switch (value)
    {
    case ControlType::Commutation: return "Commutation";
    case ControlType::Sinusoidal: return "Sinusoidal";
    case ControlType::FieldOrientedControl: return "FieldOrientedControl";
    }
    return String("Unknown: ") + int(value);
}

template<>
String toString<ControlMode>(ControlMode value)
{
    switch (value)
    {
    case ControlMode::OpenMode: return "OpenMode";
    case ControlMode::Voltage: return "Voltage";
    case ControlMode::Speed: return "Speed";
    case ControlMode::Torque: return "Torque";
    }
    return String("Unknown: ") + int(value);
}

template<>
String toString<wl_status_t>(wl_status_t value)
{
    switch (value)
    {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
    }

    return String("Unknown: ") + int(value);
}

std::array<std::reference_wrapper<Controller>, 2> controllers()
{
    return {front, back};
}

std::array<std::reference_wrapper<MotorState>, 2> motorsInController(Controller &controller)
{
    return {std::ref(controller.command.left), std::ref(controller.command.right)};
}

std::array<std::reference_wrapper<const MotorState>, 2> motorsInController(const Controller &controller)
{
    return {std::ref(controller.command.left), std::ref(controller.command.right)};
}

std::array<std::reference_wrapper<MotorFeedback>, 2> motorFeedbacksInController(Controller &controller)
{
    return {std::ref(controller.feedback.left), std::ref(controller.feedback.right)};
}

std::array<std::reference_wrapper<const MotorFeedback>, 2> motorFeedbacksInController(const Controller &controller)
{
    return {std::ref(controller.feedback.left), std::ref(controller.feedback.right)};
}

std::array<std::reference_wrapper<MotorState>, 4> motors()
{
    return {
        std::ref(front.command.left), std::ref(front.command.right),
        std::ref(back.command.left), std::ref(back.command.right)
    };
}

void fixCommonParams()
{
    for (Controller &controller : controllers())
        for (MotorState &motor : motorsInController(controller))
        {
            motor.iMotMax = settings.limits.iMotMax;
            motor.iDcMax = settings.limits.iDcMax;
            motor.nMotMax = settings.limits.nMotMax;
            motor.fieldWeakMax = settings.limits.fieldWeakMax;
            motor.phaseAdvMax = settings.limits.phaseAdvMax;
        }

    front.command.left.enable = settings.hardware.enableFrontLeft;
    front.command.right.enable = settings.hardware.enableFrontRight;
    back.command.left.enable = settings.hardware.enableBackLeft;
    back.command.right.enable = settings.hardware.enableBackRight;

    if (settings.hardware.invertFrontLeft)
        front.command.left.pwm = -front.command.left.pwm;
    if (settings.hardware.invertFrontRight)
        front.command.right.pwm = -front.command.right.pwm;
    if (settings.hardware.invertBackLeft)
        back.command.left.pwm = -back.command.left.pwm;
    if (settings.hardware.invertBackRight)
        back.command.right.pwm = -back.command.right.pwm;
}

void sendCommands()
{
    for (Controller &controller : controllers())
    {
        controller.command.start = Command::VALID_HEADER;
        controller.command.checksum = calculateChecksum(controller.command);
        controller.serial.get().write((uint8_t *) &controller.command, sizeof(controller.command));
    }
}

template<typename T, typename... Args>
void switchScreen(Args&&... args);

void setupScrollArea(uint16_t TFA, uint16_t BFA) {
  tft.writecommand(ILI9341_VSCRDEF); // Vertical scroll definition
  tft.writedata(TFA >> 8);
  tft.writedata(TFA);
  tft.writedata((320 - TFA - BFA) >> 8);
  tft.writedata(320 - TFA - BFA);
  tft.writedata(BFA >> 8);
  tft.writedata(BFA);
}

void scrollAddress(uint16_t VSP) {
  tft.writecommand(ILI9341_VSCRSADD); // Vertical scrolling start address
  tft.writedata(VSP >> 8);
  tft.writedata(VSP);
}

void updateSwapFrontBack()
{
    front.serial = settings.hardware.swapFrontBack ? Serial2 : Serial1;
    back.serial = settings.hardware.swapFrontBack ? Serial1 : Serial2;
}

void loadSettings()
{
    settingsSaver.load(settings);
}

void saveSettings()
{
    settingsSaver.save(settings);
}

void updateAccumulators()
{
    avgSpeed = 0.f;
    sumCurrent = 0.f;
    uint8_t count{0};

    for (const Controller &controller : controllers())
    {
        if (!controller.feedbackValid)
            continue;

        avgSpeed +=
                controller.feedback.left.speed * (controller.invertLeft ? -1 : 1) +
                controller.feedback.right.speed * (controller.invertRight ? -1 : 1);

        sumCurrent +=
                controller.feedback.left.current +
                controller.feedback.right.current;

        count +=2;
    }

    if (count)
        avgSpeed /= count;

    avgSpeedKmh = convertToKmh(avgSpeed);
}
}
