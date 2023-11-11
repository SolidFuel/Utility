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

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
 

struct ProcessorParameters  {     

    juce::AudioParameterBool* mono; 
    juce::AudioParameterFloat* gain;
    juce::AudioParameterFloat* stereo;
    juce::AudioParameterBool* swap;
    juce::AudioParameterBool* invertL;
    juce::AudioParameterBool* invertR;

    std::unique_ptr<juce::AudioProcessorValueTreeState> apvts;

    ProcessorParameters(juce::AudioProcessor& processor); 
};