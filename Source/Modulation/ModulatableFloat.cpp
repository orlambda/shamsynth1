/*
  ==============================================================================

    ModulatableFloat.cpp
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulatableFloat.h"

ModulatableFloat::ModulatableFloat(float p_min, float p_max, float p_value, float p_modulationScaling, Limit p_limitingMethod, std::function<float (float, float, float)> p_modulationFunction) : min(p_min), max(p_max), defaultValue(p_value), unmodulatedValue(p_value), modulatedValue(p_value), modulationScaling(p_modulationScaling), limitingMethod(p_limitingMethod), modulationFunction(p_modulationFunction)
{
}

void ModulatableFloat::setValue(float p_value)
{
    unmodulatedValue = p_value;
    resetModulatedValue();
}

void ModulatableFloat::applyModulation(float modulationValue)
{
    modulatedValue = modulationFunction(modulatedValue, modulationValue, modulationScaling);
}

float ModulatableFloat::getModulatedValue()
{
    if ((limitingMethod == Limit::bound || limitingMethod == Limit::upperBound) && modulatedValue > max)
    {
        return max;
    }
    else if((limitingMethod == Limit::bound || limitingMethod == Limit::lowerBound) && modulatedValue < min)
    {
        return min;
    }
    else
    {
        return modulatedValue;
    }
}
