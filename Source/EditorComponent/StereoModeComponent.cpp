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

#include "StereoModeComponent.hpp"

constexpr int MODE_GROUP_ID = 1100;

StereoModeComponent::StereoModeComponent() {

    using Conn = juce::Button::ConnectedEdgeFlags;


    mono_button_.setButtonText ("Mono");
    mono_button_.setConnectedEdges(Conn::ConnectedOnBottom);
    mono_button_.setClickingTogglesState(true);
    mono_button_.setRadioGroupId(MODE_GROUP_ID);
    mono_button_.setTooltip("Sum the two input channels and send to both output channels.");
    mono_button_.onClick = [this]() { update_mode(Mono); };

    stereo_button_.setButtonText ("Stereo");
    stereo_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnBottom);
    stereo_button_.setClickingTogglesState(true);
    stereo_button_.setRadioGroupId(MODE_GROUP_ID);
    stereo_button_.setTooltip("'Normal' stereo mode.");
    stereo_button_.onClick = [this]() { update_mode(Stereo); };

    left_button_.setButtonText ("L");
    left_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnBottom);
    left_button_.setClickingTogglesState(true);
    left_button_.setRadioGroupId(MODE_GROUP_ID);
    left_button_.setTooltip("Send the left input channel to both output channels");
    left_button_.onClick = [this]() { update_mode(LeftCopy); };

    right_button_.setButtonText ("R");
    right_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnBottom);
    right_button_.setClickingTogglesState(true);
    right_button_.setRadioGroupId(MODE_GROUP_ID);
    right_button_.setTooltip("Send the right input channel to both output channels");
    right_button_.onClick = [this]() { update_mode(RightCopy); };

    midside_button_.setButtonText ("M/S");
    midside_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnRight | Conn::ConnectedOnLeft );
    midside_button_.setClickingTogglesState(true);
    midside_button_.setRadioGroupId(MODE_GROUP_ID);
    midside_button_.setTooltip("Compute mid and side channels. Send mid to left and side to right.");
    midside_button_.onClick = [this]() { update_mode(MidSide); };

    mid_button_.setButtonText ("M");
    mid_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnRight);
    mid_button_.setClickingTogglesState(true);
    mid_button_.setRadioGroupId(MODE_GROUP_ID);
    mid_button_.setTooltip("Send the mid channel to both output channels");
    mid_button_.onClick = [this]() { update_mode(MidCopy); };

    side_button_.setButtonText ("S");
    side_button_.setConnectedEdges(Conn::ConnectedOnTop | Conn::ConnectedOnLeft);
    side_button_.setClickingTogglesState(true);
    side_button_.setRadioGroupId(MODE_GROUP_ID);
    side_button_.setTooltip("Send the side channel to both output channels");
    side_button_.onClick = [this]() { update_mode(SideCopy); };



    stereo_mode_listener_.onChange = [this](juce::Value &v) {
        StereoMode new_mode = StereoMode(int(v.getValue()));
        switch(new_mode) {
            case Mono :
                mono_button_.setToggleState(true, juce::sendNotification);
                break;
            case Stereo :
                stereo_button_.setToggleState(true, juce::sendNotification);
                break;
            case MidSide :
                midside_button_.setToggleState(true, juce::sendNotification);
                break;
            case LeftCopy :
                left_button_.setToggleState(true, juce::sendNotification);
                break;
            case RightCopy :
                right_button_.setToggleState(true, juce::sendNotification);
                break;
            case MidCopy :
                mid_button_.setToggleState(true, juce::sendNotification);
                break;
            case SideCopy :
                side_button_.setToggleState(true, juce::sendNotification);
                break;

            default :
                jassertfalse;
        }
    };

    // force the GUI to match the model
    stereo_mode_listener_.onChange(value_);

    value_.addListener(&stereo_mode_listener_);

    addAndMakeVisible(mono_button_);
    addAndMakeVisible(stereo_button_);
    addAndMakeVisible(midside_button_);
    addAndMakeVisible(left_button_);
    addAndMakeVisible(right_button_);
    addAndMakeVisible(mid_button_);
    addAndMakeVisible(side_button_);

}

//============================================================================
void StereoModeComponent::set_value_ptr(juce::Value &v) {
    value_.referTo(v);
}

//============================================================================
void StereoModeComponent::update_mode(StereoMode mode) {
    value_ = mode;
 }



//============================================================================
void StereoModeComponent::paint(juce::Graphics&g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}


//============================================================================
void StereoModeComponent::resized()
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
    grid.templateRows = { Track (Fr (1)), Track (Fr (1)), Track(Fr (1)) };

    grid.items.add(GridItem(mono_button_).withArea(Span(1), Span(3)));

    grid.items.add(GridItem(left_button_).withArea(Span(1), Span(1)));
    grid.items.add(GridItem(stereo_button_).withArea(Span(1), Span(1)));
    grid.items.add(GridItem(right_button_).withArea(Span(1), Span(1)));

    grid.items.add(GridItem(mid_button_).withArea(Span(1), Span(1)));
    grid.items.add(GridItem(midside_button_).withArea(Span(1), Span(1)));
    grid.items.add(GridItem(side_button_).withArea(Span(1), Span(1)));


    auto bounds = getLocalBounds();
    bounds.removeFromTop(8);

    grid.performLayout (bounds);
}