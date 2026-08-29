/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "NoiseGenerator.h"

#include "../Parameters.h"

using ParameterInfo::noiseVolumeScale, ParameterInfo::noiseHalfVolumeScale;

void NoiseGenerator::processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
    float framesPerBlock = buffer.getNumSamples();

    for (auto frame = 0; frame < framesPerBlock; ++frame)
    {
        // Generate noise at a level of 0.05
        float currentLevel = level->getModulatedValue(frame);
        float sampleValue = (random.nextFloat() * noiseVolumeScale - noiseHalfVolumeScale) * currentLevel;
        for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            buffer.addSample(channel, frame, sampleValue);
        }
    }
}

void NoiseGenerator::updateLevel(float p_level)
{
    level->setValue(p_level);
}

void NoiseGenerator::reserveSpace(int framesPerBlock)
{
    level->reserveSpace(framesPerBlock);
}

void NoiseGenerator::clearModulationSignalBlocks()
{
    level->clearAllModulation();
}
