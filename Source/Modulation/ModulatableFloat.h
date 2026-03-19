/*
  ==============================================================================

    ModulatableFloat.h
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationSignalBlock.h"

#include <functional>

// How out-of-range values are treated
enum class Limit
{
    bound,
    upperBound,
    lowerBound,
    unbound
};

class ModulatableFloat
{
public:
    ModulatableFloat(float p_min, float p_max, float p_value, Limit p_limitingMethod, std::function<float (float, float)> p_modulationFunction);
    void reserveSpace(int samplesPerBlock);
    void setValue(float p_value);
    void resetModulatedValue() {modulatedValue = unmodulatedValue;}
    void clearAllModulation();
    void applyModulationSignal(std::shared_ptr<ModulationSignalBlock> block, float scaling);
    float getUnmodulatedValue() {return unmodulatedValue;}
    float getModulatedValue(int blockIndex);
private:
    float min;
    float max;
    const float defaultValue;
    float unmodulatedValue;
    float modulatedValue;
    float modulationScaling;
    Limit limitingMethod;
    std::function<float (float value, float modulationValue)> modulationFunction;
    ModulationSignalBlock inputSignalBlock;
};

