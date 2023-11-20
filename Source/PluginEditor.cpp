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

#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

constexpr int WIDTH = 450;
constexpr int HEADER_HEIGHT = 50;
constexpr int PROPERTY_HEIGHT = 300;
constexpr int HEIGHT = HEADER_HEIGHT + PROPERTY_HEIGHT;
constexpr int MARGIN = 5;


//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p) :
     AudioProcessorEditor(&p), proc_(p),
    main_component_(p.getChanToolParameters())
{

    tooltipWindow = std::make_unique<juce::TooltipWindow>(this);

    addAndMakeVisible (header_component_);
    addAndMakeVisible (main_component_);

    setSize(WIDTH, HEIGHT);
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

    box.items.add(FlexItem(float(WIDTH), float(HEADER_HEIGHT), header_component_));
    box.items.add(FlexItem(float(WIDTH-(MARGIN*2)), float(PROPERTY_HEIGHT), main_component_)
            .withMargin(FlexItem::Margin(0, MARGIN, 0, MARGIN)));


    box.performLayout (juce::Rectangle(0, 0, getWidth(), getHeight()));
}
