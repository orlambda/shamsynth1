/*
  ==============================================================================

    ModulationOutput.h
    Created: 19 Mar 2026 8:45:43pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationIOList.h"
#include "ModulationSignalBlock.h"

class ModulationOutput
{
public:
    void reserveBlockSpace(float sampleCount) {block->reserveSpace(sampleCount);}
    float getValue(int position) {return block->getValue(position);}
    void setValue(int position, float value) {block->setValue(position, value);}
    void resetOutputBlockValues() {block->resetValues();}
    int outputBlockSize() {return block->size();}
    std::shared_ptr<ModulationSignalBlock> block = std::make_shared<ModulationSignalBlock>();
private:
};
