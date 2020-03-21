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
    front.controller.command.left.enable = front.left.enable;
    front.controller.command.right.enable = front.right.enable;
    back.controller.command.left.enable = back.left.enable;
    back.controller.command.right.enable = back.right.enable;

    if (front.left.invert)
        front.controller.command.left.pwm = -front.controller.command.left.pwm;
    if (front.right.invert)
        front.controller.command.right.pwm = -front.controller.command.right.pwm;
    if (back.left.invert)
        back.controller.command.left.pwm = -back.controller.command.left.pwm;
    if (back.right.invert)
        back.controller.command.right.pwm = -back.controller.command.right.pwm;
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
}
