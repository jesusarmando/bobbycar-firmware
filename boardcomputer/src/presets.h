#pragma once

#include "settings.h"

namespace presets {
constexpr Settings::Limits defaultLimits {
    .iMotMax = 25,
    .iDcMax = 27,
    .nMotMax = 1000,
    .fieldWeakMax = 5,
    .phaseAdvMax = 40
};
constexpr Settings::Limits kidsLimits {
    .iMotMax = 5,
    .iDcMax = 7,
    .nMotMax = 500,
    .fieldWeakMax = 2,
    .phaseAdvMax = 20
};

constexpr Settings::Hardware::Poti defaultPoti {
    .sampleCount = 100,
    .gasMin = 800,
    .gasMax = 3700,
    .bremsMin = 1300,
    .bremsMax = 4000
};

constexpr Settings::Hardware defaultHardware {
    .enableFrontLeft = true,
    .enableFrontRight = true,
    .enableBackLeft = true,
    .enableBackRight = true,

    .invertFrontLeft = false,
    .invertFrontRight = true,
    .invertBackLeft = false,
    .invertBackRight = true,

    .poti = defaultPoti,

    .swapFrontBack = false
};

constexpr Settings::DefaultMode defaultDefaultMode {
    .ctrlTyp = ControlType::FieldOrientedControl,
    .ctrlMod = ControlMode::Torque,
    .enableSmoothing = true,
    .smoothing = 20,
    .frontPercentage = 100,
    .backPercentage = 100,
    .add_schwelle = 950,
    .gas1_wert = 1250,
    .gas2_wert = 1250,
    .brems1_wert = 250,
    .brems2_wert = 750
};

constexpr Settings::TempomatMode defaultTempomatMode {
    .ctrlTyp = ControlType::FieldOrientedControl,
    .ctrlMod = ControlMode::Speed
};

constexpr Settings::LarsmMode defaultLarsmMode {
    .mode = LarsmModeMode::Mode4,
    .iterations = 5
};

constexpr Settings defaultSettings{
    .limits = defaultLimits,
    .hardware = defaultHardware,
    .defaultMode = defaultDefaultMode,
    .tempomatMode = defaultTempomatMode,
    .larsmMode = defaultLarsmMode
};
}
