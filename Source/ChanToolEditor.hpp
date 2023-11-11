#pragma once

#include "ChanToolProcessor.hpp"

#include "MainComponent.hpp"

class ChanToolEditor : public juce::AudioProcessorEditor
{
public:
    explicit ChanToolEditor(ChanToolProcessor&);

private:

    ChanToolProcessor& proc_;

    void paint(juce::Graphics&) override;
    void resized() override;

    MainComponent mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChanToolEditor)
};
