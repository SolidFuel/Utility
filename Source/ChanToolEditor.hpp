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

#include "ChanToolProcessor.hpp"

#include "EditorComponent/MainComponent.hpp"
#include "EditorComponent/HeaderComponent.hpp"

#include <memory>

class ChanToolEditor : public juce::AudioProcessorEditor
{
public:
    explicit ChanToolEditor(ChanToolProcessor&);

private:

    ChanToolProcessor& proc_;

    std::unique_ptr<juce::TooltipWindow> tooltipWindow;

    void paint(juce::Graphics&) override;
    void resized() override;

    HeaderComponent header_component_;
    MainComponent main_component_;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChanToolEditor)
};
