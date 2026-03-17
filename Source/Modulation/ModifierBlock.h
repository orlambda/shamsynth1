/*
  ==============================================================================

    ModifierBlock.h
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <vector>

class ModifierBlock
{
public:
    void reserveSpace(float sampleCount);
    float getValue(int position) {return values[position];}
    void setValue(int position, float value) {values[position] = value;}
    int size(){return values.size();}
private:
    std::vector<float> values;
};

