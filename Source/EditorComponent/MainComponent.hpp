#pragma once

#include "../ProcessorParameters.hpp"
#include "../ChanTool.hpp"
#include "../ValueListener.hpp"
#include "BoxComponent.hpp"
#include "ButtonGroupComponent.hpp"
#include "StereoModeComponent.hpp"
#include "MuteModeComponent.hpp"

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

    ProcessorParameters* params_;

    // ++++++ Things in the left box
    // -- Stero Mode
    StereoModeComponent stereo_mode_;

    // -- Swap
    juce::ToggleButton swapButton;
    std::unique_ptr<ButtonAttachment> swapAttachment;

    BoxComponent swap_box_{BCO::Vertical, true};

    // -- Invert
    juce::ToggleButton leftInvertButton;
    std::unique_ptr<ButtonAttachment> leftInvertAttachment;

    juce::ToggleButton rightInvertButton;
    std::unique_ptr<ButtonAttachment> rightInvertAttachment;

    BoxComponent invert_box_{BCO::Vertical, true};

    // -- Mute
    MuteModeComponent mute_mode_;

    // -- Left box itself
    BoxComponent left_box_{BCO::Vertical};

    //++++++ Gain box

    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainAttachment;

    BoxComponent gain_box_{BCO::Vertical, true};

    //++++++ 


    // ===================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
