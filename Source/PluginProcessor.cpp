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

void ChanToolProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate, samplesPerBlock);

    monoGlider_.forceValue(parameters.mono->get());

    leftGlider_.forceValue(parameters.invertL->get());

    rightGlider_.forceValue(parameters.invertR->get());

};


void ChanToolProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages) {
    juce::ignoreUnused(midiMessages);

    auto num_samples = buffer.getNumSamples();

    // ---- MONO parameter
    bool mono = parameters.mono->get();
    monoGlider_.go(mono);

#if (0)
    // -- STEREO parameter
    float stereo = parameters.stereo->get() / 100.f;
    if (stereo > 1.f) {
        stereo = 1.f + (stereo-1.f)/2.f;
    }
#endif

    // -- GAIN parameter
    float gain = powf(2.f, parameters.gain->get() / 6.f);

    // INVERTL parameter
    leftGlider_.go(parameters.invertL->get()); 

    // INVERTR parameter
    rightGlider_.go(parameters.invertR->get()); 

    // SWAP parameter
    auto swap = parameters.swap->get();
    swapGlider_.go(swap);


    // --- LOOP Start
    auto* channel0_data = buffer.getWritePointer(0);
    auto* channel1_data = buffer.getWritePointer(1);
    for (int i = 0; i < num_samples; ++i) {
        auto in0 = channel0_data[i];
        auto in1 = channel1_data[i];
        float out0 = in0;
        float out1 = in1;

        // mono
        auto val = monoGlider_.nextValue();
        auto mid = (out0 + out1)/2.0f;

        out0 = out0 *(1.f-val) + mid * val;
        out1 = out1 *(1.f-val) + mid * val;

        // gain
        out0 = gain * out0;
        out1 = gain * out1;

        // inverting
        out0 = out0 * leftGlider_.nextValue();
        out1 = out1 * rightGlider_.nextValue();

        // Swap the channels
        auto swapVal = swapGlider_.nextValue();
        out0 = out0 *(1-swapVal) + out1 * swapVal;
        out1 = out1 *(1-swapVal) + out0 * swapVal;

        // Output
        channel0_data[i] = out0;
        channel1_data[i] = out1;

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
