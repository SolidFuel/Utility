#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

using  SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using  ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

class MainComponent : public juce::Component {

public:

    MainComponent(juce::AudioProcessorValueTreeState *params);

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ToggleButton monoButton;
    std::unique_ptr<ButtonAttachment> monoAttachment;

    juce::ToggleButton swapButton;
    std::unique_ptr<ButtonAttachment> swapAttachment;

    juce::ToggleButton leftInvertButton;
    std::unique_ptr<ButtonAttachment> leftInvertAttachment;

    juce::ToggleButton rightInvertButton;
    std::unique_ptr<ButtonAttachment> rightInvertAttachment;

    juce::Label gainLabel;
    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainAttachment;

#if (0)
    juce::Label stereoLabel;
    juce::Slider stereoSlider;
    std::unique_ptr<SliderAttachment> stereoAttachment;
#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
