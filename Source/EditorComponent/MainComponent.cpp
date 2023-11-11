#include "MainComponent.hpp"


 MainComponent::MainComponent(ProcessorParameters *params) {

    DBGLOG("Setting up MainComponent");
    auto apvts = params->apvts.get();

    //==============================================

    monoButton.setButtonText ("Mono");
    monoAttachment.reset (new ButtonAttachment (*apvts, "Mono", monoButton));

    swapButton.setButtonText ("Swap");
    swapAttachment.reset (new ButtonAttachment (*apvts, "Swap", swapButton));

    left_box_.add(monoButton);
    left_box_.add(swapButton);

    rightInvertButton.setButtonText ("Right");
    rightInvertAttachment.reset (new ButtonAttachment (*apvts, "InvertR", rightInvertButton));

    leftInvertButton.setButtonText ("Left");
    leftInvertAttachment.reset (new ButtonAttachment (*apvts, "InvertL", leftInvertButton));

    invert_box_.setText("Invert");
    invert_box_.add(rightInvertButton);
    invert_box_.add(leftInvertButton);

    left_box_.add(invert_box_);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    // 80 and 20 are the defaults baked into the slider pimpl code.
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);
    gainSlider.setTextValueSuffix(" dB");
    gainAttachment.reset (new SliderAttachment (*apvts, "Gain", gainSlider));

    gain_box_.add(gainSlider);
    gain_box_.setText("Gain");

    addAndMakeVisible(left_box_);
    addAndMakeVisible(gain_box_);

#if (0)
    stereoLabel.setText ("Stereo", juce::dontSendNotification);
    addAndMakeVisible (stereoLabel);

    addAndMakeVisible (stereoSlider);
    stereoAttachment.reset (new SliderAttachment (*params, "Stereo", stereoSlider));
#endif

 }


void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    juce::Grid grid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using GridItem = juce::GridItem;

    grid.alignItems = juce::Grid::AlignItems::start;
    grid.justifyContent = juce::Grid::JustifyContent::start;
    grid.justifyItems = juce::Grid::JustifyItems::start;
    grid.templateColumns = { Track (Fr (1)), Track (Fr (2)), Track (Fr (1)) };

    grid.templateRows.add(Track (Fr (1)));

    invert_box_.layoutTemplate = { Track(Fr(1)), Track(Fr(1))};
    left_box_.layoutTemplate =  {Track (Fr (1)), Track (Fr (1)), Track (Fr (2)), Track (Fr (3)) };
    grid.items.add(GridItem(left_box_));

    gain_box_.layoutTemplate = { Track(Fr(5)), Track(Fr(1))};
    grid.items.add(GridItem(gain_box_));


#if (0)
    grid.templateRows.add(Track (Fr (1)));
    grid.items.add(GridItem(stereoLabel));
    grid.items.add(GridItem(stereoSlider).withArea(GridItem::Span (1), GridItem::Span (5)));

#endif
    grid.performLayout (getLocalBounds());
    
}