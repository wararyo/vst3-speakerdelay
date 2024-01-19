//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#include "delayer.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Wararyo {

//------------------------------------------------------------------------
// Delayer Implementation
//------------------------------------------------------------------------

void Delayer::setDelayTime (int32 timeSamples)
{
    delayTime = timeSamples;
    buffer.SetInterval(timeSamples);
}

void Delayer::processDelay (Sample32 *input, Sample32 *output, int32 numSamples)
{
    if(delayTime == 0) return;
 
    // 入力信号にディレイを掛ける
    for (int i = 0; i < numSamples; i++)
    {
        buffer.Write(input[i]);
        output[i] = buffer.Read();
        buffer.Update();
    }
}

//------------------------------------------------------------------------
} // namespace Wararyo
