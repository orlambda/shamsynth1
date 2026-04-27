/*
  ==============================================================================

    Bitcrusher.h
    Created: 15 Dec 2025 3:15:46pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Parameters.h"
#include "../Modulation/ModulatableFloat.h"

using ParameterValues::bitcrusherBitDepthValues, ParameterValues::bitcrusherBitDepthMaximumModFactor;

#include <JuceHeader.h>

class Bitcrusher {
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    void reserveSpace(int samplesPerBlock){bitDepth->reserveSpace(samplesPerBlock);}
    void clearModulationSignalBlocks();
    void setBitDepth(float p_depth){bitDepth->setValue(p_depth);}
    std::shared_ptr<ModulatableFloat> getBitDepthInput() {return bitDepth;}
private:
    std::shared_ptr<ModulatableFloat> bitDepth = std::make_shared<ModulatableFloat>(bitcrusherBitDepthValues, RangeLimits::bound,
                                                                                        [](float value, float modulation){return value + (value * modulation * bitcrusherBitDepthMaximumModFactor);});
};
