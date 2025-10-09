/*
  ==============================================================================

NoiseGenerator.h
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>

#include <vector>

class NoiseGenerator
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    
private:
    juce::Random random;
};

