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
    
    // TODO: refactor as this will get huge with more sliders
    // Magic numbers
    
    osc1LevelLabel.setText("Osc 1 Level", juce::dontSendNotification);
    addAndMakeVisible(osc1LevelLabel);
    osc1LevelAttachment.reset(new SliderAttachment (valueTreeState, "osc1Level", osc1LevelSlider));
    osc1LevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1LevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1LevelSlider.setPopupDisplayEnabled(true, false, this);

    osc1LevelSlider.setTextValueSuffix("");
    addAndMakeVisible(&osc1LevelSlider);
    
    noiseLevelLabel.setText("Noise Level", juce::dontSendNotification);
    addAndMakeVisible(noiseLevelLabel);
    noiseLevelAttachment.reset(new SliderAttachment (valueTreeState, "noiseLevel", noiseLevelSlider));
    noiseLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    noiseLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    noiseLevelSlider.setPopupDisplayEnabled(true, false, this);
    noiseLevelSlider.setTextValueSuffix("");
    addAndMakeVisible(&noiseLevelSlider);
    
    bitcrusherBitDepthLabel.setText("Bit Depth", juce::dontSendNotification);
    addAndMakeVisible(bitcrusherBitDepthLabel);
    
    bitcrusherBitDepthAttachment.reset(new SliderAttachment (valueTreeState, "bitcrusherBitDepth", bitcrusherBitDepthSlider));
    
    bitcrusherBitDepthSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    bitcrusherBitDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    bitcrusherBitDepthSlider.setPopupDisplayEnabled(true, false, this);
    bitcrusherBitDepthSlider.setTextValueSuffix("");
    addAndMakeVisible(&bitcrusherBitDepthSlider);
    
    lfo1FrequencyLabel.setText("LFO 1 Frequency", juce::dontSendNotification);
    addAndMakeVisible(lfo1FrequencyLabel);
    
    lfo1FrequencyAttachment.reset(new SliderAttachment (valueTreeState, "lfo1Frequency", lfo1FrequencySlider));
    
    lfo1FrequencySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo1FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo1FrequencySlider.setPopupDisplayEnabled(true, false, this);
    lfo1FrequencySlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&lfo1FrequencySlider);
    
    outputVolumeLabel.setText("Output Volume", juce::dontSendNotification);
    addAndMakeVisible(outputVolumeLabel);
    
    outputVolumeAttachment.reset(new SliderAttachment (valueTreeState, "outputVolume", outputVolumeSlider));
    
    outputVolumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    outputVolumeSlider.setPopupDisplayEnabled(true, false, this);
    outputVolumeSlider.setTextValueSuffix("");
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
    
    // Magic numbers!
    osc1LevelSlider.setBounds(40, 40, 20, 150);
    osc1LevelLabel.setBounds(20, 180, 200, 50);
    noiseLevelSlider.setBounds(140, 40, 20, 150);
    noiseLevelLabel.setBounds(120, 180, 200, 50);
    bitcrusherBitDepthSlider.setBounds(240, 40, 20, 150);
    bitcrusherBitDepthLabel.setBounds(220, 180, 200, 50);
    lfo1FrequencySlider.setBounds(340, 40, 20, 150);
    lfo1FrequencyLabel.setBounds(320, 180, 200, 50);
    outputVolumeSlider.setBounds(440, 40, 20, 150);
    outputVolumeLabel.setBounds(420, 180, 200, 50);
    int keyboardHeight = 75;
    keyboardComponent.setBounds(0, windowHeight - keyboardHeight, windowWidth, keyboardHeight);
}

void Shamsynth1AudioProcessorEditor::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
