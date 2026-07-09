/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "Editor/StandardSlider.h"

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Shamsynth1AudioProcessorEditor :  public juce::AudioProcessorEditor,
                                        private juce::Timer
{
public:
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor&);
    ~Shamsynth1AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Shamsynth1AudioProcessor& audioProcessor;
    
    // Window
    int windowWidth = 950;
    int windowHeight = 750;

    // Controls
    juce::AudioProcessorValueTreeState& valueTreeState;
    
    juce::Label osc1LevelLabel;
    StandardSlider osc1LevelSlider;
    
    juce::Label osc1SineLevelLabel;
    StandardSlider osc1SineLevelSlider;
    
    juce::Label osc1TriangleLevelLabel;
    StandardSlider osc1TriangleLevelSlider;
    
    juce::Label osc1SquareLevelLabel;
    StandardSlider osc1SquareLevelSlider;
    
    juce::Label osc1TuneLabel;
    StandardSlider osc1TuneSlider;
   
    juce::Label noiseLevelLabel;
    StandardSlider noiseLevelSlider;
    
    juce::Label bitcrusherBitDepthLabel;
    StandardSlider bitcrusherBitDepthSlider;
    
    juce::Label osc1WavefolderGeneralLabel;
    
    juce::Label osc1WavefolderThresholdLabel;
    StandardSlider osc1WavefolderThresholdSlider;
    
    juce::Label osc1WavefolderAmountLabel;
    StandardSlider osc1WavefolderAmountSlider;
    
    juce::Label env1AttackTimeLabel;
    StandardSlider env1AttackTimeSlider;
    
    juce::Label env1DecayTimeLabel;
    StandardSlider env1DecayTimeSlider;
    
    juce::Label env1SustainLevelLabel;
    StandardSlider env1SustainLevelSlider;
    
    juce::Label env1ReleaseTimeLabel;
    StandardSlider env1ReleaseTimeSlider;
    
    juce::Label lfo1FrequencyLabel;
    StandardSlider lfo1FrequencySlider;
    
    juce::Label lfo1DepthLabel;
    StandardSlider lfo1DepthSlider;
    
    juce::Label lfo2FrequencyLabel;
    StandardSlider lfo2FrequencySlider;
    
    juce::Label lfo2DepthLabel;
    StandardSlider lfo2DepthSlider;
    
    juce::Label outputVolumeLabel;
    StandardSlider outputVolumeSlider;
    
    juce::ToggleButton powerOnButton;
    std::unique_ptr<ButtonAttachment> powerOnAttachment;
    
    // Routings - do this dynamically as mod matrix will grow - will need a container for sliders
    
    juce::Label osc1EnvToTuneScalingLabel;
    juce::Slider osc1EnvToTuneScalingSlider;
    std::unique_ptr<SliderAttachment> osc1EnvToTuneScalingAttachment;
    
    juce::Label osc1EnvToOsc1LevelScalingLabel;
    juce::Slider osc1EnvToOsc1LevelScalingSlider;
    std::unique_ptr<SliderAttachment> osc1EnvToOsc1LevelScalingAttachment;
    
    juce::Label lfo1ToTuneScalingLabel;
    juce::Slider lfo1ToTuneScalingSlider;
    std::unique_ptr<SliderAttachment> lfo1ToTuneScalingAttachment;
    
    juce::Label lfo1ToOsc1LevelScalingLabel;
    juce::Slider lfo1ToOsc1LevelScalingSlider;
    std::unique_ptr<SliderAttachment> lfo1ToOsc1LevelScalingAttachment;
    
    // MIDI
    juce::MidiKeyboardComponent keyboardComponent;
    
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Shamsynth1AudioProcessorEditor)
};
