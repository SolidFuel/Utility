#pragma once

#include "PluginProcessor.h"

class ChanToolEditor : public juce::AudioProcessorEditor
{
public:
    explicit ChanToolEditor(ChanToolProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};
