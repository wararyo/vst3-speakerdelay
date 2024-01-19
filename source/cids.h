//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

using namespace Steinberg::Vst;

namespace Wararyo {
//------------------------------------------------------------------------
static const Steinberg::FUID kSpeakerDelayProcessorUID (0x97491C17, 0x15D25CD8, 0x8BD653FB, 0x26EDE4BA);
static const Steinberg::FUID kSpeakerDelayControllerUID (0x39221518, 0xFF7C5F6D, 0x92B867E1, 0x8E41EBA2);

#define SpeakerDelayVST3Category "Fx"

#define ParamTimeTag 100

#define MaxSamples 511
#define SamplesStepCount 512
#define MaxChannels 16

static const TChar* ChannelNames[MaxChannels] = {
    STR16("L"),
    STR16("R"),
    STR16("C"),
    STR16("Lfe"),
    STR16("5"),
    STR16("6"),
    STR16("7"),
    STR16("8"),
    STR16("9"),
    STR16("10"),
    STR16("11"),
    STR16("12"),
    STR16("13"),
    STR16("14"),
    STR16("15"),
    STR16("16"),
};

//------------------------------------------------------------------------
} // namespace Wararyo
