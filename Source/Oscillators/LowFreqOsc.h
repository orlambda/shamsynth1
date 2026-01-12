/*
  ==============================================================================

    LowFreqOsc.h
    Created: 15 Dec 2025 9:33:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include <vector>

// This is similar to WaveOscillator but I am avoiding multiple inheritance
// Think about how else to avoid repetitive code

// Oscillates between -1 and 1 at a given frequency
// Could process a block/array, but for now, it returns its value based on a position past its current angle
class LowFreqOsc
{
public:
    void startOsc(float f);
    void stopOsc();
    void calculateNextBlock(int samples);
    void resetAngle();
    void progressAngle();
    float getValue(int position);
    void setFrequency(float f);
    
    void setSampleRate(float sr);
    void setDepth(float d);
    void updateAngleDelta();
    std::vector<float> values;
    void reserveSpace(float sample_count) {values = std::vector<float>(sample_count);}
private:
    float sampleRate = 0.0;
    float currentAngle = 0.0;
    float angleDelta = 0.0;
    float frequency = 0.0;
    float depth = 0.0;
    bool isActive = false;
};
