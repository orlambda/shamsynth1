/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Versioning.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "Parameters.h"

using namespace ParameterValues;

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
        // Not all labels use the full name of the parameters - create a class/namespace that lists label names and can get get names from Parameters.h when needed
            // Or add label member to ParameterValues - do all parameters have labels?
        // Magic numbers
        // mod matrix scaling sliders may be a special case, or may need a function/class to get their ID
            // Routings class? test before usingg, must check capitalisation / call this function in APVTS cstor
        // addElements() might call addModMatrixSliders() etc
    
    osc1LevelLabel.setText(osc1LevelValues.name, juce::dontSendNotification);
    addAndMakeVisible(osc1LevelLabel);
    osc1LevelAttachment.reset(new SliderAttachment (valueTreeState, osc1LevelValues.ID, osc1LevelSlider));
    osc1LevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1LevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1LevelSlider.setPopupDisplayEnabled(true, false, this);
    osc1LevelSlider.setTextValueSuffix("");
    // TODO: Add to all sliders
    osc1LevelSlider.setDoubleClickReturnValue(true, osc1LevelValues.defaultValue);
    addAndMakeVisible(&osc1LevelSlider);
    
    
    osc1SineLevelLabel.setText("Sine Level", juce::dontSendNotification);
    addAndMakeVisible(osc1SineLevelLabel);
    osc1SineLevelAttachment.reset(new SliderAttachment (valueTreeState, osc1SineLevelValues.ID, osc1SineLevelSlider));
    osc1SineLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1SineLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1SineLevelSlider.setPopupDisplayEnabled(true, false, this);
    osc1SineLevelSlider.setTextValueSuffix("");
    osc1SineLevelSlider.setDoubleClickReturnValue(true, osc1SineLevelValues.defaultValue);
    addAndMakeVisible(&osc1SineLevelSlider);
    
    osc1TriangleLevelLabel.setText("Triangle Level", juce::dontSendNotification);
    addAndMakeVisible(osc1TriangleLevelLabel);
    osc1TriangleLevelAttachment.reset(new SliderAttachment (valueTreeState, osc1TriangleLevelValues.ID, osc1TriangleLevelSlider));
    osc1TriangleLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1TriangleLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1TriangleLevelSlider.setPopupDisplayEnabled(true, false, this);
    osc1TriangleLevelSlider.setTextValueSuffix("");
    osc1TriangleLevelSlider.setDoubleClickReturnValue(true, osc1TriangleLevelValues.defaultValue);
    addAndMakeVisible(&osc1TriangleLevelSlider);
    
    osc1SquareLevelLabel.setText("Square Level", juce::dontSendNotification);
    addAndMakeVisible(osc1SquareLevelLabel);
    osc1SquareLevelAttachment.reset(new SliderAttachment (valueTreeState, osc1SquareLevelValues.ID, osc1SquareLevelSlider));
    osc1SquareLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1SquareLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1SquareLevelSlider.setPopupDisplayEnabled(true, false, this);
    osc1SquareLevelSlider.setTextValueSuffix("");
    osc1SquareLevelSlider.setDoubleClickReturnValue(true, osc1SquareLevelValues.defaultValue);
    addAndMakeVisible(&osc1SquareLevelSlider);
    
    osc1TuneLabel.setText("Tune", juce::dontSendNotification);
    addAndMakeVisible(osc1TuneLabel);
    osc1TuneAttachment.reset(new SliderAttachment (valueTreeState, osc1TuneValues.ID, osc1TuneSlider));
    osc1TuneSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1TuneSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1TuneSlider.setPopupDisplayEnabled(true, false, this);
    osc1TuneSlider.setTextValueSuffix(" semitones");
    osc1TuneSlider.setDoubleClickReturnValue(true, osc1TuneValues.defaultValue);
    addAndMakeVisible(&osc1TuneSlider);
    
    noiseLevelLabel.setText(noiseLevelValues.name, juce::dontSendNotification);
    addAndMakeVisible(noiseLevelLabel);
    noiseLevelAttachment.reset(new SliderAttachment (valueTreeState, noiseLevelValues.ID, noiseLevelSlider));
    noiseLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    noiseLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    noiseLevelSlider.setPopupDisplayEnabled(true, false, this);
    noiseLevelSlider.setTextValueSuffix("");
    osc1SineLevelSlider.setDoubleClickReturnValue(true, osc1SineLevelValues.defaultValue);
    addAndMakeVisible(&noiseLevelSlider);
    
    bitcrusherBitDepthLabel.setText(bitcrusherBitDepthValues.name, juce::dontSendNotification);
    addAndMakeVisible(bitcrusherBitDepthLabel);
    bitcrusherBitDepthAttachment.reset(new SliderAttachment (valueTreeState, bitcrusherBitDepthValues.ID, bitcrusherBitDepthSlider));
    bitcrusherBitDepthSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    bitcrusherBitDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    bitcrusherBitDepthSlider.setPopupDisplayEnabled(true, false, this);
    bitcrusherBitDepthSlider.setTextValueSuffix("");
    bitcrusherBitDepthSlider.setDoubleClickReturnValue(true, bitcrusherBitDepthValues.defaultValue);
    addAndMakeVisible(&bitcrusherBitDepthSlider);
    
    osc1WavefolderGeneralLabel.setText("Wavefolder", juce::dontSendNotification);
    addAndMakeVisible(osc1WavefolderGeneralLabel);
    
    osc1WavefolderThresholdLabel.setText("Threshold", juce::dontSendNotification);
    addAndMakeVisible(osc1WavefolderThresholdLabel);
    osc1WavefolderThresholdAttachment.reset(new SliderAttachment (valueTreeState, osc1WavefolderThresholdValues.ID, osc1WavefolderThresholdSlider));
    osc1WavefolderThresholdSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1WavefolderThresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1WavefolderThresholdSlider.setPopupDisplayEnabled(true, false, this);
    osc1WavefolderThresholdSlider.setTextValueSuffix("");
    osc1WavefolderThresholdSlider.setDoubleClickReturnValue(true, osc1WavefolderThresholdValues.defaultValue);
    addAndMakeVisible(&osc1WavefolderThresholdSlider);
    
    osc1WavefolderAmountLabel.setText("Amount", juce::dontSendNotification);
    addAndMakeVisible(osc1WavefolderAmountLabel);
    osc1WavefolderAmountAttachment.reset(new SliderAttachment (valueTreeState, osc1WavefolderAmountValues.ID, osc1WavefolderAmountSlider));
    osc1WavefolderAmountSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1WavefolderAmountSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1WavefolderAmountSlider.setPopupDisplayEnabled(true, false, this);
    osc1WavefolderAmountSlider.setTextValueSuffix("");
    osc1WavefolderAmountSlider.setDoubleClickReturnValue(true, osc1WavefolderAmountValues.defaultValue);
    addAndMakeVisible(&osc1WavefolderAmountSlider);
    
    env1AttackTimeLabel.setText("A Time", juce::dontSendNotification);
    addAndMakeVisible(env1AttackTimeLabel);
    env1AttackTimeAttachment.reset(new SliderAttachment (valueTreeState, env1AttackTimeValues.ID, env1AttackTimeSlider));
    env1AttackTimeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    env1AttackTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    env1AttackTimeSlider.setPopupDisplayEnabled(true, false, this);
    env1AttackTimeSlider.setTextValueSuffix(" seconds");
    env1AttackTimeSlider.setDoubleClickReturnValue(true, env1AttackTimeValues.defaultValue);
    addAndMakeVisible(&env1AttackTimeSlider);
    
    env1DecayTimeLabel.setText("D Time", juce::dontSendNotification);
    addAndMakeVisible(env1DecayTimeLabel);
    env1DecayTimeAttachment.reset(new SliderAttachment (valueTreeState, env1DecayTimeValues.ID, env1DecayTimeSlider));
    env1DecayTimeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    env1DecayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    env1DecayTimeSlider.setPopupDisplayEnabled(true, false, this);
    env1DecayTimeSlider.setTextValueSuffix(" seconds");
    env1DecayTimeSlider.setDoubleClickReturnValue(true, env1DecayTimeValues.defaultValue);
    addAndMakeVisible(&env1DecayTimeSlider);
    
    env1SustainLevelLabel.setText("S Level", juce::dontSendNotification);
    addAndMakeVisible(env1SustainLevelLabel);
    env1SustainLevelAttachment.reset(new SliderAttachment (valueTreeState, env1SustainLevelValues.ID, env1SustainLevelSlider));
    env1SustainLevelSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    env1SustainLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    env1SustainLevelSlider.setPopupDisplayEnabled(true, false, this);
    env1SustainLevelSlider.setTextValueSuffix("");
    env1SustainLevelSlider.setDoubleClickReturnValue(true, env1SustainLevelValues.defaultValue);
    addAndMakeVisible(&env1SustainLevelSlider);
    
    env1ReleaseTimeLabel.setText("R Time", juce::dontSendNotification);
    addAndMakeVisible(env1ReleaseTimeLabel);
    env1ReleaseTimeAttachment.reset(new SliderAttachment (valueTreeState, env1ReleaseTimeValues.ID, env1ReleaseTimeSlider));
    env1ReleaseTimeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    env1ReleaseTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    env1ReleaseTimeSlider.setPopupDisplayEnabled(true, false, this);
    env1ReleaseTimeSlider.setTextValueSuffix(" seconds");
    env1ReleaseTimeSlider.setDoubleClickReturnValue(true, env1ReleaseTimeValues.defaultValue);
    addAndMakeVisible(&env1ReleaseTimeSlider);
    
    lfo1FrequencyLabel.setText("LFO 1 Freq", juce::dontSendNotification);
    addAndMakeVisible(lfo1FrequencyLabel);
    lfo1FrequencyAttachment.reset(new SliderAttachment (valueTreeState, lfo1FrequencyValues.ID, lfo1FrequencySlider));
    lfo1FrequencySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo1FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo1FrequencySlider.setPopupDisplayEnabled(true, false, this);
    lfo1FrequencySlider.setTextValueSuffix(" Hz");
    lfo1FrequencySlider.setDoubleClickReturnValue(true, lfo1FrequencyValues.defaultValue);
    addAndMakeVisible(&lfo1FrequencySlider);
    
    lfo1DepthLabel.setText("LFO 1 Depth", juce::dontSendNotification);
    addAndMakeVisible(lfo1DepthLabel);
    lfo1DepthAttachment.reset(new SliderAttachment (valueTreeState, lfo1DepthValues.ID, lfo1DepthSlider));
    lfo1DepthSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo1DepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo1DepthSlider.setPopupDisplayEnabled(true, false, this);
    lfo1DepthSlider.setTextValueSuffix("");
    lfo1DepthSlider.setDoubleClickReturnValue(true, lfo1DepthValues.defaultValue);
    addAndMakeVisible(&lfo1DepthSlider);
    
    lfo2FrequencyLabel.setText("LFO 2 Freq", juce::dontSendNotification);
    addAndMakeVisible(lfo2FrequencyLabel);
    lfo2FrequencyAttachment.reset(new SliderAttachment (valueTreeState, lfo2FrequencyValues.ID, lfo2FrequencySlider));
    lfo2FrequencySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo2FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo2FrequencySlider.setPopupDisplayEnabled(true, false, this);
    lfo2FrequencySlider.setTextValueSuffix("");
    lfo2FrequencySlider.setDoubleClickReturnValue(true, lfo2FrequencyValues.defaultValue);
    addAndMakeVisible(&lfo2FrequencySlider);
    
    lfo2DepthLabel.setText("LFO 2 Depth", juce::dontSendNotification);
    addAndMakeVisible(lfo2DepthLabel);
    lfo2DepthAttachment.reset(new SliderAttachment (valueTreeState, lfo2DepthValues.ID, lfo2DepthSlider));
    lfo2DepthSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo2DepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo2DepthSlider.setPopupDisplayEnabled(true, false, this);
    lfo2DepthSlider.setTextValueSuffix("");
    lfo2DepthSlider.setDoubleClickReturnValue(true, lfo2DepthValues.defaultValue);
    addAndMakeVisible(&lfo2DepthSlider);
    
    outputVolumeLabel.setText(outputVolumeValues.name, juce::dontSendNotification);
    addAndMakeVisible(outputVolumeLabel);
    outputVolumeAttachment.reset(new SliderAttachment (valueTreeState, outputVolumeValues.ID, outputVolumeSlider));
    outputVolumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    outputVolumeSlider.setPopupDisplayEnabled(true, false, this);
    outputVolumeSlider.setTextValueSuffix("");
    outputVolumeSlider.setDoubleClickReturnValue(true, outputVolumeValues.defaultValue);
    addAndMakeVisible(&outputVolumeSlider);
    
    powerOnAttachment.reset(new ButtonAttachment(valueTreeState, powerOnValues.ID, powerOnButton));
    powerOnButton.setButtonText(powerOnValues.name);
    addAndMakeVisible(powerOnButton);
    
    osc1EnvToTuneScalingLabel.setText("Osc 1 Env To Tune Scaling", juce::dontSendNotification);
    addAndMakeVisible(osc1EnvToTuneScalingLabel);
    osc1EnvToTuneScalingAttachment.reset(new SliderAttachment (valueTreeState, "osc1EnvToTuneScaling", osc1EnvToTuneScalingSlider));
    osc1EnvToTuneScalingSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1EnvToTuneScalingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1EnvToTuneScalingSlider.setPopupDisplayEnabled(true, false, this);
    osc1EnvToTuneScalingSlider.setTextValueSuffix("");
    osc1EnvToTuneScalingSlider.setDoubleClickReturnValue(true, scalingDefault);
    addAndMakeVisible(&osc1EnvToTuneScalingSlider);
    
    osc1EnvToOsc1LevelScalingLabel.setText("Osc 1 Env To Osc1Level Scaling", juce::dontSendNotification);
    addAndMakeVisible(osc1EnvToOsc1LevelScalingLabel);
    osc1EnvToOsc1LevelScalingAttachment.reset(new SliderAttachment (valueTreeState, "osc1EnvToOsc1LevelScaling", osc1EnvToOsc1LevelScalingSlider));
    osc1EnvToOsc1LevelScalingSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    osc1EnvToOsc1LevelScalingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    osc1EnvToOsc1LevelScalingSlider.setPopupDisplayEnabled(true, false, this);
    osc1EnvToOsc1LevelScalingSlider.setTextValueSuffix("");
    osc1EnvToOsc1LevelScalingSlider.setDoubleClickReturnValue(true, scalingDefault);
    addAndMakeVisible(&osc1EnvToOsc1LevelScalingSlider);
    
    lfo1ToTuneScalingLabel.setText("LFO 1 To Tune Scaling", juce::dontSendNotification);
    addAndMakeVisible(lfo1ToTuneScalingLabel);
    lfo1ToTuneScalingAttachment.reset(new SliderAttachment (valueTreeState, "lfo1ToTuneScaling", lfo1ToTuneScalingSlider));
    lfo1ToTuneScalingSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo1ToTuneScalingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo1ToTuneScalingSlider.setPopupDisplayEnabled(true, false, this);
    lfo1ToTuneScalingSlider.setTextValueSuffix("");
    lfo1ToTuneScalingSlider.setDoubleClickReturnValue(true, scalingDefault);
    addAndMakeVisible(&lfo1ToTuneScalingSlider);
    
    lfo1ToOsc1LevelScalingLabel.setText("LFO 1 To Osc1Level Scaling", juce::dontSendNotification);
    addAndMakeVisible(lfo1ToOsc1LevelScalingLabel);
    lfo1ToOsc1LevelScalingAttachment.reset(new SliderAttachment (valueTreeState, "lfo1ToOsc1LevelScaling", lfo1ToOsc1LevelScalingSlider));
    lfo1ToOsc1LevelScalingSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    lfo1ToOsc1LevelScalingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lfo1ToOsc1LevelScalingSlider.setPopupDisplayEnabled(true, false, this);
    lfo1ToOsc1LevelScalingSlider.setTextValueSuffix("");
    lfo1ToOsc1LevelScalingSlider.setDoubleClickReturnValue(true, scalingDefault);
    addAndMakeVisible(&lfo1ToOsc1LevelScalingSlider);
    
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
    juce::String displayText = juce::String(ProjectInfo::projectName) + " by " + juce::String(ProjectInfo::companyName) + " - v" + Versioning::currentVersion;
    g.drawFittedText(displayText, 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Shamsynth1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // Magic numbers!
    osc1LevelSlider.setBounds(40, 40, 20, 150);
    osc1LevelLabel.setBounds(20, 180, 200, 50);
    osc1SineLevelSlider.setBounds(140, 40, 20, 150);
    osc1SineLevelLabel.setBounds(120, 180, 200, 50);
    osc1TriangleLevelSlider.setBounds(240, 40, 20, 150);
    osc1TriangleLevelLabel.setBounds(220, 180, 200, 50);
    osc1SquareLevelSlider.setBounds(340, 40, 20, 150);
    osc1SquareLevelLabel.setBounds(320, 180, 200, 50);
    osc1TuneSlider.setBounds(440, 40, 20, 150);
    osc1TuneLabel.setBounds(420, 180, 200, 50);
    noiseLevelSlider.setBounds(540, 40, 20, 150);
    noiseLevelLabel.setBounds(520, 180, 200, 50);
    bitcrusherBitDepthSlider.setBounds(640, 40, 20, 150);
    bitcrusherBitDepthLabel.setBounds(620, 180, 200, 50);
    osc1WavefolderGeneralLabel.setBounds(770, 205, 200, 50);
    osc1WavefolderThresholdSlider.setBounds(740, 40, 20, 150);
    osc1WavefolderThresholdLabel.setBounds(720, 180, 200, 50);
    osc1WavefolderAmountSlider.setBounds(840, 40, 20, 150);
    osc1WavefolderAmountLabel.setBounds(820, 180, 200, 50);
    env1AttackTimeSlider.setBounds(40, 240, 20, 150);
    env1AttackTimeLabel.setBounds(20, 380, 200, 50);
    env1DecayTimeSlider.setBounds(140, 240, 20, 150);
    env1DecayTimeLabel.setBounds(120, 380, 200, 50);
    env1SustainLevelSlider.setBounds(240, 240, 20, 150);
    env1SustainLevelLabel.setBounds(220, 380, 200, 50);
    env1ReleaseTimeSlider.setBounds(340, 240, 20, 150);
    env1ReleaseTimeLabel.setBounds(320, 380, 200, 50);
    lfo1FrequencySlider.setBounds(40, 440, 20, 150);
    lfo1FrequencyLabel.setBounds(20, 580, 200, 50);
    lfo1DepthSlider.setBounds(140, 440, 20, 150);
    lfo1DepthLabel.setBounds(120, 580, 200, 50);
    lfo2FrequencySlider.setBounds(240, 440, 20, 150);
    lfo2FrequencyLabel.setBounds(220, 580, 200, 50);
    lfo2DepthSlider.setBounds(340, 440, 20, 150);
    lfo2DepthLabel.setBounds(320, 580, 200, 50);
    outputVolumeSlider.setBounds(540, 440, 20, 150);
    outputVolumeLabel.setBounds(520, 580, 200, 50);
    powerOnButton.setBounds(650, 465, 100, 100);
    osc1EnvToTuneScalingSlider.setBounds(540, 240, 20, 75);
    osc1EnvToTuneScalingLabel.setBounds(540, 300, 200, 50);
    osc1EnvToOsc1LevelScalingSlider.setBounds(740, 240, 20, 75);
    osc1EnvToOsc1LevelScalingLabel.setBounds(740, 300, 200, 50);
    lfo1ToTuneScalingSlider.setBounds(540, 340, 20, 75);
    lfo1ToTuneScalingLabel.setBounds(540, 400, 200, 50);
    lfo1ToOsc1LevelScalingSlider.setBounds(740, 340, 20, 75);
    lfo1ToOsc1LevelScalingLabel.setBounds(740, 400, 200, 50);
    int keyboardHeight = 75;
    keyboardComponent.setBounds(0, windowHeight - keyboardHeight, windowWidth, keyboardHeight);
}

// TODO: Do I want this to happen? Is this only for standalone build or would I want this in a DAW?
void Shamsynth1AudioProcessorEditor::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
