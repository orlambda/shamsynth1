/*
  ==============================================================================

    ModulationOutputManager.h
    Created: 18 Mar 2026 4:02:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Handles a global modulation signal output (e.g. LFO) or set of per-voice modulation outputs (e.g. Envelope)

// Routes output to ModulationInputManagers

#pragma once

#include "ModulationInputManager.h"
#include "ModulationIOList.h"
#include "ModulationOutput.h"

#include <map>

class ModulationOutputManager
{
public:
    ModulationOutputManager(bool p_perVoice);
    void addOutput(std::shared_ptr<ModulationOutput> source) {sources.push_back(source);}
    void addModulationTarget(ModulationDestinationID ID, std::shared_ptr<ModulationInputManager> inputDestination);
    void sendModulation(ModulationDestinationID ID, float scaling);
    std::vector<std::shared_ptr<ModulationOutput>> sources;
    void reserveSpace(int totalNumSamples);
private:
    std::map<ModulationDestinationID, std::shared_ptr<ModulationInputManager>> routings;
    bool perVoice;
};
