/*
  ==============================================================================

    WaveOscillator.cpp
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "WaveOscillator.h"
#include "../Helpers/audio_maths.h"

#include <math.h>

void WaveOscillator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();
    if (isActive)
    {
        for (int sample = 0; sample < totalNumSamples; ++sample)
        {
            // Apply LFO to tune
            for (auto modifier: tuneModifiers)
            {
                currentTuneAdjustment = 0;
                // temp scaling - measures LFO depth
                
                float scale = 12;
                currentTuneAdjustment = currentTuneAdjustment + (modifier->getValue(sample) * scale);
            }
            updateAngleDelta();
            // Update angle delta here instead of in frequency/tune setters?
            float sampleValue = std::sin(currentAngle) * currentLevel;
            for (int channel = 0; channel < totalNumOutputChannels; ++channel)
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
    // Tune is currently in semitones (probably change this to cents)
    float adjustedFrequency = audio_maths::increaseHzUsingCents(frequency, (currentTune + currentTuneAdjustment) * 100);
    angleDelta = (adjustedFrequency / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void WaveOscillator::setFrequency(float f)
{
    // Use abs for now to deal with negative values
    if (f >= 0.0)
        {frequency = f;}
    updateAngleDelta();
}

void WaveOscillator::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}
