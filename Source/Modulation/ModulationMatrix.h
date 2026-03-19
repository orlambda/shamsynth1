/*
  ==============================================================================

    ModulationMatrix.h
    Created: 13 Mar 2026 9:29:11pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationRouting.h"
#include "ModulationSignalBlock.h"

#include <vector>

class ModulationMatrix
{
public:
    void addRouting(std::shared_ptr<ModulationSignalBlock> source, std::shared_ptr<ModulationSignalBlock> destination);
    void setScaling(std::shared_ptr<ModulationSignalBlock> source, std::shared_ptr<ModulationSignalBlock> destination, float scaling);
    void applyModulation();
private:
    // TODO: find container to allow search by ?
    // maybe use enums for source and target IDs (how does this work with per-voice sources/targets? 1 per voice?)
    std::vector<ModulationRouting> routings;
};
