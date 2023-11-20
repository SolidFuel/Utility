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


#include "ProcessorParameters.hpp"

const juce::StringArray mode_choices = {{
    "Mono", "Stero", "Mid/Side", "LeftCopy", "RightCopy"
}};

const juce::StringArray mute_choices = {{
    "Off", "Both", "Left", "Right"
}};

ProcessorParameters::ProcessorParameters(juce::AudioProcessor& processor) {

    using RangedParam = std::unique_ptr<juce::RangedAudioParameter>;

    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    stereo_mode = new juce::AudioParameterChoice({"stereo_mode", 1}, "Stereo Mode", 
            mode_choices, StereoMode::Stereo );
    layout.add(RangedParam(stereo_mode));

    mute = new juce::AudioParameterChoice({"mute", 1}, "Mute", mute_choices, MuteOff);
    layout.add(RangedParam(mute));

    gain = new juce::AudioParameterFloat({"gain", 1}, "Gain", -100.f, 40.f, 0.f);
    layout.add(RangedParam(gain));

    swap = new juce::AudioParameterBool({"swap", 1}, "Swap", false);
    layout.add(RangedParam(swap));

    invertL = new juce::AudioParameterBool({"invert_left", 1}, "InvertL", false);
    layout.add(RangedParam(invertL));

    invertR = new juce::AudioParameterBool({"invert_right", 1}, "InvertR", false);
    layout.add(RangedParam(invertR));

    apvts = std::unique_ptr<juce::AudioProcessorValueTreeState>(
        new juce::AudioProcessorValueTreeState(
        processor, nullptr, "CHANNELTOOLS-PARAMETERS", std::move(layout)));
}

