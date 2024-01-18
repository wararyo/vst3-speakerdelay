//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace Wararyo {
//------------------------------------------------------------------------
static const Steinberg::FUID kSpeakerDelayProcessorUID (0x97491C17, 0x15D25CD8, 0x8BD653FB, 0x26EDE4BA);
static const Steinberg::FUID kSpeakerDelayControllerUID (0x39221518, 0xFF7C5F6D, 0x92B867E1, 0x8E41EBA2);

#define SpeakerDelayVST3Category "Fx"

#define ParamLTag 100
#define ParamRTag 101

#define MaxSamples 511
#define SamplesStepCount 512

//------------------------------------------------------------------------
} // namespace Wararyo
