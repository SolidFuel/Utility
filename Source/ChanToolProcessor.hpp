#pragma once

#include "ProcessorParameters.hpp"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

#include "Glider.hpp"

const long GLIDER_TIMING = 3000; // in samples

class ChanToolProcessor : public juce::AudioProcessor {
public:

    //==============================================================================
    // These are in setup.cpp

    ChanToolProcessor();

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; };

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;


    //==============================================================================
    // in-line

    bool isBusesLayoutSupported (const BusesLayout&) const override { return true; }

    const juce::String getName() const override {return JucePlugin_Name;}

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void releaseResources() override {};

    ProcessorParameters* getChanToolParameters() { return &parameters_; }

    //==============================================================================
    // These are in processing.cpp

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlock(juce::AudioBuffer<double>&, juce::MidiBuffer&) override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;



private:

    ProcessorParameters parameters_;

    BooleanGlider<float> mute_glider_{1.f, 0.f, GLIDER_TIMING};

    BooleanGlider<float> left_left_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> left_mid_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> left_right_glider_{0.f, 1.f, GLIDER_TIMING};

    BooleanGlider<float> right_right_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_mid_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_side_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_left_glider_{0.f, 1.f, GLIDER_TIMING};

    BooleanGlider<float> leftGlider_ {1.f, -1.f, GLIDER_TIMING};
    BooleanGlider<float> rightGlider_ {1.f, -1.f, GLIDER_TIMING};
    
    BooleanGlider<float> swapGlider_ {0.f, 1.f, GLIDER_TIMING};

    void parseCurrentXml(const juce::XmlElement * elem);

    // in processing.cpp
    template <class FT> void process_samples(juce::AudioBuffer<FT>&);

    // in setup.cpp
    void force_gliders();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChanToolProcessor)
};
