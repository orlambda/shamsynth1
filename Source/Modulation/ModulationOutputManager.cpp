/*
  ==============================================================================

    ModulationOutputManager.cpp
    Created: 18 Mar 2026 4:02:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationOutputManager.h"

ModulationOutputManager::ModulationOutputManager(bool p_perVoice, ParameterNames names) : perVoice(p_perVoice), scaling_id(names.ID), scaling_name(names.name)
{}

void ModulationOutputManager::addModulationTarget(ModulationDestinationID ID, std::shared_ptr<ModulationInputManager> inputDestination)
{
    routings.insert({ID, inputDestination});
}

void ModulationOutputManager::sendModulation(ModulationDestinationID ID, float scaling)
{
    // TODO: TEMP while some mod io are unused
    if (routings[ID] != nullptr)
    routings[ID]->applyModulation(sources, scaling, perVoice);
}

void ModulationOutputManager::reserveSpace(int totalNumSamples)
{
    for (auto routing : routings)
    {
        // TODO: TEMP while some mod io are unused
        if (routing.second != nullptr)
        routing.second->reserveSpace(totalNumSamples);
    }
}
