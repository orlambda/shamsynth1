/*
  ==============================================================================

    Bitcrusher.cpp
    Created: 15 Dec 2025 3:15:46pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Bitcrusher.h"

Bitcrusher::Bitcrusher()
{
    // Temporary safe value
    bitDepth = 32;
}

// TEMP: NOT USED
Bitcrusher::Bitcrusher(juce::AudioProcessor& p_p)
{}
//Bitcrusher::Bitcrusher(juce::AudioProcessor& p_p) : p(p_p)
//{}

void Bitcrusher::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float currentBitDepth = bitDepth;
    float totalNumSamples = buffer.getNumSamples();
    float availableValues = powf(2, currentBitDepth);
    for (auto sample = 0; sample < totalNumSamples; ++sample)
    {
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            // Change range from [-1,1] to [0,1]
            float currentValue = (buffer.getSample(channel, sample) + 1) * 0.5f;
            float remainder = fmodf(currentValue, 1/availableValues);
            currentValue -= remainder;
            // Change range back to [-1,1]
            currentValue = currentValue * 2 - 1;
            buffer.setSample(channel, sample, currentValue);
        }
    }
    
    
    
}
