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

#include "../ProcessorParameters.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

#include "solidfuel/solidfuel.hpp"

using namespace solidfuel;


class StereoModeComponent : public juce::Component {

public:

    StereoModeComponent();

    void set_value_ptr(juce::Value &v);

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::Value value_;

    ValueListener stereo_mode_listener_;

    juce::TextButton mono_button_;
    juce::TextButton stereo_button_;
    juce::TextButton left_button_;
    juce::TextButton right_button_;
    juce::TextButton midside_button_;
    juce::TextButton mid_button_;
    juce::TextButton side_button_;


    void update_mode(StereoMode mode);


    // ===================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoModeComponent)
};
