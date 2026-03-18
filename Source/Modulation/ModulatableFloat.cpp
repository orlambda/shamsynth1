/*
  ==============================================================================

    ModulatableFloat.cpp
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulatableFloat.h"

ModulatableFloat::ModulatableFloat(float p_min, float p_max, float p_value, Limit p_limitingMethod, std::function<float (float, float)> p_modulationFunction) : min(p_min), max(p_max), defaultValue(p_value), unmodulatedValue(p_value), modulatedValue(p_value), limitingMethod(p_limitingMethod), modulationFunction(p_modulationFunction)
{
}

void ModulatableFloat::reserveSpace(int samplesPerBlock)
{
    if (samplesPerBlock > inputSignalBlock.size())
    {
        inputSignalBlock.reserveSpace(samplesPerBlock);
    }
}

void ModulatableFloat::setValue(float p_value)
{
    unmodulatedValue = p_value;
    resetModulatedValue();
}

// THE VALUES PASSED IN block ARE WRONG
void ModulatableFloat::applyModulationSignal(std::shared_ptr<ModulationSignalBlock> block, float scaling)
{
    // TODO: delete when this is unnecessary
    reserveSpace(block->size());
    for (int i = 0; i < block->size(); ++i)
    {
        // TODO: addValue()
        float valueToAdd = inputSignalBlock.getValue(i) + (block->getValue(i) * scaling);
        inputSignalBlock.setValue(i, valueToAdd);
    }
}

float ModulatableFloat::getModulatedValue(int blockIndex)
{
    float value = modulationFunction(modulatedValue, inputSignalBlock.getValue(blockIndex));
    if ((limitingMethod == Limit::bound || limitingMethod == Limit::upperBound) && value > max)
    {
        return max;
    }
    else if((limitingMethod == Limit::bound || limitingMethod == Limit::lowerBound) && value < min)
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
    inputSignalBlock.resetValues();
}
