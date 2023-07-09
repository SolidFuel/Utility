#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>

struct Parameters
{
    void add(juce::AudioProcessor& processor) const
    {
        
        processor.addParameter(mono);
        processor.addParameter(gain);
    }

    //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterBool* mono =
        new juce::AudioParameterBool({"Mono", 1}, "Mono", false);

    juce::AudioParameterFloat* gain =
        new juce::AudioParameterFloat({"Gain", 1}, "Gain", -100.f, 40.f, 0.f);

};