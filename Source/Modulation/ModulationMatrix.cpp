/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 13 Mar 2026 9:29:11pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationMatrix.h"


void ModulationMatrix::addSource(ModulationSourceID sourceID, std::shared_ptr<ModulationOutputManager> source)
{
    sources.insert({sourceID, source});
}
void ModulationMatrix::addRouting(ModulationSourceID sourceID, ModulationDestinationID destinationID, std::shared_ptr<ModulationInputManager> destination)
{
    sources[sourceID]->addModulationTarget(destinationID, destination);
}
void ModulationMatrix::sendModulation(ModulationSourceID sourceID, ModulationDestinationID destinationID, float scaling)
{
    sources[sourceID]->sendModulation(destinationID, scaling);
}

