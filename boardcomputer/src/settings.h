#pragma once

#include <cstdint>

#include "../../common.h"

namespace {
enum class LarsmModeMode : uint8_t { Mode1, Mode2, Mode3, Mode4 };

struct Settings
{
    struct {
        int16_t iMotMax;      // [A] Maximum motor current limit
        int16_t iDcMax;       // [A] Maximum DC Link current limit (This is the current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A)
        int16_t nMotMax;      // [rpm] Maximum motor speed limit
        int16_t fieldWeakMax; // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed.
        int16_t phaseAdvMax;  // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed.
    } limits;

    struct {
        bool enableFrontLeft, enableFrontRight, enableBackLeft, enableBackRight;
        bool invertFrontLeft, invertFrontRight, invertBackLeft, invertBackRight;

        struct {
            int16_t sampleCount;
            int16_t gasMin, gasMax, bremsMin, bremsMax;
        } poti;

        bool swapFrontBack;
    } hardware;

    struct {
        ControlType ctrlTyp;
        ControlMode ctrlMod;
        bool enableSmoothing;
        int16_t smoothing;
        int16_t frontPercentage;
        int16_t backPercentage;
        int16_t add_schwelle;
        int16_t gas1_wert;
        int16_t gas2_wert;
        int16_t brems1_wert;
        int16_t brems2_wert;
    } defaultMode;

    struct {
        ControlType ctrlTyp;
        ControlMode ctrlMod;
    } tempomatMode;

    struct {
        LarsmModeMode mode;
        uint8_t iterations;
    } larsmMode;


    template<typename T>
    void forEverySetting(T &&callable);
};

template<typename T>
void Settings::forEverySetting(T &&callable)
{
    callable("iMotMax", limits.iMotMax);
    callable("iDcMax", limits.iDcMax);
    callable("nMotMax", limits.nMotMax);
    callable("fieldWeakMax", limits.fieldWeakMax);
    callable("phaseAdvMax", limits.phaseAdvMax);

    callable("enableFrontLeft", hardware.enableFrontLeft);
    callable("enableFrontRigh", hardware.enableFrontRight);
    callable("enableBackLeft", hardware.enableBackLeft);
    callable("enableBackRight", hardware.enableBackRight);

    callable("invertFrontLeft", hardware.invertFrontLeft);
    callable("invertFrontRigh", hardware.invertFrontRight);
    callable("invertBackLeft", hardware.invertBackLeft);
    callable("invertBackRight", hardware.invertBackRight);

    callable("sampleCount", hardware.poti.sampleCount);
    callable("gasMin", hardware.poti.gasMin);
    callable("gasMax", hardware.poti.gasMax);
    callable("bremsMin", hardware.poti.bremsMin);
    callable("bremsMax", hardware.poti.bremsMax);

    callable("swapFrontBack", hardware.swapFrontBack);

    callable("default.ctrlTyp", defaultMode.ctrlTyp);
    callable("default.ctrlMod", defaultMode.ctrlMod);
    callable("default.enableS", defaultMode.enableSmoothing);
    callable("default.smoothi", defaultMode.smoothing);
    callable("default.frontPe", defaultMode.frontPercentage);
    callable("default.backPer", defaultMode.backPercentage);
    callable("default.add_sch", defaultMode.add_schwelle);
    callable("default.gas1_we", defaultMode.gas1_wert);
    callable("default.gas2_we", defaultMode.gas2_wert);
    callable("default.brems1_", defaultMode.brems1_wert);
    callable("default.brems2_", defaultMode.brems2_wert);

    callable("tempoma.ctrlTyp", tempomatMode.ctrlTyp);
    callable("tempomt.ctrlMod", tempomatMode.ctrlMod);

    callable("larsm.mode", larsmMode.mode);
    callable("larsm.iters", larsmMode.iterations);
}
}
