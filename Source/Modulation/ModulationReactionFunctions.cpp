/*
  ==============================================================================

    ModulationReactionFunctions.cpp
    Created: 22 Apr 2026 1:55:57am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationReactionFunctions.h"

#include "../Parameters.h"

using namespace ParameterValues;

// TODO: should this `return value * (modulation * osc1LevelMaximumModFactor + 1);`
float ModulationReactionFunctions::modulateLevel(float value, float modulation)
{
    return value * (modulation + 1) * levelMaximumModFactor;
}

float ModulationReactionFunctions::modulateTune(float value, float modulation)
{
    return value + (modulation * tuneMaximumModFactor);
}
