/*
  ==============================================================================

    ModulationMatrix.h
    Created: 13 Mar 2026 9:29:11pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Provides a map of all modulation output managers, allowing routing them to input managers and applying modulation with scaling.
// IO managers connect to one or more sources / destinations.
// Signal sources store their own routings.

#pragma once

#include "ModulationIOList.h"
#include "ModulationOutputManager.h"
#include "ModulationSignalBlock.h"

#include <map>
#include <vector>

class ModulationMatrix
{
public:
    void addSource(ModulationSourceID sourceID, std::shared_ptr<ModulationOutputManager> source);
    void addRouting(ModulationSourceID sourceID, ModulationDestinationID destinationID, std::shared_ptr<ModulationInputManager> destination);
    void sendModulation(ModulationSourceID sourceID, ModulationDestinationID destinationID, float scaling);
private:
    std::map<ModulationSourceID, std::shared_ptr<ModulationOutputManager>> sources;
};
