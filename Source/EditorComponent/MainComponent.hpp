#pragma once

#include "../ProcessorParameters.hpp"
#include "../ChanTool.hpp"
#include "../ValueListener.hpp"
#include "BoxComponent.hpp"
#include "ButtonGroupComponent.hpp"
#include "StereoModeComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

using  SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using  ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

class MainComponent : public juce::Component {

public:

    MainComponent(ProcessorParameters *params);

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    using BCO = BoxComponent::Orientation;
    static constexpr int STEREO_MODE_GROUP_ID = 1001;

    ProcessorParameters* params_;

    juce::TextButton mute_button_;
    juce::Value mute_value_;
    ValueListener mute_listener_;

    StereoModeComponent stereo_mode_;

    juce::ToggleButton swapButton;
    std::unique_ptr<ButtonAttachment> swapAttachment;

    BoxComponent swap_box_{BCO::Vertical, true};

    juce::ToggleButton leftInvertButton;
    std::unique_ptr<ButtonAttachment> leftInvertAttachment;

    juce::ToggleButton rightInvertButton;
    std::unique_ptr<ButtonAttachment> rightInvertAttachment;

    BoxComponent invert_box_{BCO::Vertical, true};

    BoxComponent left_box_{BCO::Vertical};


    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainAttachment;

    BoxComponent gain_box_{BCO::Vertical, true};

    void update_mute();

    // ===================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
