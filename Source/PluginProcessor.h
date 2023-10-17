#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>

class ChanToolProcessor : public PluginHelpers::ProcessorBase {
public:
    ChanToolProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:

struct Parameters
{    juce::AudioParameterBool* mono; 

    juce::AudioParameterFloat* gain;

    juce::AudioParameterFloat* stereo;

    juce::AudioParameterBool* swap;

    juce::AudioParameterBool* invertL;
    juce::AudioParameterBool* invertR;

    std::unique_ptr<juce::AudioProcessorValueTreeState> apvts;

     Parameters(ChanToolProcessor& processor);

};

    Parameters parameters;

    bool invertR_old = false;
    bool invertL_old = false;

public:
    Parameters* getChanToolParameters() { return &parameters; }
};
