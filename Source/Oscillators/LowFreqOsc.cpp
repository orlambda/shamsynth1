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

void LowFreqOsc::progressOsc(int samples)
{
    // Is there a danger of overflow?
    currentAngle = fmod(currentAngle + (angleDelta * samples), 2.0 * juce::MathConstants<double>::pi);
    // How do plugins handle an LFO given a rate of 0 not being stuck at 0 output?
    if (frequency == 0)
    {
        resetAngle();
    }
}

void LowFreqOsc::resetAngle()
{
    currentAngle = 0;
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
    if (!isActive) {return 0.0;}
    return std::sin(currentAngle + position * angleDelta) * depth;
}

