#pragma once

#include <stdint.h>

#include "../../common.h"

class HardwareSerial;

namespace {
struct Controller {
    Controller(HardwareSerial &serial) : serial{serial} {}

    HardwareSerial &serial;

    Command command;
    Feedback feedback, newFeedback;

    unsigned long lastFeedback = 0;

    uint8_t idx = 0;                        // Index for new data pointer
    uint16_t bufStartFrame;                 // Buffer Start Frame
    uint8_t *p;                             // Pointer declaration for the new received data
    uint8_t incomingByte;
    uint8_t incomingBytePrev;
};
}
