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

#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

constexpr int GAIN_WIDTH = 300;
constexpr int TOOL_WIDTH = 150;
constexpr int FULL_WIDTH = GAIN_WIDTH + TOOL_WIDTH;

constexpr int HEADER_HEIGHT = 50;
constexpr int PROPERTY_HEIGHT = 320;
constexpr int FULL_HEIGHT = HEADER_HEIGHT + PROPERTY_HEIGHT;

constexpr int MARGIN = 5;


//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p) :
    AudioProcessorEditor(&p), proc_(p),
    header_component_(p.getParameters()),
    main_component_(p.getParameters())
{

    // use a local copy so we don't need to worry about clean up
    // of listeners.
    tooltip_value_.referTo(proc_.getParameters()->show_tooltips);
    tooltip_listener_.onChange = [this](juce::Value &v) { set_tooltips(v); };
    set_tooltips(tooltip_value_);
    tooltip_value_.addListener(&tooltip_listener_);

    gain_only_value_.referTo(proc_.getParameters()->show_only_gain);
    gain_only_listener_.onChange = [this](juce::Value &v) { set_gain_only(v); };
    set_gain_only(gain_only_value_);
    gain_only_value_.addListener(&gain_only_listener_);


    addAndMakeVisible (header_component_);
    addAndMakeVisible (main_component_);

    // This will be done by set_gain_only()
    //setSize(FULL_WIDTH, FULL_HEIGHT);
}

//==============================================================================
void PluginEditor::set_tooltips(juce::Value &v) {
    auto show = bool(v.getValue());

    if (show) {
        if (! tooltip_window_) {
            tooltip_window_ = std::make_unique<juce::TooltipWindow>(this);
        }
    }  else {
        tooltip_window_.reset();
    }
}

//==============================================================================
void PluginEditor::set_gain_only(juce::Value &v) {
    auto gain_only = bool(v.getValue());

    DBGLOG("PluginEditor::set_gain_only -- changing to ", gain_only);

    if (gain_only) {
        current_width_ = GAIN_WIDTH;
    }  else {
        current_width_ = FULL_WIDTH;
    }

    setSize(current_width_,  FULL_HEIGHT);
}

//==============================================================================
void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

//==============================================================================
void PluginEditor::resized()
{
    using FlexItem = juce::FlexItem;
    juce::FlexBox box;

    box.flexDirection = juce::FlexBox::Direction::column;
    box.alignContent = juce::FlexBox::AlignContent::center;

    box.items.add(FlexItem(float(current_width_), float(HEADER_HEIGHT), header_component_));
    box.items.add(FlexItem(float(current_width_-(MARGIN*2)), float(PROPERTY_HEIGHT), main_component_)
            .withMargin(FlexItem::Margin(0, MARGIN, 0, MARGIN)));


    box.performLayout (juce::Rectangle(0, 0, getWidth(), getHeight()));
}
