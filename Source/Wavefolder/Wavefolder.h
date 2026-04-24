/*
  ==============================================================================

    Wavefolder.h
    Created: 13 Mar 2026 9:30:19pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Simple wavefolder
// Any sample that goes above or below the threshold is folded over it.
// Wavefolding is symmetrical for positive and negative samples
// Threshold is a positive value

#pragma once

#include <JuceHeader.h>

class Wavefolder
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    void setThreshold(float f) {threshold = abs(f);};
    void SetAmount(float s) {amount = s;};
private:
    float threshold = 1.0f;
    float amount = 1.0f;
};
