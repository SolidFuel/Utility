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


#include "../PluginProcessor.hpp"

#include "../Debug.hpp"

#include <cmath>


#if NANCHECK
std::unique_ptr<juce::FileLogger> nan_dbgout;
#endif

//============================================================================
void PluginProcessor::prepareToPlay(double, int) {

    force_gliders();

}

//============================================================================
void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer&) {
    process_samples(buffer);
}

//============================================================================
void PluginProcessor::processBlock(juce::AudioBuffer<double>& buffer,
                                    juce::MidiBuffer&) {
    process_samples(buffer);
}


//============================================================================
template <class FT>
void PluginProcessor::process_samples(juce::AudioBuffer<FT>& buffer) {

    const FT sqrt2 = std::sqrt(FT(2.0));
    auto num_samples = buffer.getNumSamples();

    // ---- Stero Mode parameter
    const StereoMode mode = StereoMode(parameters_.stereo_mode->getIndex());
    left_left_glider_.go(mode == LeftCopy || mode == Stereo);
    left_mid_glider_.go(mode == MidSide || mode == Mono || mode == MidCopy);
    left_side_glider_.go(mode == SideCopy);
    left_right_glider_.go(mode == RightCopy);

    right_right_glider_.go(mode == RightCopy || mode == Stereo);
    right_mid_glider_.go(mode == Mono || mode == MidCopy);
    right_side_glider_.go(mode == MidSide || mode == SideCopy);
    right_left_glider_.go(mode == LeftCopy);

    // -- GAIN parameter
    float gain = std::pow(10.f, parameters_.gain->get() / 20.f);

    // INVERTL parameter
    leftGlider_.go(parameters_.invertL->get()); 

    // INVERTR parameter
    rightGlider_.go(parameters_.invertR->get()); 

    // SWAP parameter
    auto swap = parameters_.swap->get();
    swapGlider_.go(swap);

    // MUTE parameter
    const auto mute = MuteMode(parameters_.mute->getIndex());
    left_mute_glider_.go(mute == MuteBoth || mute == MuteLeft);
    right_mute_glider_.go(mute == MuteBoth || mute == MuteRight);


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


        // stereo mode
        auto left_left = left_left_glider_.nextValue();
        auto left_mid = left_mid_glider_.nextValue();
        auto left_side = left_side_glider_.nextValue();
        auto left_right = left_right_glider_.nextValue();

        out0 = in0 * left_left + mid * left_mid + 
               in1 * left_right + side * left_side;

        auto right_right = right_right_glider_.nextValue();
        auto right_mid = right_mid_glider_.nextValue();
        auto right_side = right_side_glider_.nextValue();
        auto right_left = right_left_glider_.nextValue();

        out1 = in1 * right_right + mid * right_mid +
               in0 * right_left + side * right_side;

        // inverting
        out0 = out0 * leftGlider_.nextValue();
        out1 = out1 * rightGlider_.nextValue();

        // Swap the channels
        auto swap_value = swapGlider_.nextValue();
        auto temp = out0;
        out0 = out0 *(1.f-swap_value) + out1 * swap_value;
        out1 = out1 *(1.f-swap_value) + temp * swap_value;


        // gain
        out0 = gain * out0;
        out1 = gain * out1;

        // mute
        auto left_mute_value = left_mute_glider_.nextValue();
        auto right_mute_value = right_mute_glider_.nextValue();

        out0 = out0 * left_mute_value;
        out1 = out1 * right_mute_value;

        // --- OUTPUT ---
        channel0_data[i] = out0;
        channel1_data[i] = out1;

    #if NANCHECK
        if (std::isnan(out0) || std::isnan(out1)) {
            if (! nan_dbgout) {
                nan_dbgout = 
                    std::unique_ptr<juce::FileLogger>
                        (juce::FileLogger::createDateStampedLogger(JucePlugin_Name, "NANCHECK", ".txt", "--------NANCHECK--------"));
            }

            nan_dbgout->logMessage(concat(
                "in0 = ", in0,
                "; in1 = ", in1,
                "; out0 = ", out0,
                "; out1 = ", out1,
                "; mid = ", mid,
                "; side = ", side,
                "\n mode = ", mode,
                "; raw gain = ", parameters_.gain->get(),
                "; comp gain = ", gain,
                "\n :MODE 0: ll = ", left_left, 
                "; lr = ", left_right,
                "; lm = ", left_mid,
                "; ls = ", left_side,
                "\n :MODE 1: rl = ", right_left, 
                "; rr = ", right_right,
                "; rm = ", right_mid,
                "; rs = ", right_side
            ));
        }
    #endif

    }
}
