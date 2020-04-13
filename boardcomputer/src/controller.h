#pragma once

#include <functional>

#include "../../common.h"

#include "feedbackparser.h"

class HardwareSerial;

namespace {
struct Controller {
    Controller(HardwareSerial &serial) :
        serial{serial}
    {
    }

    std::reference_wrapper<HardwareSerial> serial;

    bool invertLeft{}, invertRight{};

    Command command{};

    bool feedbackValid{};
    Feedback feedback{};

    FeedbackParser parser{serial, feedbackValid, feedback};
};
}
