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
            currentAngle = fmod(currentAngle + angleDelta, 1.0f);
        }
        output->setValue(i, value);
    }
}

void LowFreqOsc::resetAngle()
{
    currentAngle = 0.0f;
}

void LowFreqOsc::progressAngle()
{
    currentAngle = fmod(currentAngle + angleDelta, 1.0f);
}

void LowFreqOsc::updateAngleDelta()
{
    angleDelta = frequency / sampleRate;
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

void LowFreqOsc::reserveSpace(int framesPerBlock)
{
    output->reserveBlockSpace(framesPerBlock);
}

void LowFreqOsc::releaseResources()
{
    output->releaseResources();
}

void LowFreqOsc::setSampleRate(float sr)
{
    sampleRate = sr;
    updateAngleDelta();
}

void LowFreqOsc::setValue(int position, float value)
{
    if (position < output->outputBlockSize())
    {
        output->setValue(position, value);
    }
}

float LowFreqOsc::getValue(int position)
{
    return output->getValue(position);
}

void LowFreqOsc::resetLFO()
{
    resetAngle();
}
