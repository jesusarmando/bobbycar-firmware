#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "globals.h"
#include "utils.h"

namespace {
wl_status_t last_status;
IPAddress last_ip;

bool power_toggle{false};

void handleSerial()
{
    const auto status = WiFi.status();
    if (last_status != status)
    {
        Serial.print("Status changed to: ");
        Serial.println(toString(status));
        last_status = status;
    }

    const auto ip = WiFi.localIP();
    if (last_ip != ip)
    {
        Serial.print("IP changed to: ");
        Serial.println(ip.toString());
        last_ip = ip;
    }

    while(Serial.available())
    {
        const auto c = Serial.read();

        switch (c)
        {
        case 't':
        case 'T':
            power_toggle = !power_toggle;
            Serial.printf("power: %d\n", power_toggle);
            for (auto &controller : controllers)
                controller.command.poweroff = power_toggle;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            for (auto &controller : controllers)
                controller.command.buzzer.freq = c-'0';
            break;
        case 'A':
            InputDispatcher::rotate(-1);
            break;
        case 'B':
            InputDispatcher::rotate(1);
            break;
        case ' ':
            InputDispatcher::button(true);
            InputDispatcher::button(false);
            break;
        case 'm':
        case 'M':
            printMemoryUsage();
            break;
        }
    }
}
}
