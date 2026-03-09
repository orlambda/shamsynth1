/*
  ==============================================================================

    LowFreqOsc.h
    Created: 15 Dec 2025 9:33:39pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../ModifierBlock/ModifierBlock.h"
#include "../Oscillators/Waveforms.h"

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
    void resetLFO();
    void resetAngle();
    void progressAngle();
    void setFrequency(float f);
    void setSampleRate(float sr);
    void setDepth(float d);
    void updateAngleDelta();
    void reserveSpace(int sampleCount) {values.reserveSpace(sampleCount);}
    ModifierBlock values;
    void setValue(int position, float value);
    float getValue(int position);
private:
    float sampleRate = 0.0f;
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
    float frequency = 0.0f;
    float depth = 0.0f;
    bool isActive = false;
};
