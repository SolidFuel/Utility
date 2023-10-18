#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>

#include "Glider.h"

const long GLIDER_TIMING = 3000; // in samples

class ChanToolProcessor : public PluginHelpers::ProcessorBase {
public:
    ChanToolProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void ChanToolProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) override;

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

    BooleanGlider<float> monoGlider_{0.f, 1.f, GLIDER_TIMING};

    BooleanGlider<float> leftGlider_ {1.f, -1.f, GLIDER_TIMING};
    BooleanGlider<float> rightGlider_ {1.f, -1.f, GLIDER_TIMING};
    
    BooleanGlider<float> swapGlider_ {0.f, 1.f, GLIDER_TIMING};

public:
    Parameters* getChanToolParameters() { return &parameters; }
};
