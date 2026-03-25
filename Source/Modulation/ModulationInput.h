/*
  ==============================================================================

    ModulationInput.h
    Created: 20 Mar 2026 4:54:47am
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Holds a block which represents an input signal for a parent ModulatableFloat

#pragma once

#include "ModulationIOList.h"
#include "ModulationOutput.h"

class ModulationInput
{
public:
    void reserveBlockSpace(float sampleCount) {block->reserveSpace(sampleCount);}
    void resetBlockValues() {block->resetValues();}
    void applyModulation(std::shared_ptr<ModulationOutput> modulationSourceBlock, float scaling);
    float getValue(int position) {return block->getValue(position);}
    void addValue(int index, float valueToAdd) {setValue(index, getValue(index) + valueToAdd);}
    int blockSize() {return block->size();}
    std::shared_ptr<ModulationSignalBlock> block = std::make_shared<ModulationSignalBlock>();
private:
    void setValue(int position, float value) {block->setValue(position, value);}
};
