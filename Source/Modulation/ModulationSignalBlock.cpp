/*
  ==============================================================================

    ModulationSignalBlock.cpp
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Represents a portion of a modulation signal to be passed from a ModulationOutput and applied to a ModulationInput
// Both inputs and outputs hold a block to store their signal

#include "ModulationSignalBlock.h"

#include <algorithm>

void ModulationSignalBlock::reserveSpace(float framesPerBlock)
{
    values.resize(framesPerBlock);
    values.shrink_to_fit();
}

void ModulationSignalBlock::releaseResources()
{
    values.clear();
    values.shrink_to_fit();
}
