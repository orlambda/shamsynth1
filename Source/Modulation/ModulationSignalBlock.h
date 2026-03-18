/*
  ==============================================================================

    ModulationSignalBlock.h
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <vector>

class ModulationSignalBlock
{
public:
    void reserveSpace(float sampleCount);
    float getValue(int position) {return values[position];}
    void setValue(int position, float value) {values[position] = value;}
    void resetValues();
    int size(){return values.size();}
private:
    std::vector<float> values;
};

