#include "PluginProcessor.h"
#include "PluginEditor.h"

ChanToolProcessor::ChanToolProcessor()
{
    parameters.add(*this);
}

void ChanToolProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages) {
    juce::ignoreUnused(midiMessages);

    auto num_samples = buffer.getNumSamples();
    float gain = powf(2.f, parameters.gain->get() / 6.f);

    if (parameters.mono->get()) {
        auto* channel0_data = buffer.getWritePointer(0);
        auto* channel1_data = buffer.getWritePointer(1);
        for (int i = 0; i < num_samples; ++i) {
            float output = gain * (channel0_data[i] + channel1_data[i])/ 2.0f;
            channel0_data[i] = output;
            channel1_data[i] = output;
        }

    } else {
        buffer.applyGain(gain);
    }
        
}
juce::AudioProcessorEditor* ChanToolProcessor::createEditor() {
    return new NewPluginTemplateAudioProcessorEditor(*this);
}

void ChanToolProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    //Serializes your parameters, and any other potential data into an XML:

    juce::ValueTree params("Params");

    for (auto& param: getParameters())
    {
        juce::ValueTree paramTree(PluginHelpers::getParamID(param));
        paramTree.setProperty("Value", param->getValue(), nullptr);
        params.appendChild(paramTree, nullptr);
    }

    juce::ValueTree pluginPreset("MyPlugin");
    pluginPreset.appendChild(params, nullptr);
    //This a good place to add any non-parameters to your preset

    copyXmlToBinary(*pluginPreset.createXml(), destData);
}

void ChanToolProcessor::setStateInformation(const void* data,
                                                          int sizeInBytes)
{
    //Loads your parameters, and any other potential data from an XML:

    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr)
    {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param: getParameters())
        {
            auto paramTree = params.getChildWithName(PluginHelpers::getParamID(param));

            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }

        //Load your non-parameter data now
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChanToolProcessor();
}
