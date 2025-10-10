/*
  ==============================================================================

    WaveOscillator.h
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class WaveOscillator
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    void setFundamental(float f) {fundamental = f;}
private:
    float fundamental;
    float sampleRate;
};
