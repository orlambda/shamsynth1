/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Shamsynth1AudioProcessorEditor::Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor& p)
    : AudioProcessorEditor(&p),audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
    
    // TODO: refactor
    // these define the parameters of our slider object
    OutputVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    OutputVolume.setRange(0.0, 1, 0.01);
    OutputVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    OutputVolume.setPopupDisplayEnabled(true, false, this);
    OutputVolume.setTextValueSuffix(" Output Volume");
    OutputVolume.setValue(0.5);
    // this function adds the slider to the editor
    addAndMakeVisible(&OutputVolume);
    
    OutputVolume.addListener(this);
}

Shamsynth1AudioProcessorEditor::~Shamsynth1AudioProcessorEditor()
{
}

//==============================================================================
void Shamsynth1AudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions (15.0f));
    g.drawFittedText("shamsynth1 by orlambda", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Shamsynth1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    OutputVolume.setBounds(40, 40, 20, 150);
}

void Shamsynth1AudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &OutputVolume)
    {
        audioProcessor.OutputVolume = slider->getValue();
    }
}
