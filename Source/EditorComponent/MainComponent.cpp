#include "MainComponent.hpp"


 MainComponent::MainComponent(ProcessorParameters *params) : 
        params_(params)
{

    DBGLOG("Setting up MainComponent");
    auto apvts = params->apvts.get();

    mute_value_ = apvts->getParameterAsValue("mute");

    auto stereo_value = apvts->getParameterAsValue("stereo_mode");

    stereo_mode_.set_value_ptr(stereo_value);

    //==============================================
    mute_button_.setButtonText("Mute");
    mute_button_.setClickingTogglesState(true);

    update_mute();
    mute_button_.onClick = [this]() {update_mute(); };
    mute_listener_.onChange = [this](juce::Value &v) {
        auto state = bool(v.getValue());
        mute_button_.setToggleState(state, juce::sendNotification);
    };

    mute_value_.addListener(&mute_listener_);

    left_box_.add(mute_button_, 8, 3);

    //==============================================
    left_box_.add(stereo_mode_);

    //==============================================
    swapButton.setButtonText ("Swap");
    swapAttachment.reset (new ButtonAttachment (*apvts, "swap", swapButton));
    swap_box_.add(swapButton);

    left_box_.add(swap_box_, 5, 0);

    //==============================================
    rightInvertButton.setButtonText ("Right");
    rightInvertAttachment.reset (new ButtonAttachment (*apvts, "invert_right", rightInvertButton));

    leftInvertButton.setButtonText ("Left");
    leftInvertAttachment.reset (new ButtonAttachment (*apvts, "invert_left", leftInvertButton));

    invert_box_.setText("Invert");
    invert_box_.add(rightInvertButton);
    invert_box_.add(leftInvertButton);

    left_box_.add(invert_box_, 5, 0);

    //==============================================
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    // 80 and 20 are the defaults baked into the slider pimpl code.
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);
    gainSlider.setTextValueSuffix(" dB");
    gainAttachment.reset (new SliderAttachment (*apvts, "gain", gainSlider));

    gain_box_.add(gainSlider);
    gain_box_.setText("Gain");
    gain_box_.setMargin({0, 6, 0, 0});

    //==============================================
    addAndMakeVisible(left_box_);
    addAndMakeVisible(gain_box_);

 }

 //============================================================================
void MainComponent::update_mute() {
    auto state = mute_button_.getToggleState();
    mute_button_.setButtonText(state ? "Unmute" : "Mute");
    mute_value_ = state;
}


//============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

//============================================================================
void MainComponent::resized()
{
    juce::Grid grid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using GridItem = juce::GridItem;

    grid.alignItems = juce::Grid::AlignItems::start;
    grid.justifyContent = juce::Grid::JustifyContent::start;
    grid.justifyItems = juce::Grid::JustifyItems::start;
    grid.templateColumns = { Track (Fr (1)), Track (Fr (2)) };

    grid.templateRows.add(Track (Fr (1)));

    invert_box_.layoutTemplate = { Track(Fr(1)), Track(Fr(1))};
    swap_box_.layoutTemplate = { Track(Fr(1)) };
    left_box_.layoutTemplate =  {
        Track(Fr(10)), // Mute
        Track(Fr(30)), // Mode 
        Track(Fr(12)), // Swap
        Track(Fr(20)), // Invert
        Track(Fr( 8)), // SPACER
        };
    grid.items.add(GridItem(left_box_));

    gain_box_.layoutTemplate = { Track(Fr(1))};
    grid.items.add(GridItem(gain_box_));


    grid.performLayout (getLocalBounds());
    
}