#pragma once

#include <algorithm>

#include <WString.h>
#include <WiFi.h>

#include "display.h"
#include "globals.h"

namespace {
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

String toString(wl_status_t status)
{
    switch (status)
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

    return String("Unknown: ") + int(status);
}

void fixCommonParams()
{
    for (auto &controller : controllers)
    {
        controller.command.left.iMotMax = controller.command.right.iMotMax = settings.iMotMax;
        controller.command.left.iDcMax = controller.command.right.iDcMax = settings.iDcMax;
        controller.command.left.nMotMax = controller.command.right.nMotMax = settings.nMotMax;
        controller.command.left.fieldWeakMax = controller.command.right.fieldWeakMax = settings.fieldWeakMax;
        controller.command.left.phaseAdvMax = controller.command.right.phaseAdvMax = settings.phaseAdvMax;
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
    for (auto &controller : controllers)
    {
        controller.command.start = Command::VALID_HEADER;
        controller.command.checksum = calculateChecksum(controller.command);
        controller.serial.write((uint8_t *) &controller.command, sizeof(controller.command));
    }
}

template<typename T, typename... Args>
void switchScreen(Args&&... args);

}
