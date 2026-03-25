/*
  ==============================================================================

    ModulationInputManager.h
    Created: 18 Mar 2026 4:02:52pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Handles a global modulation signal input (e.g. LFO frequency) or set of per-voice modulation inputs (e.g. Tune)

#pragma once

#include "ModulatableFloat.h"
#include "ModulationOutput.h"

class ModulationInputManager
{
public:
    ModulationInputManager(bool p_perVoice);
    void addTargetModulationFloat(std::shared_ptr<ModulatableFloat> f) {inputs.push_back(f);}
    void applyModulation(std::vector<std::shared_ptr<ModulationOutput>> blocks, float scaling, bool outputIsPerVoice);
    // Is this ever used?
    bool isPerVoice() {return perVoice;}
    void reserveSpace(int totalNumSamples);
protected:
private:
    std::vector<std::shared_ptr<ModulatableFloat>> inputs;
    bool perVoice;
};
