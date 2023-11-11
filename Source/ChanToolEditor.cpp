#include "ChanToolProcessor.hpp"
#include "ChanToolEditor.hpp"

constexpr int WIDTH = 600;
constexpr int HEADER_HEIGHT = 50;
constexpr int PROPERTY_HEIGHT = 300;
constexpr int HEIGHT = HEADER_HEIGHT + PROPERTY_HEIGHT;
constexpr int MARGIN = 5;


ChanToolEditor::ChanToolEditor(ChanToolProcessor& p) :
     AudioProcessorEditor(&p), proc_(p),
    main_component_(p.getChanToolParameters())
{

    addAndMakeVisible (header_component_);
    addAndMakeVisible (main_component_);

    setSize(WIDTH, HEIGHT);
}

//==============================================================================
void ChanToolEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

//==============================================================================
void ChanToolEditor::resized()
{
    using FlexItem = juce::FlexItem;
    juce::FlexBox box;

    box.flexDirection = juce::FlexBox::Direction::column;
    box.alignContent = juce::FlexBox::AlignContent::center;

    box.items.add(FlexItem(float(WIDTH), float(HEADER_HEIGHT), header_component_));
    box.items.add(FlexItem(float(WIDTH-(MARGIN*2)), float(PROPERTY_HEIGHT), main_component_)
            .withMargin(FlexItem::Margin(0, MARGIN, 0, MARGIN)));


    box.performLayout (juce::Rectangle(0, 0, getWidth(), getHeight()));
}
