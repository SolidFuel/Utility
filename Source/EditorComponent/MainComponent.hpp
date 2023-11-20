/****
 * Chantool - Versatile VST3 Channel Utility for Digital Audio Workstations 
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

#include "../ProcessorParameters.hpp"
#include "../Debug.hpp"
#include "../ValueListener.hpp"
#include "StereoModeComponent.hpp"
#include "MuteModeComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <solidfuel/solidfuel.hpp>

using  SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using  ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

using namespace solidfuel;

class MainComponent : public juce::Component {

public:

    MainComponent(ProcessorParameters *params);

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    using BCO = BoxComponent::Orientation;

    ProcessorParameters* params_;

    // ++++++ Things in the left box
    // -- Stero Mode
    StereoModeComponent stereo_mode_;

    // -- Swap
    juce::ToggleButton swap_button_;
    std::unique_ptr<ButtonAttachment> swapAttachment;

    BoxComponent swap_box_{BCO::Vertical, true};

    // -- Invert
    juce::ToggleButton leftInvertButton;
    std::unique_ptr<ButtonAttachment> leftInvertAttachment;

    juce::ToggleButton rightInvertButton;
    std::unique_ptr<ButtonAttachment> rightInvertAttachment;

    BoxComponent invert_box_{BCO::Vertical, true};

    // -- Mute
    MuteModeComponent mute_mode_;

    // -- Left box itself
    BoxComponent left_box_{BCO::Vertical};

    //++++++ Gain box

    juce::Slider gain_slider_;
    std::unique_ptr<SliderAttachment> gainAttachment;

    BoxComponent gain_box_{BCO::Vertical, true};

    //++++++ 


    // ===================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
