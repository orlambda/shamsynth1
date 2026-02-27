/*
  ==============================================================================

    WaveOscillator.h
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Oscillators/LowFreqOsc.h"

#include <JuceHeader.h>

// Adds all Waveforms for a Voice
class WaveOscillator
{
public:
    void startNote(float f);
    void endNote();
    // Abruptly ends all sound
    void silence();
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    void trigger(float f);
    void setFrequency(float f);
    // Is this necessary or can it
        // a) stay in the constructor if it won't change within Oscillator's lifetime (check this), or
        // b) be passed in through startNote()
    void setSampleRate(float sr);
    void updateAngleDelta();
    void updateLevel(float level) {currentLevel = level;}
    void updateSineLevel(float level) {currentSineLevel = level;}
    void updateTriangleLevel(float level) {currentTriangleLevel = level;}
    void updateSquareLevel(float level) {currentSquareLevel = level;}
    void updateTune(float tune) {currentTune = tune; updateAngleDelta();}
    
    std::vector<std::shared_ptr<LowFreqOsc>> tuneModifiers;
    
    // Temporary
    float sampleRate = 0.0;
private:
    // TODO: initialise in constructor
    float currentAngle = 0.0;
    float angleDelta = 0.0;
    
    float frequency = 0.0;
    
    float currentLevel = 1.0;
    float currentSineLevel = 1.0;
    float currentTriangleLevel = 1.0;
    float currentSquareLevel = 1.0;
    float currentTune = 0.0;
    float currentTuneAdjustment = 0.0;

    
    bool isActive = false;
};
