#pragma once

#include <array>
#include <iterator>

#include <ArduinoJson.h>

#include "modebase.h"
#include "globals.h"
#include "utils.h"

namespace {
class BluetoothMode final : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override;
    void update() override;

    const char *displayName() const override { return "Bluetooth"; }

private:
    std::array<uint8_t, 256> buffer;
    std::array<uint8_t, 256>::iterator pos{std::begin(buffer)};
};

namespace modes {
BluetoothMode bluetoothMode;
}

void BluetoothMode::start()
{
    ModeBase::start();

    // clear buffer
    while (bluetoothSerial.available())
        bluetoothSerial.read();
}

void BluetoothMode::update()
{
    bool newLine{false};
    while (bluetoothSerial.available())
    {
        *pos = bluetoothSerial.read();
        if (*pos == '\n')
            newLine = true;
        ++pos;
        if (newLine)
            break;
    }

    if (!newLine)
        return;

    StaticJsonDocument<256> doc;
    const auto error = deserializeJson(doc, &(*buffer.begin()), std::distance(buffer.begin(), pos));

    pos = buffer.begin();

    if (error)
    {
        bluetoothSerial.println(error.c_str());
        return;
    }

    if (!doc.containsKey("frontLeft"))
    {
        bluetoothSerial.print("no frontLeft");
        return;
    }
    if (!doc.containsKey("frontRight"))
    {
        bluetoothSerial.print("no frontRight");
        return;
    }
    if (!doc.containsKey("backLeft"))
    {
        bluetoothSerial.print("no backLeft");
        return;
    }
    if (!doc.containsKey("backRight"))
    {
        bluetoothSerial.print("no backRight");
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
