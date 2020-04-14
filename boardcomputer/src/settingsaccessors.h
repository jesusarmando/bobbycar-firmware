#pragma once

#include "globals.h"
#include "accessorinterface.h"
#include "utils.h"

namespace {
//! Special type of RefAccessor that also saves settings after setValue()
template<typename T>
struct RefAccessorSaveSettings : public virtual RefAccessor<T>
{
    void setValue(T value) override { RefAccessor<T>::setValue(value); saveSettings(); };
};

struct IMotMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.iMotMax; } };
struct IDcMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.iDcMax; } };
struct NMotMaxKmhAccessor : public virtual AccessorInterface<int16_t>
{
    int16_t getValue() const override { return convertToKmh(settings.limits.nMotMax); }
    void setValue(int16_t value) override { settings.limits.nMotMax = convertFromKmh(value); }
};
struct NMotMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.nMotMax; } };
struct FieldWeakMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.fieldWeakMax; } };
struct PhaseAdvMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.phaseAdvMax; } };

struct FrontLeftEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.enableFrontLeft; } };
struct FrontRightEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.enableFrontRight; } };
struct BackLeftEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.enableBackLeft; } };
struct BackRightEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.enableBackRight; } };

struct FrontLeftInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.invertFrontLeft; } };
struct FrontRightInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.invertFrontRight; } };
struct BackLeftInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.invertBackLeft; } };
struct BackRightInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hardware.invertBackRight; } };

struct SampleCountAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hardware.poti.sampleCount; } };
struct GasMinAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hardware.poti.gasMin; } };
struct GasMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hardware.poti.gasMax; } };
struct BremsMinAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hardware.poti.bremsMin; } };
struct BremsMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hardware.poti.bremsMax; } };

struct SwapFrontBackAccessor : public RefAccessorSaveSettings<bool> {
    bool &getRef() const override { return settings.hardware.swapFrontBack; }
    void setValue(bool value) override { RefAccessorSaveSettings<bool>::setValue(value); updateSwapFrontBack(); };
};

struct DefaultModeCtrlTypAccessor : public RefAccessorSaveSettings<ControlType> { ControlType &getRef() const override { return settings.defaultMode.ctrlTyp; } };
struct DefaultModeCtrlModAccessor : public RefAccessorSaveSettings<ControlMode> { ControlMode &getRef() const override { return settings.defaultMode.ctrlMod; } };
struct DefaultModeEnableSmoothingAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.enableSmoothing; } };
struct DefaultModeSmoothingAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.smoothing; } };
struct DefaultModeFrontPercentageAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.frontPercentage; } };
struct DefaultModeBackPercentageAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.backPercentage; } };
struct DefaultModeAddSchwelleAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.add_schwelle; } };
struct DefaultModeGas1WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.gas1_wert; } };
struct DefaultModeGas2WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.gas2_wert; } };
struct DefaultModeBrems1WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.brems1_wert; } };
struct DefaultModeBrems2WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.brems2_wert; } };

struct TempomatModeCtrlTypAccessor : public RefAccessorSaveSettings<ControlType> { ControlType &getRef() const override { return settings.tempomatMode.ctrlTyp; } };
struct TempomatModeCtrlModAccessor : public RefAccessorSaveSettings<ControlMode> { ControlMode &getRef() const override { return settings.tempomatMode.ctrlMod; } };

struct LarsmModeModeAccessor : public RefAccessorSaveSettings<LarsmModeMode> { LarsmModeMode &getRef() const override { return settings.larsmMode.mode; } };
struct LarsmModeIterationsAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.larsmMode.iterations; } };
}
