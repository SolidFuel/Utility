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

#include "MainComponent.hpp"


 MainComponent::MainComponent(ProcessorParameters *params) : 
        params_(params)
{

    DBGLOG("Setting up MainComponent");
    auto apvts = params->apvts.get();

    auto stereo_value = apvts->getParameterAsValue("stereo_mode");
    stereo_mode_.set_value_ptr(stereo_value);

    auto mute_value_ = apvts->getParameterAsValue("mute");
    mute_mode_.set_value_ptr(mute_value_);

    //==============================================
    
    left_box_.add(stereo_mode_);

    //==============================================
    swap_button_.setButtonText("Swap");
    swap_button_.setTooltip("Swap the output channels");
    swapAttachment.reset (new ButtonAttachment (*apvts, "swap", swap_button_));
    swap_box_.add(swap_button_);

    left_box_.add(swap_box_, 5, 0);

    //==============================================
    rightInvertButton.setButtonText ("Right");
    rightInvertButton.setTooltip("Invert the polarity of the right output channel");
    rightInvertAttachment.reset (new ButtonAttachment (*apvts, "invert_right", rightInvertButton));

    leftInvertButton.setButtonText ("Left");
    leftInvertButton.setTooltip("Invert the polarity of the left output channel");
    leftInvertAttachment.reset (new ButtonAttachment (*apvts, "invert_left", leftInvertButton));

    invert_box_.setText("Invert");
    invert_box_.add(rightInvertButton);
    invert_box_.add(leftInvertButton);

    left_box_.add(invert_box_, 5, 3);

    //==============================================
    left_box_.add(mute_mode_, 0, 10);

    //==============================================
    offset_button_.setButtonText("DC Offset");
    offset_button_.setTooltip("Remove any DC component");
    offsetAttachment.reset (new ButtonAttachment (*apvts, "dc_offset", offset_button_));
    offset_box_.add(offset_button_);

    left_box_.add(offset_box_, 5, 0);

    left_box_.setMargin(0, 5);
    left_box_.setGap(5);

    //==============================================
    gain_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    // 80 and 20 are the defaults baked into the slider pimpl code.
    gain_slider_.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);
    gain_slider_.setTextValueSuffix(" dB");
    gain_slider_.setTooltip("Adjust the gain of the output");
    gainAttachment.reset (new SliderAttachment (*apvts, "gain", gain_slider_));

    gain_box_.add(gain_slider_);
    gain_box_.setText("Gain");
    gain_box_.setMargin({0, 6, 0, 0});

    right_box_.add(gain_box_);

    pan_slider_.setTooltip("Pan output left/right");
    // make the textbox read-only
    pan_slider_.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, true, 50, 20);
    panAttachment.reset (new SliderAttachment (*apvts, "pan", pan_slider_));
    pan_box_.add(pan_slider_);
    pan_box_.setMargin({5, 0, 0, 0});

    right_box_.add(pan_box_);

    right_box_.setMargin({0, 6, 0, 0});

    //==============================================
    addAndMakeVisible(left_box_);
    addAndMakeVisible(right_box_);

 }


//============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

//============================================================================
void MainComponent::resized()
{
    juce::Grid grid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using Px = juce::Grid::Px;
    using GridItem = juce::GridItem;

    grid.alignItems = juce::Grid::AlignItems::start;
    grid.justifyContent = juce::Grid::JustifyContent::start;
    grid.justifyItems = juce::Grid::JustifyItems::start;

    grid.rowGap = juce::Grid::Px(5);
    grid.templateRows = { Track (Fr (1)) };

    if (! bool(params_->show_only_gain.getValue())) {
        DBGLOG("MainComponent::resized --- Showing both sides")
        grid.templateColumns = { Track (Fr (1)), Track (Fr (2)) };

        invert_box_.layoutTemplate = { Track(Fr(1)), Track(Fr(1))};
        swap_box_.layoutTemplate = { Track(Fr(1)) };
        offset_box_.layoutTemplate = { Track(Fr(1)) };
        left_box_.layoutTemplate =  {
            Track(Fr(30)), // Mode 
            Track(Fr(12)), // Swap
            Track(Fr(20)), // Invert
            Track(Fr(10)), // Mute
            Track(Fr(12)), // DC Offset
            };
        left_box_.setVisible(true);
        grid.items.add(GridItem(left_box_).withMargin({0, 5, 7, 0 }));
    } else {
        left_box_.setVisible(false);
        grid.templateColumns = { Track (Fr (1)) };
        DBGLOG("MainComponent::resized --- Showing only gain side")

    }


    gain_box_.layoutTemplate = { Track(Fr(1)) };
    pan_box_.layoutTemplate = { Track(Fr(1)) };

    right_box_.layoutTemplate = { Track(Fr(1)), Track(Px(35)) };

    grid.items.add(GridItem(right_box_).withMargin({5, 5, 10, 2 }));


    grid.performLayout (getLocalBounds());
    
}