#pragma once

#include <Esp.h>

#include "textinterface.h"

namespace {
template<const char *Ttext, typename TreturnType, TreturnType (EspClass::*Tmethod)()>
using EspStatusTextHelper = StatusTextHelper<Ttext, EspClass, &ESP, TreturnType, Tmethod>;

constexpr char TEXT_ESPHEAPSIZE[] = "Heap size: ";
using EspHeapSizeText = EspStatusTextHelper<TEXT_ESPHEAPSIZE, uint32_t, &EspClass::getHeapSize>;

constexpr char TEXT_ESPFREEHEAP[] = "Free heap: ";
using EspFreeHeapText = EspStatusTextHelper<TEXT_ESPFREEHEAP, uint32_t, &EspClass::getFreeHeap>;

constexpr char TEXT_ESPMINFREEHEAP[] = "Min free heap: ";
using EspMinFreeHeapText = EspStatusTextHelper<TEXT_ESPMINFREEHEAP, uint32_t, &EspClass::getMinFreeHeap>;

constexpr char TEXT_ESPMAXALLOCHEAP[] = "Max alloc heap: ";
using EspMaxAllocHeapText = EspStatusTextHelper<TEXT_ESPMAXALLOCHEAP, uint32_t, &EspClass::getMaxAllocHeap>;

constexpr char TEXT_ESPPSRAMSIZE[] = "psram size: ";
using EspPsramSizeText = EspStatusTextHelper<TEXT_ESPPSRAMSIZE, uint32_t, &EspClass::getPsramSize>;

constexpr char TEXT_ESPFREEPSRAM[] = "Free psram: ";
using EspFreePsramText = EspStatusTextHelper<TEXT_ESPFREEPSRAM, uint32_t, &EspClass::getFreePsram>;

constexpr char TEXT_ESPMINFREEPSRAM[] = "Min free psram: ";
using EspMinFreePsramText = EspStatusTextHelper<TEXT_ESPMINFREEPSRAM, uint32_t, &EspClass::getMinFreePsram>;

constexpr char TEXT_ESPMAXALLOCPSRAM[] = "Max alloc psram: ";
using EspMaxAllocPsramText = EspStatusTextHelper<TEXT_ESPMAXALLOCPSRAM, uint32_t, &EspClass::getMaxAllocPsram>;

constexpr char TEXT_ESPCHIPREVISION[] = "Chip revision: ";
using EspChipRevisionText = EspStatusTextHelper<TEXT_ESPCHIPREVISION, uint8_t, &EspClass::getChipRevision>;

constexpr char TEXT_ESPCPUFREQMHZ[] = "Cpu freq MHz: ";
using EspCpuFreqMHzText = EspStatusTextHelper<TEXT_ESPCPUFREQMHZ, uint32_t, &EspClass::getCpuFreqMHz>;

constexpr char TEXT_ESPCYCLECOUNT[] = "Cycle count: ";
using EspCycleCountText = EspStatusTextHelper<TEXT_ESPCYCLECOUNT, uint32_t, &EspClass::getCycleCount>;

constexpr char TEXT_ESPSDKVERSION[] = "Sdk version: ";
using EspSdkVersionText = EspStatusTextHelper<TEXT_ESPSDKVERSION, const char *, &EspClass::getSdkVersion>;

constexpr char TEXT_ESPFLASHCHIPSIZE[] = "Flash chip size: ";
using EspFlashChipSizeText = EspStatusTextHelper<TEXT_ESPFLASHCHIPSIZE, uint32_t, &EspClass::getFlashChipSize>;

constexpr char TEXT_ESPFLASHCHIPSPEED[] = "Flash chip speed: ";
using EspFlashChipSpeedText = EspStatusTextHelper<TEXT_ESPFLASHCHIPSPEED, uint32_t, &EspClass::getFlashChipSpeed>;

constexpr char TEXT_ESPFLASHCHIPMODE[] = "Flash chip mode: ";
using EspFlashChipModeText = EspStatusTextHelper<TEXT_ESPFLASHCHIPMODE, FlashMode_t, &EspClass::getFlashChipMode>; // TODO: improve stringifying

constexpr char TEXT_ESPSKETCHSIZE[] = "Sketch size: ";
using EspSketchSizeText = StaticallyCachedText<EspStatusTextHelper<TEXT_ESPSKETCHSIZE, uint32_t, &EspClass::getSketchSize>>; // caching because of slow

constexpr char TEXT_ESPSKETCHMD5[] = "Sketch MD5: ";
using EspSketchMd5Text = StaticallyCachedText<EspStatusTextHelper<TEXT_ESPSKETCHMD5, String, &EspClass::getSketchMD5>>; // caching because of slow

constexpr char TEXT_ESPFREESKETCHSPACE[] = "Free sketch space: ";
using EspFreeSketchSpaceText = StaticallyCachedText<EspStatusTextHelper<TEXT_ESPFREESKETCHSPACE, uint32_t, &EspClass::getFreeSketchSpace>>; // caching because of slow
}
