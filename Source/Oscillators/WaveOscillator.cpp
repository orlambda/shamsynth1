/*
  ==============================================================================

    WaveOscillator.cpp
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "WaveOscillator.h"
#include "Waveforms.h"
#include "../Helpers/audio_maths.h"

#include <cmath>

void WaveOscillator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels, Envelope& envelope)
{
    clearModulationSignalBlocks();
    float totalNumSamples = buffer.getNumSamples();
    if (isActive)
    {
        // Apply LFO and envelope to tune
        for (auto modifier: tuneModifiers)
        {
            // TODO - TEMPORARY MAGIC NUMBER
            float tuneScaling = 6.0f;
            currentTune.applyModulationSignal(modifier, tuneScaling);
        }
        for (int sample = 0; sample < totalNumSamples; ++sample)
        {
            currentTuneAdjustment = currentTune.getModulatedValue(sample);
            updateAngleDelta();
            // Update angle delta here instead of in frequency/tune setters?
            float sineSampleValue = Waveforms::sin(currentAngle) * currentSineLevel;
            float triangleSampleValue = Waveforms::triangle(currentAngle) * currentTriangleLevel;
            float squareSampleValue = Waveforms::square(currentAngle) * currentSquareLevel;
            float sampleValue = (sineSampleValue + triangleSampleValue + squareSampleValue);
            for (int channel = 0; channel < totalNumOutputChannels; ++channel)
            {
                buffer.addSample(channel, sample, sampleValue);
            }
            currentAngle = fmod(currentAngle + angleDelta, 2.0f * juce::MathConstants<double>::pi);
        }
        wavefolder.processBlock(buffer, totalNumOutputChannels);
        for (int sample = 0; sample < totalNumSamples; ++sample)
        {
            buffer.applyGain(sample, 1, currentLevel * envelope.values->getValue(sample));
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
    float adjustedFrequency = audio_maths::increaseHzUsingCents(frequency, (currentTune.getUnmodulatedValue() + currentTuneAdjustment) * 100.0f);
    angleDelta = (adjustedFrequency / sampleRate) * 2.0f * juce::MathConstants<double>::pi;
}

void WaveOscillator::setFrequency(float f)
{
    // Use abs for now to deal with negative values
    if (f >= 0.0f)
        {frequency = f;}
    updateAngleDelta();
}

void WaveOscillator::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}

void WaveOscillator::reserveSpace(int samplesPerBlock)
{
    currentTune.reserveSpace(samplesPerBlock);
}

void WaveOscillator::reset()
{
    resetAngle();
    isActive = false;
}

void WaveOscillator::clearModulationSignalBlocks()
{
    currentTune.clearAllModulation();
}
