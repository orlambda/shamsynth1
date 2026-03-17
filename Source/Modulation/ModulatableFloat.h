/*
  ==============================================================================

    ModulatableFloat.h
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <functional>

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
    ModulatableFloat(float p_min, float p_max, float p_value, float p_modulationScaling, Limit p_limitingMethod, std::function<float (float, float, float)> p_modulationFunction);
    // How out-of-range values are treated
    void setValue(float p_value);
    void resetModulatedValue() {modulatedValue = unmodulatedValue;}
    void applyModulation(float modulationValue);
    float getUnmodulatedValue() {return unmodulatedValue;}
    float getModulatedValue();
private:
    float min;
    float max;
    const float defaultValue;
    float unmodulatedValue;
    float modulatedValue;
    float modulationScaling;
    Limit limitingMethod;
    std::function<float (float value, float modulationValue, float scaling)> modulationFunction;
};

