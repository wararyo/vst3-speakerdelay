//------------------------------------------------------------------------
// Copyright(c) 2024 wararyo.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"
#include "delayer.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace Wararyo {

//------------------------------------------------------------------------
// SpeakerDelayController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
    for (int i = 0; i < MaxChannels; i++)
    {
        // StepCount > 1のときはMaxPlainは使われないっぽいので適当に指定しておく
        RangeParameter* param = new RangeParameter(ChannelNames[i], ParamTimeTag + i, STR16("Sa"), 0, SamplesStepCount, 0, SamplesStepCount);
        parameters.addParameter(param);
    }

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;
    
    IBStreamer streamer (state, kLittleEndian);
    Delayer delayers[MaxChannels];
    TSize size = streamer.readRaw(&delayers, sizeof(delayers));
    for (int i = 0; i < MaxChannels; i++)
    {
        setParamNormalized(ParamTimeTag + i, getNormalizedValueFromSamples(delayers[i].getDelayTime()));
    }

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API SpeakerDelayController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API SpeakerDelayController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
ParamValue SpeakerDelayController::getNormalizedValueFromSamples (int32 value)
{
	return value / ParamValue (SamplesStepCount);
}

//------------------------------------------------------------------------
} // namespace Wararyo
