/*
  ==============================================================================

    Wavefolder.cpp
    Created: 13 Mar 2026 9:30:19pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Wavefolder.h"

void Wavefolder::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();
    for (auto sample = 0; sample < totalNumSamples; ++sample)
    {
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            float currentValue = (buffer.getSample(channel, sample));
            if (currentValue > threshold)
            {
                float difference = currentValue - threshold;
                buffer.setSample(channel, sample, currentValue - (difference * amount));
            }
            else if (currentValue < -threshold)
            {
                float difference = threshold - currentValue;
                buffer.setSample(channel, sample, currentValue + (difference * amount));
            }
        }
    }
}
