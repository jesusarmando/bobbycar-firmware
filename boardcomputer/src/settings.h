#pragma once

namespace {
constexpr auto defaultGasMin = 800, defaultGasMax = 3700,
               defaultBremsMin = 1300, defaultBremsMax = 4000;
constexpr auto defaultInvertFrontLeft = false, defaultInvertFrontRight = true, defaultInvertBackLeft = false, defaultInvertBackRight = true;
constexpr auto defaultEnableFrontLeft = true, defaultEnableFrontRight = true, defaultEnableBackLeft = true, defaultEnableBackRight = true;
constexpr auto defaultIMotMax = 25, defaultIDcMax = 27, defaultFieldWeakMax = 5;
constexpr auto defaultDefaultModeGas1Wert = 1250, defaultDefaultModeGas2Wert = 1250, defaultDefaultModeBrems1Wert = 250, defaultDefaultModeBrems2Wert = 750;
constexpr auto gasPin = 35, bremsPin = 33;
constexpr auto rxPin1 = 4, txPin1 = 5,
               rxPin2 = 25, txPin2 = 26;
}
