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


#include "../PluginProcessor.hpp"
#include "../PluginEditor.hpp"
#include "../Debug.hpp"

#include "version.hpp"


#if SF_DEBUG
    std::unique_ptr<juce::FileLogger> dbgout = 
        std::unique_ptr<juce::FileLogger>
            (juce::FileLogger::createDateStampedLogger(
                std::string("SolidFuel/") + JucePlugin_Name, "LogFile", 
                ".txt", "---- " + PLUGIN_VERSION + " (" + GIT_HASH +")")
            );
#endif


//============================================================================
PluginProcessor::PluginProcessor() : 
    AudioProcessor(BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters_(*this)
{

}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo() ||
        layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo()) {

        return false;
    }

    return true;
}


//============================================================================
juce::AudioProcessorEditor* PluginProcessor::createEditor() {

    DBGLOG("------- Setting Up Editor -----------");
    return new PluginEditor (*this);
}

//============================================================================
void PluginProcessor::force_gliders() {

    const MuteMode mute_mode = MuteMode(parameters_.mute->getIndex());
    left_mute_glider_.forceValue(mute_mode == MuteBoth || mute_mode == MuteLeft);
    right_mute_glider_.forceValue(mute_mode == MuteBoth || mute_mode == MuteRight);


    leftGlider_.forceValue(parameters_.invertL->get());
    rightGlider_.forceValue(parameters_.invertR->get());

    swapGlider_.forceValue(parameters_.swap->get());
    
    const StereoMode mode = StereoMode(parameters_.stereo_mode->getIndex());
    left_left_glider_.forceValue(mode == LeftCopy || mode == Stereo);
    left_mid_glider_.forceValue(mode == MidSide || mode == Mono || mode == MidCopy);
    left_side_glider_.forceValue(mode == SideCopy);
    left_right_glider_.forceValue(mode == RightCopy);

    right_right_glider_.forceValue(mode == RightCopy || mode == Stereo);
    right_mid_glider_.forceValue(mode == Mono || mode == MidCopy);
    right_side_glider_.forceValue(mode == MidSide || mode == SideCopy);
    right_left_glider_.forceValue(mode == LeftCopy);

    pan_glider_.restart(0.5, parameters_.pan->get(), GLIDER_TIMING);
    gain_glider_.restart(0.0, parameters_.gain->get(), GLIDER_TIMING);

}


//============================================================================
// Serialize Parameters for the host to save for us.
//

constexpr int CURRENT_STATE_VERSION = 1;
const juce::String XML_TOP_TAG = "ChanTool-Preset";

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {

    DBGLOG("GET STATE called");

    auto xml = std::make_unique<juce::XmlElement>(XML_TOP_TAG);
    xml->setAttribute("version", CURRENT_STATE_VERSION);

    DBGLOG("  Created Top")


    //--------------------------------------
    auto state = parameters_.apvts->copyState();
    auto apvts_xml = state.createXml();
    // createXml gives back a unqiue_ptr. So we need to unwrap it.
    xml->addChildElement(apvts_xml.release());
    DBGLOG("  Wrote ValueTree")

    //--------------------------------------
    auto child = xml->createNewChildElement("GUI-Parameters");
    child->setAttribute("show_tooltips", bool(parameters_.show_tooltips.getValue()));
    child->setAttribute("show_only_gain", bool(parameters_.show_only_gain.getValue()));

    //--------------------------------------
    DBGLOG("XML out =", xml->toString());
    copyXmlToBinary(*xml, destData);
    DBGLOG("  Done")

}

//============================================================================
void PluginProcessor::parseCurrentXml(const juce::XmlElement * elem) {

    DBGLOG("PluginProcessor::parseCurrentXml called")

    auto *child = elem->getChildByName(parameters_.apvts->state.getType());
    if (child) {
        parameters_.apvts->replaceState(juce::ValueTree::fromXml(*child));

        // Are these forces a good idea ?
        // If it is before prepareToPlay() - it will do the same thing
        // If it is after  prepareToPlay() - then processBlock() has been
        //     running. Don't we want to glide to the new values ?
        //
        force_gliders();
    }
    DBGLOG(" -- apvts  done")

    child = elem->getChildByName("GUI-Parameters");
    if (child) {
        parameters_.show_tooltips = child->getBoolAttribute("show_tooltips", 
            bool(parameters_.show_tooltips.getValue()));
        parameters_.show_only_gain = child->getBoolAttribute("show_only_gain", 
            bool(parameters_.show_only_gain.getValue()));
    }

    DBGLOG(" -- others done")



}

//============================================================================
// Read Serialize Parameters from the host and set our state.
//
void PluginProcessor::setStateInformation (const void* data, int sizeInBytes) {
    DBGLOG("SET STATE called");

    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml) {
        DBGLOG("XML in =", xml->toString());

        if (xml->hasTagName(XML_TOP_TAG)) {
            int version = xml->getIntAttribute("version");
            if (version == CURRENT_STATE_VERSION) {
                parseCurrentXml(xml.get());
            } else {
                jassert(false);
            }
        }

    }  else {
        DBGLOG("   NO XML decoded")
    }
}


//============================================================================
// This creates new instances of the plugin..

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
