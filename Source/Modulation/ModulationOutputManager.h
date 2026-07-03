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
#include "../Parameters.h"

#include <map>
#include <string>

using namespace ParameterValues;

class ModulationOutputManager
{
public:
    ModulationOutputManager(bool p_perVoice, ParameterNames names);
    void addOutput(std::shared_ptr<ModulationOutput> source) {sources.push_back(source);}
    void addModulationTarget(ModulationDestinationID ID, std::shared_ptr<ModulationInputManager> inputDestination);
    void sendModulation(ModulationDestinationID ID, float scaling);
    std::vector<std::shared_ptr<ModulationOutput>> sources;
    void reserveSpace(int totalNumSamples);
    std::string get_scaling_id() {return scaling_id;}
    std::string get_scaling_name() {return scaling_name;}
private:
    std::map<ModulationDestinationID, std::shared_ptr<ModulationInputManager>> routings;
    bool perVoice;
    const std::string scaling_id;
    const std::string scaling_name;
};
