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
    return val / 32.133;
}

float convertFromKmh(float val)
{
    return val * 32.133;
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
            motor.iMotMax = settings.iMotMax;
            motor.iDcMax = settings.iDcMax;
            motor.nMotMax = settings.nMotMax;
            motor.fieldWeakMax = settings.fieldWeakMax;
            motor.phaseAdvMax = settings.phaseAdvMax;
        }

    if (front.invertLeft)
        front.command.left.pwm = -front.command.left.pwm;
    if (front.invertRight)
        front.command.right.pwm = -front.command.right.pwm;
    if (back.invertLeft)
        back.command.left.pwm = -back.command.left.pwm;
    if (back.invertRight)
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

void applyDefaultSettings()
{
    gasMin = defaultGasMin;
    gasMax = defaultGasMax;
    bremsMin = defaultBremsMin;
    bremsMax = defaultBremsMax;

    front.command.left.enable = defaultEnableFrontLeft;
    front.command.right.enable = defaultEnableFrontRight;
    back.command.left.enable = defaultEnableBackLeft;
    back.command.right.enable = defaultEnableBackRight;

    front.invertLeft = defaultInvertFrontLeft;
    front.invertRight = defaultInvertFrontRight;
    back.invertLeft = defaultInvertBackLeft;
    back.invertRight = defaultInvertBackRight;

    settings.iMotMax = defaultIMotMax;
    settings.iDcMax = defaultIDcMax;
    settings.nMotMax = defaultNMotMax;
    settings.fieldWeakMax = defaultFieldWeakMax;
    settings.phaseAdvMax = defaultPhaseAdvMax;

    for (Controller &controller : controllers())
        controller.command.buzzer = {};
}
}
