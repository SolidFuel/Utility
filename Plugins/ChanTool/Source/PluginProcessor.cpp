#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <memory>

ChanToolProcessor::Parameters::Parameters(ChanToolProcessor& processor) {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    mono = new juce::AudioParameterBool({"Mono", 1}, "Mono", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(mono));

    gain = new juce::AudioParameterFloat({"Gain", 1}, "Gain", -100.f, 40.f, 0.f);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(gain));

    stereo = new juce::AudioParameterFloat({"Stereo", 1}, "Stereo", 0.f, 200.f, 100.f);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(stereo));

    swap = new juce::AudioParameterBool({"Swap", 1}, "Swap", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(swap));

    invertL = new juce::AudioParameterBool({"InvertL", 1}, "InvertL", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(invertL));

    invertR = new juce::AudioParameterBool({"InvertR", 1}, "InvertR", false);
    layout.add(std::unique_ptr<juce::RangedAudioParameter>(invertR));

    apvts = std::unique_ptr<juce::AudioProcessorValueTreeState>(
        new juce::AudioProcessorValueTreeState(
        processor, nullptr, "CHANNELTOOLS-PARAMETERS", std::move(layout)));
}



ChanToolProcessor::ChanToolProcessor() : parameters(*this)
{
}

void ChanToolProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages) {
    juce::ignoreUnused(midiMessages);

    auto num_samples = buffer.getNumSamples();
    float gain = powf(2.f, parameters.gain->get() / 6.f);
    float stereo = parameters.stereo->get() / 100.f;
    if (stereo > 1.f) {
        stereo = 1.f + (stereo-1.f)/2.f;
    }
    bool mono = parameters.mono->get();

    float l_delta = 0.0;
    float l_factor = invertL_old ? -1.f : 1.f;

    if (invertL_old != parameters.invertL->get() ) {
        l_delta = (2.f / (num_samples-1)) * (-l_factor);
        invertL_old = !invertL_old;
    }

    float r_delta = 0.0;
    float r_factor = invertR_old ? -1.f : 1.f;

    if (invertR_old != parameters.invertR->get() ) {
        r_delta = (2.f / (num_samples-1)) * (-r_factor);
        invertR_old = !invertR_old;
    }

    auto* channel0_data = buffer.getWritePointer(0);
    auto* channel1_data = buffer.getWritePointer(1);
    for (int i = 0; i < num_samples; ++i) {
        auto in0 = channel0_data[i];
        auto in1 = channel1_data[i];
        float out0 = in0;
        float out1 = in1;

        if (mono) {
            float output = gain * (channel0_data[i] + channel1_data[i])/ 2.0f;
            out0 = out1 = output;
        } else {
            auto mid = (in0 + in1)/2.0f;
            auto side = (in0 - in1)/2.0f;
            if (stereo <  0.01f) {
                out0 = gain * mid;
                out1 = gain * mid;
            } else {
                out0 = gain * ((2.f - stereo) * mid + (stereo * side)) / 2.f;
                out1 = gain * ((2.f - stereo) * mid - (stereo * side)) / 2.f;
            }

        }

        // inverting
        out0 = out0 * l_factor;
        l_factor += l_delta;

        out1 = out1 * r_factor;
        r_factor += r_delta;

        if (parameters.swap->get()) {
            channel1_data[i] = out0;
            channel0_data[i] = out1;
        } else {
            channel0_data[i] = out0;
            channel1_data[i] = out1;
        }
    }


    if (parameters.mono->get()) {

    } else {
        buffer.applyGain(gain);
    }
        
}
juce::AudioProcessorEditor* ChanToolProcessor::createEditor() {
    return new ChanToolEditor(*this);
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
        }
    }  
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChanToolProcessor();
}
