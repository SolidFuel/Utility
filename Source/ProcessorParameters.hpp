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

#include <juce_audio_processors/juce_audio_processors.h>

#include <memory>
 

// If adding to this, be sure mode_choices in ProcessorParameters.cpp stay
// in synch.
enum StereoMode {
    Mono, Stereo, MidSide, LeftCopy, RightCopy, MidCopy, SideCopy
};

enum MuteMode {
    MuteOff, MuteBoth, MuteLeft, MuteRight
};

struct ProcessorParameters  {     

    juce::AudioParameterChoice* stereo_mode;
    juce::AudioParameterChoice* mute; 
    juce::AudioParameterFloat* gain;
    juce::AudioParameterBool* swap;
    juce::AudioParameterBool* invertL;
    juce::AudioParameterBool* invertR;
    juce::AudioParameterBool* dc_offset;

    std::unique_ptr<juce::AudioProcessorValueTreeState> apvts;

    juce::Value show_tooltips{juce::var{true}};

    ProcessorParameters(juce::AudioProcessor& processor); 
};