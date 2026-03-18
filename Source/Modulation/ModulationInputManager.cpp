/*
  ==============================================================================

    ModulationInputManager.cpp
    Created: 18 Mar 2026 4:02:52pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationInputManager.h"

void ModulationInputManager::applyModulation(std::shared_ptr<ModulationSignalBlock> block, float scaling)
{
    for (auto input : inputs)
    {
        // CURRENTLY INCORRECT
        input->applyModulationSignal(block, scaling);
    }
}
