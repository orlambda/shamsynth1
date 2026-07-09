/*
  ==============================================================================

    StandardSlider.h
    Created: 9 Jul 2026 4:56:26am
    Author:  Orlando Shamlou

  ==============================================================================
*/

// A slider that can be attached ao an audio parameter

#pragma once

#include <JuceHeader.h>

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

struct StandardSlider : juce::Slider
{
    StandardSlider() {}
    void attach(juce::AudioProcessorValueTreeState& apvts, std::string parameterID);
    std::unique_ptr<SliderAttachment> parameterAttachment;
};
