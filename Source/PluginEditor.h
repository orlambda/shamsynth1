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
    int windowWidth = 1000;
    int windowHeight = 700;

    // Controls
    juce::AudioProcessorValueTreeState& valueTreeState;
    juce::Label outputVolumeLabel;
    juce::Slider outputVolumeSlider;
    std::unique_ptr<SliderAttachment> outputVolumeAttachment;
    
    // MIDI
    juce::MidiKeyboardComponent keyboardComponent;
    
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Shamsynth1AudioProcessorEditor)
};
