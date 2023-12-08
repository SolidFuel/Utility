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

#include "PluginProcessor.hpp"

#include "EditorComponent/MainComponent.hpp"
#include "EditorComponent/HeaderComponent.hpp"

#include <memory>

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor&);

private:

    PluginProcessor& proc_;

    juce::Value tooltip_value_{juce::var{true}};
    ValueListener tooltip_listener_;
    juce::Value gain_only_value_{juce::var{false}};
    ValueListener gain_only_listener_;

    std::unique_ptr<juce::TooltipWindow> tooltip_window_;

    void paint(juce::Graphics&) override;
    void resized() override;

    void set_tooltips(juce::Value &v);
    void set_gain_only(juce::Value &v);

    HeaderComponent header_component_;
    MainComponent main_component_;

    int current_width_ = 100;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
