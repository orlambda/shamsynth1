/*
  ==============================================================================

    ModulationInputManager.cpp
    Created: 18 Mar 2026 4:02:52pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModulationInputManager.h"

ModulationInputManager::ModulationInputManager(bool perVoice) : perVoice(perVoice)
{}

void ModulationInputManager::applyModulation(std::vector<std::shared_ptr<ModulationOutput>> outputs, float scaling, bool outputIsPerVoice)
{
    if (perVoice)
    {
        if (outputIsPerVoice)
        {
            for (int i = 0; i < inputs.size() && i < outputs.size(); ++i)
            {
                inputs[i]->applyModulationSignal(outputs[i], scaling);
            }
        }
        else
        {
            for (auto input : inputs)
            {
                input->applyModulationSignal(outputs[0], scaling);
            }
        }
    }
    else
    {
        for (auto output : outputs)
        {
            inputs[0]->applyModulationSignal(output, scaling);
        }
    }
}

void ModulationInputManager::reserveSpace(int totalNumSamples)
{
    for (auto input : inputs)
    {
        input->reserveSpace(totalNumSamples);
    }
}
