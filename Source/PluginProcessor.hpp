/****
 * solidUtility - Versatile VST3 Channel Utility for Digital Audio Workstations 
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/

#pragma once

#include "ProcessorParameters.hpp"

#include "Glider.hpp"

const long GLIDER_TIMING = 3000; // in samples

class PluginProcessor : public juce::AudioProcessor {
public:

    //==============================================================================
    // These are in setup.cpp

    PluginProcessor();

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    bool isBusesLayoutSupported(const BusesLayout&) const override;



    //==============================================================================
    // in-line


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
    void releaseResources() override {}

    ProcessorParameters* getParameters() { return &parameters_; }

    //==============================================================================
    // These are in processing.cpp

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlock(juce::AudioBuffer<double>&, juce::MidiBuffer&) override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;



private:

    ProcessorParameters parameters_;

    BooleanGlider<float> left_mute_glider_{1.f, 0.f, GLIDER_TIMING};
    BooleanGlider<float> right_mute_glider_{1.f, 0.f, GLIDER_TIMING};

    BooleanGlider<float> left_left_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> left_mid_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> left_side_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> left_right_glider_{0.f, 1.f, GLIDER_TIMING};

    BooleanGlider<float> right_right_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_mid_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_side_glider_{0.f, 1.f, GLIDER_TIMING};
    BooleanGlider<float> right_left_glider_{0.f, 1.f, GLIDER_TIMING};

    BooleanGlider<float> leftGlider_ {1.f, -1.f, GLIDER_TIMING};
    BooleanGlider<float> rightGlider_ {1.f, -1.f, GLIDER_TIMING};
    
    BooleanGlider<float> swapGlider_ {0.f, 1.f, GLIDER_TIMING};

    Glider<float> gain_glider_{0.0, 0.0, GLIDER_TIMING};
    Glider<float> pan_glider_{0.5, 0.5, GLIDER_TIMING};

    void parseCurrentXml(const juce::XmlElement * elem);

    // For the high pass filter used to remove DC offset

    // Filter constant
    // alpha will be computed in the prepareToPlay()
    // function since it is based on sample rate.
    double alpha = 1.00;
    // The last values we computed to remove offset
    double last_left_value = 0.0;
    double last_right_value = 0.0;
    // The last values we saw BEFORE removing offset
    double last_offset_left_value = 0.0;
    double last_offset_right_value = 0.0;

    // in processing.cpp
    template <class FT> void process_samples(juce::AudioBuffer<FT>&);

    // in setup.cpp
    void force_gliders();


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
