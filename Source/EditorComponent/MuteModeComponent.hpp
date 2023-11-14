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

#include "../ValueListener.hpp"
#include "../ProcessorParameters.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

class MuteModeComponent : public juce::Component {

public:

    MuteModeComponent();

    void set_value_ptr(juce::Value &v);

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::Value value_;

    ValueListener mute_mode_listener_;

    juce::TextButton left_mute_button_;
    ValueListener left_listener_;
    juce::TextButton both_mute_button_;
    ValueListener both_listener_;
    juce::TextButton right_mute_button_;
    ValueListener right_listener_;

    juce::Atomic<bool> working = false;

    void update_mode(bool state, MuteMode mode);

    bool all_off();


    // ===================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MuteModeComponent)
};
