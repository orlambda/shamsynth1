/*
  ==============================================================================

    ModulatableFloat.cpp
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulatableFloat.h"

ModulatableFloat::ModulatableFloat(float p_min, float p_max, float p_value, RangeLimits p_limitingMethod, std::function<float (float, float)> p_modulationFunction) : min(p_min), max(p_max), defaultValue(p_value), unmodulatedValue(p_value), modulatedValue(p_value), limitingMethod(p_limitingMethod), modulationFunction(p_modulationFunction)
{
}

void ModulatableFloat::reserveSpace(int samplesPerBlock)
{
    input->reserveBlockSpace(samplesPerBlock);
}

void ModulatableFloat::setValue(float p_value)
{
    unmodulatedValue = p_value;
    resetModulatedValue();
}

void ModulatableFloat::applyModulationSignal(std::shared_ptr<ModulationOutput> output, float scaling)
{
    input->applyModulation(output, scaling);
}

float ModulatableFloat::getModulatedValue(int blockIndex)
{
    float value = modulationFunction(modulatedValue, input->getValue(blockIndex));
    if ((limitingMethod == RangeLimits::bound || limitingMethod == RangeLimits::upperBound) && value > max)
    {
        return max;
    }
    else if((limitingMethod == RangeLimits::bound || limitingMethod == RangeLimits::lowerBound) && value < min)
    {
        return min;
    }
    else
    {
        return value;
    }
}

void ModulatableFloat::clearAllModulation()
{
    input->resetBlockValues();
}
