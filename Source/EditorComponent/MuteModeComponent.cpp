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

#include "MuteModeComponent.hpp"

MuteModeComponent::MuteModeComponent() {

    using Conn = juce::Button::ConnectedEdgeFlags;


    left_mute_button_.setButtonText ("L");
    left_mute_button_.setConnectedEdges(Conn::ConnectedOnRight);
    left_mute_button_.setClickingTogglesState(true);
    left_mute_button_.setTooltip("Mute the Left channel of the output.");
    left_listener_.onChange = [this](juce::Value &v) { update_mode(bool(v.getValue()), MuteLeft); };
    left_mute_button_.getToggleStateValue().addListener(&left_listener_);

    both_mute_button_.setButtonText ("Mute");
    both_mute_button_.setConnectedEdges(Conn::ConnectedOnLeft | Conn::ConnectedOnRight);
    both_mute_button_.setClickingTogglesState(true);
    both_mute_button_.setTooltip("Mute both channels of the output");
    both_listener_.onChange = [this](juce::Value &v) { update_mode(bool(v.getValue()), MuteBoth); };
    both_mute_button_.getToggleStateValue().addListener(&both_listener_);

    right_mute_button_.setButtonText ("R");
    right_mute_button_.setConnectedEdges(Conn::ConnectedOnLeft);
    right_mute_button_.setClickingTogglesState(true);
    right_mute_button_.setTooltip("Mute the right channel of the output");
    right_listener_.onChange = [this](juce::Value &v) { update_mode(bool(v.getValue()), MuteRight); };
    right_mute_button_.getToggleStateValue().addListener(&right_listener_);



    mute_mode_listener_.onChange = [this](juce::Value &v) {
        StereoMode new_mode = StereoMode(int(v.getValue()));
        DBGLOG("mute_mode_listener_.onChange call new_mode = ", new_mode);
        working.set(true);
        DBGLOG("  -- mml Left")
        left_mute_button_.setToggleState(new_mode == MuteLeft, juce::sendNotification);
        DBGLOG("  -- mml Both")
        both_mute_button_.setToggleState(new_mode == MuteBoth, juce::sendNotification);
        DBGLOG("  -- mml Right")
        right_mute_button_.setToggleState(new_mode == MuteRight, juce::sendNotification);
        working.set(false);
    };

    // force the GUI to match the model
    mute_mode_listener_.onChange(value_);

    value_.addListener(&mute_mode_listener_);

    addAndMakeVisible(left_mute_button_);
    addAndMakeVisible(both_mute_button_);
    addAndMakeVisible(right_mute_button_);

}

//============================================================================
void MuteModeComponent::set_value_ptr(juce::Value &v) {
    value_.referTo(v);
}
//============================================================================
bool MuteModeComponent::all_off() {
    return ! left_mute_button_.getToggleState() 
        && ! both_mute_button_.getToggleState()
        && ! right_mute_button_.getToggleState();
}
//============================================================================
void MuteModeComponent::update_mode(bool state, MuteMode mode) {
    DBGLOG("MuteModeComponent::update_mode called state = ",
         state, "; mode = ", mode)

    if (state) {
        value_ = mode;
    } else if (all_off()) {
        value_ = MuteOff;
    }
 }



//============================================================================
void MuteModeComponent::paint(juce::Graphics&g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}


//============================================================================
void MuteModeComponent::resized()
{
    juce::Grid grid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using GridItem = juce::GridItem;
    using Span = GridItem::Span;

    grid.alignItems = juce::Grid::AlignItems::center;
    grid.justifyContent = juce::Grid::JustifyContent::center;
    grid.justifyItems = juce::Grid::JustifyItems::center;
    grid.templateColumns = { Track (Fr (1)), Track (Fr (2)), Track(Fr (1)) };
    grid.templateRows = { Track (Fr (1)) };

    grid.items.add(GridItem(left_mute_button_));
    grid.items.add(GridItem(both_mute_button_));
    grid.items.add(GridItem(right_mute_button_));

    auto bounds = getLocalBounds();
    grid.performLayout (bounds);
}