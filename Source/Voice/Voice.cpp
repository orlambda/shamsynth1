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
        float sampleValue = random.nextFloat();
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            auto currentValue = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, currentValue + sampleValue * 0.1 - 0.05);
        }
//        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
}

void Voice::sayHi()
{
    std::cout << "Hi!" << std::endl;
}
