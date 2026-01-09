/*
  ==============================================================================

NoiseGenerator.h
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/


#pragma once

#include "../Oscillators/LowFreqOsc.h"

#include <JuceHeader.h>

#include <vector>

class NoiseGenerator
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    
    // Temporary
    float sampleRate = 0.0;
    float currentLevel = 0.0;
    // Consider making private, using add/remove lfo functions, etc.
    std::vector<std::shared_ptr<LowFreqOsc>> levelModifiers;
private:
    juce::Random random;

};

