/*
  ==============================================================================

    WaveOscillator.cpp
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "WaveOscillator.h"

#include <math.h>

void WaveOscillator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();
    if (isActive)
    {
        for (auto sample = 0; sample < totalNumSamples; ++sample)
        {
            for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
            {
                float value = std::sinf(currentAngle) * currentLevel * overallLevel;
                currentAngle = fmod(currentAngle + angleDelta, 2.0 * juce::MathConstants<double>::pi);
                buffer.addSample(channel, sample, value);
            }
        }
    }
}

void WaveOscillator::silence()
{
    isActive = false;
}

void WaveOscillator::endNote()
{
    // TODO: this needs to work with the envelope rather than silencing immediately
    silence();
}

void WaveOscillator::startNote(float f)
{
    setFundamental(f);
    isActive = true;
    // TODO: initialise envelope position
}

void WaveOscillator::updateAngleDelta()
{
    angleDelta = (frequency / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void WaveOscillator::setFundamental(float f)
{
    frequency = f;
    updateAngleDelta();
}

void WaveOscillator::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}
