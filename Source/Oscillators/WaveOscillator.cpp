/*
  ==============================================================================

    WaveOscillator.cpp
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "WaveOscillator.h"

void WaveOscillator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();
    
    // Each oscillator/generator
    // Starting with a white noise generator
    

    for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        for (auto sample = 0; sample < totalNumSamples; ++sample)
        {
            // TODO: sin function
            float value = 0.0f;
            buffer.addSample(channel, sample, value);
        }
    }
}

