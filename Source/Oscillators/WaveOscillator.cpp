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
            float sampleValue = std::sin(currentAngle) * currentLevel * overallLevel;
            for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
            {
                buffer.addSample(channel, sample, sampleValue);
            }
            currentAngle = fmod(currentAngle + angleDelta, 2.0 * juce::MathConstants<double>::pi);
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
    setFrequency(f);
    isActive = true;
    // TODO: initialise envelope position
}

void WaveOscillator::updateAngleDelta()
{
    angleDelta = (frequency / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void WaveOscillator::setFrequency(float f)
{
    frequency = f;
    updateAngleDelta();
}

void WaveOscillator::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}
