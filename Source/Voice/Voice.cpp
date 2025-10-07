/*
  ==============================================================================

    Voice.cpp
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "Voice.h"

#include <iostream>

void Voice::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
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

void Voice::sayHi()
{
    std::cout << "Hi!" << std::endl;
}
