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

#include "HeaderComponent.hpp"

#include <version.hpp>

const std::string about_text = "      " + PLUGIN_NAME_UPPER + "    \n"
    "Version " + PLUGIN_VERSION + " (" + GIT_HASH + ")\n"
    "Copyright (c) 2023 Solid Fuel\n"
    "Licensed under GPL 3 (https://opensource.org/license/gpl-3-0/)\n"
    "Source code : https://github.com/SolidFuel/ChanTool\n"
    "\n"
    "* This program is free software: you can redistribute it and/or modify it\n"
    "* under the terms of the GNU General Public License as published by the \n"
    "* Free Software Foundation, either version 3 of the License, or (at your \n"
    "* option) any later version. This program is distributed in the hope that it \n"
    "* will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty\n"
    "* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file\n"
    "* in the root directory.\n"
    "\n"
    "\n"
    "JUCE Copyright (c) 2022 - Raw Material Software Limited \n"
    "Used by permission under GPL 3\n"
    "Source Code : https://github.com/juce-framework/JUCE\n"
    ;

HeaderComponent::HeaderComponent(ProcessorParameters *params) {

    tooltip_value_.referTo(params->show_tooltips);
    gain_only_value_.referTo(params->show_only_gain);

    nameLabel_.setText (JucePlugin_Name, juce::dontSendNotification);
    nameLabel_.setFont(juce::Font(32.0f, juce::Font::bold));
    nameLabel_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (nameLabel_);

    menuButton_.setButtonText("menu");
    menuButton_.changeWidthToFitText();
    menuButton_.setTriggeredOnMouseDown(true);
    menuButton_.onClick = [this]() { show_menu_(); };

    addAndMakeVisible(menuButton_);

}

void HeaderComponent::paint (juce::Graphics& g) {
    g.fillAll (juce::Colour(0xff060660));

}

//==============================================================================
void HeaderComponent::show_menu_() {
    menuButton_.setEnabled(false);

    juce::PopupMenu menu;

    menu.addItem(3, "Gain Only", true, bool(gain_only_value_.getValue()));
    menu.addItem(2, "Tooltips", true, bool(tooltip_value_.getValue()));
    menu.addItem(1, "About");

    menu.showMenuAsync({}, [this](int r) { process_menu_(r); });


}

//==============================================================================
void HeaderComponent::show_about_box_() {
    auto options = juce::DialogWindow::LaunchOptions();

    auto* te = new juce::TextEditor();

    te->setMultiLine(true);
    te->setText(about_text, false);
    te->setReadOnly(true);

    te->setSize(600, 400);

    options.dialogTitle = "ABOUT " + PLUGIN_NAME_UPPER;
    options.content = juce::OptionalScopedPointer<juce::Component>(te, true);

    options.launchAsync();

}


//==============================================================================
void HeaderComponent::toggle_tooltips_() {
    auto new_value = ! bool(tooltip_value_.getValue());
    tooltip_value_.setValue(new_value);
}

//==============================================================================
void HeaderComponent::toggle_gain_only_() {
    auto new_value = ! bool(gain_only_value_.getValue());
    gain_only_value_.setValue(new_value);
}

//==============================================================================
void HeaderComponent::process_menu_(int results) {
    switch (results) {
        case 1 :
            show_about_box_();
            break;
        case 2 :
            toggle_tooltips_();
            break;
        case 3 :
            toggle_gain_only_();
            break;
        default :
            break;
    }
    menuButton_.setEnabled(true);
}

//==============================================================================
constexpr int MARGIN = 10;
constexpr int LABEL_WIDTH = 220;

void HeaderComponent::resized() {

    //const auto component_width = getWidth();
    const auto component_height = getHeight();

    const auto menu_height = component_height / 2.0f;
    menuButton_.changeWidthToFitText(int(menu_height));
    menuButton_.setTopLeftPosition({MARGIN, int(menu_height / 2.0f)});

    auto button_right_side = menuButton_.getWidth() + MARGIN;

    nameLabel_.setSize(LABEL_WIDTH, component_height-MARGIN);

    auto label_left = (getWidth() - LABEL_WIDTH)/2;

    // The idea is - If the label won't crowd the button, then
    // center the label on the entire window. Otherwise, center it
    // it in the space left after placing the menu button.
    if (label_left - button_right_side < 10 ) {
        auto room = getWidth() - button_right_side;
        auto start = button_right_side + (room - LABEL_WIDTH)/2;

        nameLabel_.setTopLeftPosition(start, MARGIN/2);

    } else {
        nameLabel_.setCentreRelative(0.5f, 0.5f);
    }
}