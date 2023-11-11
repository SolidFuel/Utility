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


#include "../ChanToolProcessor.hpp"
#include "../ChanToolEditor.hpp"
#include "../ChanTool.hpp"

#if CHANTOOL_DEBUG
    std::unique_ptr<juce::FileLogger> dbgout = 
        std::unique_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("ChanTool", "ChanToolLogFile", ".txt", "--------V1--------"));
#endif


ChanToolProcessor::ChanToolProcessor() : parameters(*this){
}

juce::AudioProcessorEditor* ChanToolProcessor::createEditor() {

    DBGLOG("------- Setting Up Editor -----------");
    return new ChanToolEditor (*this);
}

void ChanToolProcessor::getStateInformation(juce::MemoryBlock& destData) {

    auto state = parameters.apvts->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
  
}

void ChanToolProcessor::setStateInformation(const void* data,
                                            int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName(parameters.apvts->state.getType())) {
            parameters.apvts->replaceState(juce::ValueTree::fromXml(*xmlState));
            leftGlider_.forceValue(parameters.invertL->get());
            rightGlider_.forceValue(parameters.invertR->get());
            monoGlider_.forceValue(parameters.mono->get());
        }
    }  
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChanToolProcessor();
}
