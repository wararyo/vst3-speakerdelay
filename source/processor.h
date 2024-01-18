//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Wararyo {

//------------------------------------------------------------------------
//  SpeakerDelayProcessor
//------------------------------------------------------------------------
class SpeakerDelayProcessor : public AudioEffect
{
public:
	SpeakerDelayProcessor ();
	~SpeakerDelayProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new SpeakerDelayProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	tresult PLUGIN_API terminate () SMTG_OVERRIDE;
    
    tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
    int32 timeL, timeR;
    
    inline int32 getSamplesFromNormalized (ParamValue value);
    /**
     * @fn
     * 信号を遅延させる処理を行う
     * @param (input) 入力
     * @param (output) 出力
     * @param (numSamples) 入力および出力の長さ(サンプル数)
     * @param (timeSamples) 遅らせる時間(サンプル数)
     */
    void processDelay(Sample32* input, Sample32* output, int32 numSamples, int32 timeSamples);
};

//------------------------------------------------------------------------
} // namespace Wararyo
