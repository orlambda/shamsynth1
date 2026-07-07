/*
  ==============================================================================

    ModulationScalingParameter.h
    Created: 5 Jul 2026 8:37:22pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationIOList.h"

#include <memory>

class ModulationScalingParameter
{
public:
    ModulationScalingParameter(std::atomic<float>* p_p, ModulationSourceID p_sourceID, ModulationDestinationID p_destinationID) :
    p(p_p), sourceID(p_sourceID), destinationID(p_destinationID)
    {}
    void setParam(std::atomic<float>* p_p) {p = p_p;}
    ModulationSourceID getSourceID() {return sourceID;}
    ModulationDestinationID getDestinationID() {return destinationID;}
    std::atomic<float>* getParam() {return p;}
    std::atomic<float>* operator=(std::atomic<float>* p_p) {return p = p_p;}
    float getValue() {return *p;}
private:
    std::atomic<float>* p = nullptr;
    const ModulationSourceID sourceID;
    const ModulationDestinationID destinationID;
};
