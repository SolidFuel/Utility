#pragma once

#include "ChanToolProcessor.hpp"

#include "EditorComponent/MainComponent.hpp"
#include "EditorComponent/HeaderComponent.hpp"

class ChanToolEditor : public juce::AudioProcessorEditor
{
public:
    explicit ChanToolEditor(ChanToolProcessor&);

private:

    ChanToolProcessor& proc_;

    void paint(juce::Graphics&) override;
    void resized() override;

    HeaderComponent header_component_;
    MainComponent main_component_;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChanToolEditor)
};
