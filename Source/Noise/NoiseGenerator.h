/*
  ==============================================================================

NoiseGenerator.h
    Created: 9 Oct 2025 8:28:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Modulation/ModulatableFloat.h"
#include "../Modulation/ModulationReactionFunctions.h"
#include "../Oscillators/LowFreqOsc.h"
#include "../Parameters.h"

#include <JuceHeader.h>

#include <vector>

using ModulationReactionFunctions::modulateLevel;
using ParameterValues::noiseLevelValues;

class NoiseGenerator
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    void clearModulationSignalBlocks();
    void reserveSpace(int samplesPerBlock);
    void updateLevel(float p_level);
    float sampleRate = 0.0;
    std::shared_ptr<ModulatableFloat> level = std::make_shared<ModulatableFloat>(noiseLevelValues, RangeLimits::lowerBound, modulateLevel);
private:
    juce::Random random;
};
