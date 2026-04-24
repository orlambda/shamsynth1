/*
  ==============================================================================

    LowFreqOsc.cpp
    Created: 15 Dec 2025 9:33:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "LowFreqOsc.h"
#include "../Oscillators/Waveforms.h"

#include <JuceHeader.h>

void LowFreqOsc::startOsc(float f)
{
    setFrequency(f);
    resetAngle();
    isActive = true;
}

void LowFreqOsc::stopOsc()
{
    resetLFO();
}

void LowFreqOsc::calculateNextBlock(int samples)
{
    for (int i = 0; i < samples; ++i)
    {
        float value = 0.0f;
        if (isActive) {
            value = Waveforms::sin(currentAngle) * depth;
            currentAngle = fmod(currentAngle + angleDelta, 2.0f * juce::MathConstants<double>::pi);
        }
        outputSignalBlock->setValue(i, value);
        output->setValue(i, value);
    }
}

void LowFreqOsc::resetAngle()
{
    currentAngle = 0.0f;
}

void LowFreqOsc::progressAngle()
{
    currentAngle = fmod(currentAngle + angleDelta, 2.0f * juce::MathConstants<double>::pi);
}

void LowFreqOsc::updateAngleDelta()
{
    angleDelta = (frequency / sampleRate) * 2.0f * juce::MathConstants<double>::pi;
}

void LowFreqOsc::setFrequency(float f)
{
    frequency = f;
    updateAngleDelta();
}

void LowFreqOsc::setDepth(float d)
{
    depth = d;
}

void LowFreqOsc::reserveSpace(int sampleCount)
{
    outputSignalBlock->reserveSpace(sampleCount);
    output->reserveBlockSpace(sampleCount);
}

void LowFreqOsc::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}

void LowFreqOsc::setValue(int position, float value)
{
    if (position < outputSignalBlock->size())
    {
        outputSignalBlock->setValue(position, value);
    }
}

float LowFreqOsc::getValue(int position)
{
    return outputSignalBlock->getValue(position);
}

void LowFreqOsc::resetLFO()
{
    resetAngle();
}
