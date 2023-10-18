#include "MainComponent.h"


 MainComponent::MainComponent(juce::AudioProcessorValueTreeState *params) {
    monoButton.setButtonText ("Mono");
    addAndMakeVisible (monoButton);
    monoAttachment.reset (new ButtonAttachment (*params, "Mono", monoButton));

    swapButton.setButtonText ("Swap");
    addAndMakeVisible (swapButton);
    swapAttachment.reset (new ButtonAttachment (*params, "Swap", swapButton));

    rightInvertButton.setButtonText ("InvertR");
    addAndMakeVisible (rightInvertButton);
    rightInvertAttachment.reset (new ButtonAttachment (*params, "InvertR", rightInvertButton));

    leftInvertButton.setButtonText ("InvertL");
    addAndMakeVisible (leftInvertButton);
    leftInvertAttachment.reset (new ButtonAttachment (*params, "InvertL", leftInvertButton));

    gainLabel.setText ("Gain", juce::dontSendNotification);
    addAndMakeVisible (gainLabel);

    addAndMakeVisible (gainSlider);
    gainAttachment.reset (new SliderAttachment (*params, "Gain", gainSlider));


    stereoLabel.setText ("Stereo", juce::dontSendNotification);
    addAndMakeVisible (stereoLabel);

    addAndMakeVisible (stereoSlider);
    stereoAttachment.reset (new SliderAttachment (*params, "Stereo", stereoSlider));

    setSize (600, 400);

 }


void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    juce::Grid outerGrid;
 
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using GridItem = juce::GridItem;
    // using FlexItem = juce::FlexItem;

    outerGrid.alignItems = juce::Grid::AlignItems::start;
    outerGrid.justifyContent = juce::Grid::JustifyContent::start;
    outerGrid.justifyItems = juce::Grid::JustifyItems::start;
    outerGrid.templateColumns = { Track (Fr (1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    outerGrid.templateRows.add(Track (Fr (1)));
    outerGrid.items.add(GridItem(monoButton).withArea(1, GridItem::Span (3)));
    outerGrid.items.add(GridItem(swapButton).withArea(1, GridItem::Span (3)));

    outerGrid.templateRows.add(Track (Fr (1)));
    outerGrid.items.add(GridItem(leftInvertButton).withArea(2, GridItem::Span (3)));
    outerGrid.items.add(GridItem(rightInvertButton).withArea(2, GridItem::Span (3)));

    outerGrid.templateRows.add(Track (Fr (1)));
    outerGrid.items.add(GridItem(gainLabel));
    outerGrid.items.add(GridItem(gainSlider).withArea(3, GridItem::Span (5)));

    outerGrid.templateRows.add(Track (Fr (1)));
    outerGrid.items.add(GridItem(stereoLabel));
    outerGrid.items.add(GridItem(stereoSlider).withArea(4, GridItem::Span (5)));


    outerGrid.performLayout (getLocalBounds());
    
}