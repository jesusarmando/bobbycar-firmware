#pragma once

#include "settings.h"

namespace {
namespace presets {
const Settings defaultSettings{
    .limits = {
        .iMotMax = 25,
        .iDcMax = 27,
        .nMotMax = 1000,
        .fieldWeakMax = 5,
        .phaseAdvMax = 40
    },

    .hardware = {
        .enableFrontLeft = true,
        .enableFrontRight = true,
        .enableBackLeft = true,
        .enableBackRight = true,

        .invertFrontLeft = false,
        .invertFrontRight = true,
        .invertBackLeft = false,
        .invertBackRight = true,

        .poti = {
            .sampleCount = 100,
            .gasMin = 800,
            .gasMax = 3700,
            .bremsMin = 1300,
            .bremsMax = 4000,
        },

        .swapFrontBack = false
    },

    .defaultMode = {
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
    },
    .tempomatMode = {
        .ctrlTyp = ControlType::FieldOrientedControl,
        .ctrlMod = ControlMode::Speed,
    },
    .larsmMode = {
        .mode = LarsmModeMode::Mode4,
        .iterations = 5,
    }
};
}
}
