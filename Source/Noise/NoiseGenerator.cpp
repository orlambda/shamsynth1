/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "NoiseGenerator.h"

#include "../Parameters.h"

using ParameterValues::noiseVolumeScale, ParameterValues::noiseHalfVolumeScale;

void NoiseGenerator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float totalNumSamples = buffer.getNumSamples();

    for (auto sample = 0; sample < totalNumSamples; ++sample)
    {
        // Generate noise at a level of 0.05
        float currentLevel = level->getModulatedValue(sample);
        float sampleValue = (random.nextFloat() * noiseVolumeScale - noiseHalfVolumeScale) * currentLevel;
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            buffer.addSample(channel, sample, sampleValue);
        }
    }
}

void NoiseGenerator::updateLevel(float p_level)
{
    level->setValue(p_level);
}

void NoiseGenerator::reserveSpace(int samplesPerBlock)
{
    level->reserveSpace(samplesPerBlock);
}

void NoiseGenerator::clearModulationSignalBlocks()
{
    level->clearAllModulation();
}
