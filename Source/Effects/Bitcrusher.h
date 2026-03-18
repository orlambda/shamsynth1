/*
  ==============================================================================

    Bitcrusher.h
    Created: 15 Dec 2025 3:15:46pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Bitcrusher {
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    // TODO: make private, work out how to get value (function, pass processor reference in constructor, etc)
    // Temporary safe value
    float bitDepth = 32.0f;
private:
};
