#include "PluginProcessor.h"
#include "PluginEditor.h"

ChanToolEditor::ChanToolEditor(
    ChanToolProcessor& p)
    : AudioProcessorEditor(&p), proc_(p),
    mainComponent(p.getChanToolParameters()->apvts.get())
{

    addAndMakeVisible (mainComponent);
    setSize(600, 400);
}

void ChanToolEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ChanToolEditor::resized()
{
    mainComponent.setBounds (0, 0, getWidth(), getHeight());
    //setBounds(getLocalBounds());
}
