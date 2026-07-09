/*
  ==============================================================================

    StandardSlider.cpp
    Created: 9 Jul 2026 4:56:26am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "StandardSlider.h"


void StandardSlider::attach(juce::AudioProcessorValueTreeState& apvts, std::string parameterID)
{
    parameterAttachment.reset(new SliderAttachment (apvts, parameterID, *this));
}
