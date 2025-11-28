/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Shamsynth1AudioProcessorEditor::Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor& p)
    : AudioProcessorEditor(&p),audioProcessor (p), keyboardComponent(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize(windowWidth, windowHeight);
    
    // For grabbing keyboard focus
    startTimer(400);
    
    
    // TODO: refactor
    // these define the parameters of our slider object
    OutputVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    OutputVolume.setRange(0.0, 1, 0.01);
    OutputVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    OutputVolume.setPopupDisplayEnabled(true, false, this);
    OutputVolume.setTextValueSuffix(" Output Volume");
    OutputVolume.setValue(audioProcessor.OutputVolume);
    // this function adds the slider to the editor
    addAndMakeVisible(&OutputVolume);
    
    // MIDI
    addAndMakeVisible(keyboardComponent);
    
    
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
    // Temporary versioning to ensure correct build is running
    std::string versionNumber = "0.0.01";
    // Increment before compiling to ensure build always matches code
    std::string compileNumber = "06";
    std::string displayText = "shamsynth1 by orlambda - version " + versionNumber + ", build no " + compileNumber;
    g.drawFittedText(displayText, 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Shamsynth1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    OutputVolume.setBounds(40, 40, 20, 150);
    int keyboardHeight = 75;
    keyboardComponent.setBounds(0, windowHeight - keyboardHeight, windowWidth, keyboardHeight);
}

void Shamsynth1AudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    // myMap[slider] = slider->getValue();
    if (slider == &OutputVolume)
    {
        audioProcessor.OutputVolume = slider->getValue();
    }
}

void Shamsynth1AudioProcessorEditor::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
