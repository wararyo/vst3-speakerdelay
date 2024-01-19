//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/vst/vsttypes.h"
#include "ringbuffer.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Wararyo {

//------------------------------------------------------------------------
//  Delayer
//------------------------------------------------------------------------
class Delayer
{
public:
//------------------------------------------------------------------------
	Delayer () = default;
	~Delayer () = default;

    void setDelayTime(int32 timeSamples);
    /**
     * @fn
     * 信号を遅延させる処理を行う
     * @param (input) 入力
     * @param (output) 出力
     * @param (numSamples) 入力および出力の長さ(サンプル数)
     * @param (timeSamples) 遅らせる時間(サンプル数)
     */
    void processDelay(Sample32 *input, Sample32 *output, int32 numSamples);

//------------------------------------------------------------------------
protected:
    int32 delayTime;
    CRingBuffer buffer;
};

//------------------------------------------------------------------------
} // namespace Wararyo
