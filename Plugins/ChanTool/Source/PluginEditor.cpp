#include "PluginProcessor.h"
#include "PluginEditor.h"

ChanToolEditor::ChanToolEditor(
    ChanToolProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void ChanToolEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ChanToolEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
