/*
  ==============================================================================

    ModifierBlock.cpp
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#include "ModifierBlock.h"

void ModifierBlock::reserveSpace(float sampleCount)
{
    if (sampleCount > values.size())
    {
        values = std::vector<float>(sampleCount);
    }
}
