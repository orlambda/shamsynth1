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

void WaveOscillator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float framesPerBlock = buffer.getNumSamples();
    if (isActive)
    {
        for (int frame = 0; frame < framesPerBlock; ++frame)
        {
            currentModulatedTune = currentTune->getModulatedValue(frame);
            currentModulatedLevel = currentLevel->getModulatedValue(frame);
            updateAngleDelta();
            // Update angle delta here instead of in frequency/tune setters?
            float sineSampleValue = Waveforms::sin(currentAngle) * currentSineLevel;
            float triangleSampleValue = Waveforms::triangle(currentAngle) * currentTriangleLevel;
            float squareSampleValue = Waveforms::square(currentAngle) * currentSquareLevel;
            float sampleValue = (sineSampleValue + triangleSampleValue + squareSampleValue);
            for (int channel = 0; channel < totalNumOutputChannels; ++channel)
            {
                buffer.addSample(channel, frame, sampleValue);
            }
            currentAngle = fmod(currentAngle + angleDelta, 1.0f);
        }
        wavefolder.processBlock(buffer, totalNumOutputChannels);
        
        for (int frame = 0; frame < framesPerBlock; ++frame)
        {
            buffer.applyGain(frame, 1, currentLevel->getModulatedValue(frame));
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
    float adjustedFrequency = audio_maths::increaseHzUsingCents(frequency, (currentModulatedTune) * 100.0f);
    angleDelta = adjustedFrequency / sampleRate;
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

void WaveOscillator::reserveSpace(int framesPerBlock)
{
    currentLevel->reserveSpace(framesPerBlock);
    currentTune->reserveSpace(framesPerBlock);
}

void WaveOscillator::reset()
{
    resetAngle();
    isActive = false;
}

void WaveOscillator::clearModulationSignalBlocks()
{
    currentLevel->clearAllModulation();
    currentTune->clearAllModulation();
}
