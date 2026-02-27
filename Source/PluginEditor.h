/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

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
    
    Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor&);
    ~Shamsynth1AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Shamsynth1AudioProcessor& audioProcessor;
    
    // Window
    int windowWidth = 750;
    int windowHeight = 570;

    // Controls
    juce::AudioProcessorValueTreeState& valueTreeState;
    
    juce::Label osc1LevelLabel;
    juce::Slider osc1LevelSlider;
    std::unique_ptr<SliderAttachment> osc1LevelAttachment;
    
    juce::Label osc1SineLevelLabel;
    juce::Slider osc1SineLevelSlider;
    std::unique_ptr<SliderAttachment> osc1SineLevelAttachment;
    
    juce::Label osc1TriangleLevelLabel;
    juce::Slider osc1TriangleLevelSlider;
    std::unique_ptr<SliderAttachment> osc1TriangleLevelAttachment;
    
    juce::Label osc1SquareLevelLabel;
    juce::Slider osc1SquareLevelSlider;
    std::unique_ptr<SliderAttachment> osc1SquareLevelAttachment;
    
    juce::Label osc1TuneLabel;
    juce::Slider osc1TuneSlider;
    std::unique_ptr<SliderAttachment> osc1TuneAttachment;
   
    juce::Label noiseLevelLabel;
    juce::Slider noiseLevelSlider;
    std::unique_ptr<SliderAttachment> noiseLevelAttachment;
    
    juce::Label bitcrusherBitDepthLabel;
    juce::Slider bitcrusherBitDepthSlider;
    std::unique_ptr<SliderAttachment> bitcrusherBitDepthAttachment;
    
    juce::Label lfo1FrequencyLabel;
    juce::Slider lfo1FrequencySlider;
    std::unique_ptr<SliderAttachment> lfo1FrequencyAttachment;
    
    juce::Label lfo1DepthLabel;
    juce::Slider lfo1DepthSlider;
    std::unique_ptr<SliderAttachment> lfo1DepthAttachment;
    
    juce::Label lfo2FrequencyLabel;
    juce::Slider lfo2FrequencySlider;
    std::unique_ptr<SliderAttachment> lfo2FrequencyAttachment;
    
    juce::Label lfo2DepthLabel;
    juce::Slider lfo2DepthSlider;
    std::unique_ptr<SliderAttachment> lfo2DepthAttachment;
    
    
    juce::Label outputVolumeLabel;
    juce::Slider outputVolumeSlider;
    std::unique_ptr<SliderAttachment> outputVolumeAttachment;
    
    // MIDI
    juce::MidiKeyboardComponent keyboardComponent;
    
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Shamsynth1AudioProcessorEditor)
};
