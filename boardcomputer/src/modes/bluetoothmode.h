#pragma once

#include <ArduinoJson.h>

#include "modebase.h"
#include "globals.h"

namespace {
class BluetoothMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override;
    void update() override;
    void stop() override {};

    String displayName() const override { return "Bluetooth"; }
};

void BluetoothMode::start()
{
    // clear buffer
    while (bluetooth.serial.available())
        bluetooth.serial.read();
}

void BluetoothMode::update()
{
    bool newLine{false};
    while (bluetooth.serial.available())
    {
        *bluetooth.pos = bluetooth.serial.read();
        if (*bluetooth.pos == '\n')
            newLine = true;
        bluetooth.pos++;
        if (newLine)
            break;
    }

    if (!newLine)
        return;

    StaticJsonDocument<256> doc;
    const auto error = deserializeJson(doc, &(*bluetooth.buffer.begin()), std::distance(bluetooth.buffer.begin(), bluetooth.pos));

    bluetooth.pos = bluetooth.buffer.begin();

    if (error)
    {
        bluetooth.serial.println(error.c_str());
        return;
    }

    if (!doc.containsKey("frontLeft"))
    {
        bluetooth.serial.print("no frontLeft");
        return;
    }
    if (!doc.containsKey("frontRight"))
    {
        bluetooth.serial.print("no frontRight");
        return;
    }
    if (!doc.containsKey("backLeft"))
    {
        bluetooth.serial.print("no backLeft");
        return;
    }
    if (!doc.containsKey("backRight"))
    {
        bluetooth.serial.print("no backRight");
        return;
    }

    controllers[0].command.left.pwm = doc["frontLeft"].as<int16_t>();
    controllers[0].command.right.pwm = doc["frontRight"].as<int16_t>();
    controllers[1].command.left.pwm = doc["backLeft"].as<int16_t>();
    controllers[1].command.right.pwm = doc["backRight"].as<int16_t>();

    for (Controller &controller : controllers)
    {
        Command &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->enable = true;
            motor->ctrlTyp = ControlType::FieldOrientedControl;
            motor->ctrlMod = ControlMode::Torque;
        }
    }
    fixCommonParams();

    sendCommands();
}
}
