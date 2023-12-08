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

class HeaderComponent : public juce::Component {

public:

    HeaderComponent(ProcessorParameters *params);

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Label nameLabel_;

    juce::TextButton menuButton_;

    juce::Value tooltip_value_{juce::var{true}};
    juce::Value gain_only_value_{juce::var{false}};

    void show_menu_();
    void process_menu_(int results);
    void show_about_box_();
    void toggle_tooltips_();
    void toggle_gain_only_();

//==========================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)

};
