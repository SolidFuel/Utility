#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>

struct Parameters
{
    void add(juce::AudioProcessor& processor) const
    {
        
        processor.addParameter(mono);
        processor.addParameter(gain);
        processor.addParameter(stereo);
        processor.addParameter(swap);
        processor.addParameter(invertL);
        processor.addParameter(invertR);
    }

    //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterBool* mono =
        new juce::AudioParameterBool({"Mono", 1}, "Mono", false);

    juce::AudioParameterFloat* gain =
        new juce::AudioParameterFloat({"Gain", 1}, "Gain", -100.f, 40.f, 0.f);

    juce::AudioParameterFloat* stereo =
        new juce::AudioParameterFloat({"Stereo", 1}, "Stereo", 0.f, 200.f, 100.f);

    juce::AudioParameterBool* swap =
        new juce::AudioParameterBool({"Swap", 1}, "Swap", false);

    juce::AudioParameterBool* invertL =
        new juce::AudioParameterBool({"InvertL", 1}, "InvertL", false);
    juce::AudioParameterBool* invertR =
        new juce::AudioParameterBool({"InvertR", 1}, "InvertR", false);

};