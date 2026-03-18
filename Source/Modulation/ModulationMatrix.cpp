/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 13 Mar 2026 9:29:11pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationMatrix.h"

void ModulationMatrix::addRouting(std::shared_ptr<ModulationSignalBlock> source, std::shared_ptr<ModulationSignalBlock> destination)
{
    // REFACTOR: add routing
    routings.push_back(ModulationRouting(source, destination));
}

void ModulationMatrix::setScaling(std::shared_ptr<ModulationSignalBlock> source, std::shared_ptr<ModulationSignalBlock> destination, float scaling)
{
    // REFACTOR: find routing
    for (auto routing: routings)
    {
        if (source == routing.getSource() && destination == routing.getDestination())
        {
            routing.setScaling(scaling);
            return;
        }
    }
}

void ModulationMatrix::applyModulation()
{
    for (auto routing : routings)
    {
        routing.applyModulation();
    }
}
