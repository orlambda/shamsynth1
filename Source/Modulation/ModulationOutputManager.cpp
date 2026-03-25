/*
  ==============================================================================

    ModulationOutputManager.cpp
    Created: 18 Mar 2026 4:02:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationOutputManager.h"

ModulationOutputManager::ModulationOutputManager(bool p_perVoice) : perVoice(p_perVoice)
{}

void ModulationOutputManager::addModulationTarget(ModulationDestinationID ID, std::shared_ptr<ModulationInputManager> inputDestination)
{
    routings.insert({ID, inputDestination});
}

void ModulationOutputManager::sendModulation(ModulationDestinationID ID, float scaling)
{
    routings[ID]->applyModulation(sources, scaling, perVoice);
}

void ModulationOutputManager::reserveSpace(int totalNumSamples)
{
    for (auto routing : routings)
    {
        routing.second->reserveSpace(totalNumSamples);
    }
}
