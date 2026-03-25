/*
  ==============================================================================

    ModulationRouting.h
    Created: 17 Mar 2026 5:20:42pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "ModulationSignalBlock.h"

#include <JuceHeader.h>

class ModulationRouting
{
public:
    ModulationRouting(std::shared_ptr<ModulationSignalBlock> p_source, std::shared_ptr<ModulationSignalBlock> p_destination);
    float getScaling(){return scaling;}
    void setScaling(float s){scaling = s;}
    // Optimisation: can check source for info e.g. if it has non-0 values / has been cleared
    bool isActive(){return !juce::exactlyEqual(scaling, 0.0f);}
    std::shared_ptr<ModulationSignalBlock> getSource() {return source;}
    std::shared_ptr<ModulationSignalBlock> getDestination() {return destination;}
private:
    const std::shared_ptr<ModulationSignalBlock> source;
    const std::shared_ptr<ModulationSignalBlock> destination;
    float scaling = 0.0f;
};
