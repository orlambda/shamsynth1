/*
  ==============================================================================

    ModulationSignalBlock.h
    Created: 2 Mar 2026 2:30:55pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

// Represents a block of a signal to be passed from a ModulationOutput to a ModulationInput
// Size should always be the same as the buffer of audio being processed

#pragma once

#include <vector>

class ModulationSignalBlock
{
public:
    void reserveSpace(float sampleCount);
    float getValue(int position) {return values[position];}
    void setValue(int position, float value) {values[position] = value;}
    void resetValues() {std::fill(values.begin(), values.end(), 0.0f);}
    int size() {return static_cast<int>(values.size());}
private:
    std::vector<float> values;
};
