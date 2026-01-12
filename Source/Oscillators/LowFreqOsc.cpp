/*
  ==============================================================================

    LowFreqOsc.cpp
    Created: 15 Dec 2025 9:33:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "LowFreqOsc.h"

#include <JuceHeader.h>

#include <math.h>

void LowFreqOsc::startOsc(float f)
{
    setFrequency(f);
    resetAngle();
    isActive = true;
}

void LowFreqOsc::stopOsc()
{
    isActive = false;
}

void LowFreqOsc::calculateNextBlock(int samples)
{
    // This will only be true if we are sent more samples in a block than expected
    // We avoid allocating space in usual cases
    while (samples > values.size())
    {
        values.push_back(0.0);
    }
    for (int i = 0; i < samples; ++i)
    {
        float value = 0.0;
        if (isActive) {
            value = std::sin(currentAngle + angleDelta) * depth;
        }
        values[i] = value;
        currentAngle = fmod(currentAngle + angleDelta, 2 * juce::MathConstants<double>::pi);
    }
}

void LowFreqOsc::resetAngle()
{
    currentAngle = 0.0;
}

void LowFreqOsc::progressAngle()
{
    currentAngle = fmod(currentAngle + angleDelta, 2 * juce::MathConstants<double>::pi);
}

void LowFreqOsc::updateAngleDelta()
{
    angleDelta = (frequency / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void LowFreqOsc::setFrequency(float f)
{
    frequency = f;
    updateAngleDelta();
}

// Expect value between 0 and 1, no range checking
void LowFreqOsc::setDepth(float d)
{
    depth = d;
}

void LowFreqOsc::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}

float LowFreqOsc::getValue(int position)
{
    return values[position];
}

