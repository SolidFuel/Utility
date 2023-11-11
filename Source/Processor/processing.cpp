/****
 * ChanTool - Simple DAW Channel Utility 
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/


#include "../ChanToolProcessor.hpp"


//============================================================================
void ChanToolProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate, samplesPerBlock);

    monoGlider_.forceValue(parameters.mono->get());

    leftGlider_.forceValue(parameters.invertL->get());

    rightGlider_.forceValue(parameters.invertR->get());

};

//============================================================================
void ChanToolProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages) {
    juce::ignoreUnused(midiMessages);

    auto num_samples = buffer.getNumSamples();

    // ---- MONO parameter
    bool mono = parameters.mono->get();
    monoGlider_.go(mono);

#if (0)
    // -- STEREO parameter
    float stereo = parameters.stereo->get() / 100.f;
    if (stereo > 1.f) {
        stereo = 1.f + (stereo-1.f)/2.f;
    }
#endif

    // -- GAIN parameter
    float gain = powf(2.f, parameters.gain->get() / 6.f);

    // INVERTL parameter
    leftGlider_.go(parameters.invertL->get()); 

    // INVERTR parameter
    rightGlider_.go(parameters.invertR->get()); 

    // SWAP parameter
    auto swap = parameters.swap->get();
    swapGlider_.go(swap);


    // --- LOOP Start
    auto* channel0_data = buffer.getWritePointer(0);
    auto* channel1_data = buffer.getWritePointer(1);
    for (int i = 0; i < num_samples; ++i) {
        auto in0 = channel0_data[i];
        auto in1 = channel1_data[i];
        float out0 = in0;
        float out1 = in1;

        // mono
        auto val = monoGlider_.nextValue();
        auto mid = (out0 + out1)/2.0f;

        out0 = out0 *(1.f-val) + mid * val;
        out1 = out1 *(1.f-val) + mid * val;

        // gain
        out0 = gain * out0;
        out1 = gain * out1;

        // inverting
        out0 = out0 * leftGlider_.nextValue();
        out1 = out1 * rightGlider_.nextValue();

        // Swap the channels
        auto swapVal = swapGlider_.nextValue();
        out0 = out0 *(1-swapVal) + out1 * swapVal;
        out1 = out1 *(1-swapVal) + out0 * swapVal;

        // Output
        channel0_data[i] = out0;
        channel1_data[i] = out1;

    }
}
