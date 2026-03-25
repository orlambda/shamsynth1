/*
  ==============================================================================

    ModulationInput.cpp
    Created: 20 Mar 2026 4:54:47am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationInput.h"

void ModulationInput::applyModulation(std::shared_ptr<ModulationOutput> output, float scaling)
{
    for (int i = 0; i < output->block->size(); ++i)
    {
        addValue(i, output->block->getValue(i) * scaling);
    }
}
