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
                                        private juce::Slider::Listener
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

    // Controls
    void sliderValueChanged (juce::Slider* slider) override;
    juce::Slider OutputVolume;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Shamsynth1AudioProcessorEditor)
};
