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
    Bitcrusher();
    Bitcrusher(juce::AudioProcessor& p_p);
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    // TODO: make private, work out how to get value (function, pass processor reference in constructor, etc)
    float bitDepth;
private:
// For if I use the constructor with parameter
//    juce::AudioProcessor& p;
};
