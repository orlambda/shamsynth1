/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Versioning.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Shamsynth1AudioProcessorEditor::Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor& p)
    : AudioProcessorEditor(&p),audioProcessor (p), valueTreeState(p.parameters), keyboardComponent(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(windowWidth, windowHeight);
    
    // For grabbing keyboard focus
    startTimer(400);
    
    outputVolumeLabel.setText("Output Volume", juce::dontSendNotification);
    addAndMakeVisible(outputVolumeLabel);
    outputVolumeAttachment.reset(new SliderAttachment (valueTreeState, "outputVolume", outputVolumeSlider));
    
    // TODO: refactor
    outputVolumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    // Magic numbers!
    outputVolumeSlider.setRange(0.0, 1, 0.01);
    outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    outputVolumeSlider.setPopupDisplayEnabled(true, false, this);
    outputVolumeSlider.setTextValueSuffix(" Output Volume");
    addAndMakeVisible(&outputVolumeSlider);
    
    // MIDI
    addAndMakeVisible(keyboardComponent);
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
    std::string displayText = "shamsynth1 by orlambda - version " + Versioning::currentVersion;
    g.drawFittedText(displayText, 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Shamsynth1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    outputVolumeSlider.setBounds(40, 40, 20, 150);
    outputVolumeLabel.setBounds(20, 180, 200, 50);
    int keyboardHeight = 75;
    keyboardComponent.setBounds(0, windowHeight - keyboardHeight, windowWidth, keyboardHeight);
}

void Shamsynth1AudioProcessorEditor::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
