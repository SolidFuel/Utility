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

#include <cmath>

//============================================================================
void ChanToolProcessor::prepareToPlay(double, int) {

    force_gliders();

}

//============================================================================
void ChanToolProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer&) {
    process_samples(buffer);
}

//============================================================================
void ChanToolProcessor::processBlock(juce::AudioBuffer<double>& buffer,
                                    juce::MidiBuffer&) {
    process_samples(buffer);
}


//============================================================================
template <class FT>
void ChanToolProcessor::process_samples(juce::AudioBuffer<FT>& buffer) {

    const FT sqrt2 = std::sqrt(FT(2.0));
    auto num_samples = buffer.getNumSamples();

    // ---- MONO parameter
    const StereoMode mode = StereoMode(parameters_.stereo_mode->getIndex());

    // -- GAIN parameter
    float gain = powf(2.f, parameters_.gain->get() / 6.f);

    // INVERTL parameter
    leftGlider_.go(parameters_.invertL->get()); 

    // INVERTR parameter
    rightGlider_.go(parameters_.invertR->get()); 

    // SWAP parameter
    auto swap = parameters_.swap->get();
    swapGlider_.go(swap);

    // MUTE parameter
    auto mute = parameters_.mute->get();
    mute_glider_.go(mute);


    // --- LOOP Start
    auto* channel0_data = buffer.getWritePointer(0);
    auto* channel1_data = buffer.getWritePointer(1);
    for (int i = 0; i < num_samples; ++i) {
        auto in0 = channel0_data[i];
        auto in1 = channel1_data[i];
        auto out0 = in0;
        auto out1 = in1;

        auto mid = (out0 + out1)/sqrt2;
        auto side = (out0 - out1)/sqrt2;


        // mode
        left_left_glider_.go(mode == LeftCopy || mode == Stereo);
        auto left_left = left_left_glider_.nextValue();

        left_mid_glider_.go(mode == MidSide || mode == Mono);
        auto left_mid = left_mid_glider_.nextValue();

        left_right_glider_.go(mode == RightCopy);
        auto left_right = left_right_glider_.nextValue();

        out0 = in0 * left_left + mid * left_mid + 
               in1 * left_right;


        right_right_glider_.go(mode == RightCopy || mode == Stereo);
        auto right_right = right_right_glider_.nextValue();

        right_mid_glider_.go(mode == Mono);
        auto right_mid = right_mid_glider_.nextValue();

        right_side_glider_.go(mode == MidSide);
        auto right_side = right_side_glider_.nextValue();

        right_left_glider_.go(mode == LeftCopy);
        auto right_left = right_left_glider_.nextValue();


        out1 = in1 * right_right + mid * right_mid +
               side * right_side + in0 * right_left;

        // inverting
        out0 = out0 * leftGlider_.nextValue();
        out1 = out1 * rightGlider_.nextValue();

        // Swap the channels
        auto swapVal = swapGlider_.nextValue();
        auto temp = out0;
        out0 = out0 *(1.f-swapVal) + out1 * swapVal;
        out1 = out1 *(1.f-swapVal) + temp * swapVal;


        // gain
        out0 = gain * out0;
        out1 = gain * out1;

        // mute
        auto mute_value = mute_glider_.nextValue();
        out0 = out0 * mute_value;
        out1 = out1 * mute_value;

        // Output
        channel0_data[i] = out0;
        channel1_data[i] = out1;

    }
}
