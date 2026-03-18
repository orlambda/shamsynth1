/*
  ==============================================================================

    ModulationSignalBlock.cpp
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationSignalBlock.h"

#include <algorithm>

void ModulationSignalBlock::reserveSpace(float sampleCount)
{
    if (sampleCount > values.size())
    {
        // Could erase data
        values = std::vector<float>(sampleCount);
    }
}

void ModulationSignalBlock::resetValues()
{
    std::fill(values.begin(), values.end(), 0.0f);
}
