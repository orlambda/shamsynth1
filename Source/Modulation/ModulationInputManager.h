/*
  ==============================================================================

    ModulationInputManager.h
    Created: 18 Mar 2026 4:02:52pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationSignalBlock.h"
#include "ModulatableFloat.h"


class ModulationInputManager
{
public:
    void addModulationInput(std::shared_ptr<ModulatableFloat> f){inputs.push_back(f);}
    void applyModulation(std::shared_ptr<ModulationSignalBlock> block, float scaling);
protected:
private:
    std::vector<std::shared_ptr<ModulatableFloat>> inputs;
};
