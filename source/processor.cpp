//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"
#include "ringbuffer.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Wararyo {
//------------------------------------------------------------------------
// SpeakerDelayProcessor
//------------------------------------------------------------------------
SpeakerDelayProcessor::SpeakerDelayProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kSpeakerDelayControllerUID);
}

//------------------------------------------------------------------------
SpeakerDelayProcessor::~SpeakerDelayProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::setBusArrangements (SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
{
    // inputとoutputのバスが1つずつで、かつinputとoutputの構成がステレオの場合
    if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
    {
        return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
    }
 
    // 対応していないバス構成の場合、kResultFalseを返す。
    return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
                    case ParamLTag:
                        timeL = getSamplesFromNormalized(value);
                        break;
                    case ParamRTag:
                        timeR = getSamplesFromNormalized(value);
                        break;
				}
			}
		}
	}
    
    // numSamplesが0のとき、inputsとoutputsには何も入らない
    if (data.numSamples == 0) return kResultOk;
	
	//--- Here you have to implement your processing
    processDelay(data.inputs[0].channelBuffers32[0], data.outputs[0].channelBuffers32[0], data.numSamples, timeL);
    processDelay(data.inputs[0].channelBuffers32[1], data.outputs[0].channelBuffers32[1], data.numSamples, 128);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
int32 SpeakerDelayProcessor::getSamplesFromNormalized (ParamValue value)
{
    return (int32)(value * SamplesStepCount);
}

//------------------------------------------------------------------------
void SpeakerDelayProcessor::processDelay(Sample32 *input, Sample32 *output, int32 numSamples, int32 timeSamples)
{
    if(timeSamples == 0) return;
    
    CRingBuffer buffer;
    buffer.SetInterval(timeSamples);
 
    // 入力信号にディレイを掛ける
    for (int i = 0; i < numSamples; i++)
    {
        float value;
        buffer.Write(input[i]);
        output[i] = buffer.Read();
        buffer.Update();
    }
}

//------------------------------------------------------------------------
} // namespace Wararyo
