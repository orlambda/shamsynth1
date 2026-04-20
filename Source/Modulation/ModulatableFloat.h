/*
  ==============================================================================

    ModulatableFloat.h
    Created: 13 Mar 2026 10:50:26pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationInput.h"
#include "ModulationOutput.h"

#include <memory>
#include <functional>

// How out-of-range values are treated
enum class RangeLimits
{
    bound,
    upperBound,
    lowerBound,
    unbound
};

class ModulatableFloat
{
public:
    // TODO: constructor parameters: ParameterFloatValues object
    ModulatableFloat(float p_min, float p_max, float p_value, RangeLimits p_limitingMethod, std::function<float (float, float)> p_modulationFunction);
    void reserveSpace(int samplesPerBlock);
    void setValue(float p_value);
    void resetModulatedValue() {modulatedValue = unmodulatedValue;}
    void clearAllModulation();
    void applyModulationSignal(std::shared_ptr<ModulationOutput> output, float scaling);
    float getUnmodulatedValue() {return unmodulatedValue;}
    float getModulatedValue(int blockIndex);
    std::shared_ptr<ModulationInput> input = std::make_shared<ModulationInput>();
private:
    float min;
    float max;
    const float defaultValue;
    float unmodulatedValue;
    float modulatedValue;
    float modulationScaling;
    RangeLimits limitingMethod;
    std::function<float (float value, float modulationValue)> modulationFunction;
};
