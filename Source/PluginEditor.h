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
                                        private juce::Slider::Listener,
                                        private juce::Timer
{
public:
    Shamsynth1AudioProcessorEditor(Shamsynth1AudioProcessor&);
    ~Shamsynth1AudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Shamsynth1AudioProcessor& audioProcessor;
    
    // Window
    int windowWidth = 1000;
    int windowHeight = 700;

    // Controls
    void sliderValueChanged (juce::Slider* slider) override;
    juce::Slider OutputVolumeSlider;
    
    // MIDI
    juce::MidiKeyboardComponent keyboardComponent;
    
    void timerCallback() override;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Shamsynth1AudioProcessorEditor)
};
