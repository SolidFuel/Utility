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


#include "ProcessorParameters.hpp"

ProcessorParameters::ProcessorParameters(juce::AudioProcessor& processor) {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    mono = new juce::AudioParameterBool({"Mono", 1}, "Mono", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(mono));

    gain = new juce::AudioParameterFloat({"Gain", 1}, "Gain", -100.f, 40.f, 0.f);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(gain));

    stereo = new juce::AudioParameterFloat({"Stereo", 1}, "Stereo", 0.f, 200.f, 100.f);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(stereo));

    swap = new juce::AudioParameterBool({"Swap", 1}, "Swap", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(swap));

    invertL = new juce::AudioParameterBool({"InvertL", 1}, "InvertL", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(invertL));

    invertR = new juce::AudioParameterBool({"InvertR", 1}, "InvertR", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(invertR));

    apvts = std::unique_ptr<juce::AudioProcessorValueTreeState>(
        new juce::AudioProcessorValueTreeState(
        processor, nullptr, "CHANNELTOOLS-PARAMETERS", std::move(layout)));
}

