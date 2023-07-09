#pragma once

#include "PluginProcessor.h"

class NewPluginTemplateAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit NewPluginTemplateAudioProcessorEditor(ChanToolProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};
