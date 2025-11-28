/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "NoiseGenerator.h"

void NoiseGenerator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();
    
    // Each oscillator/generator
    // Starting with a white noise generator

    for (auto sample = 0; sample < totalNumSamples; ++sample)
    {
        float sampleValue = random.nextFloat() * 0.1 - 0.05;
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            buffer.addSample(channel, sample, sampleValue);
        }
    }
}
