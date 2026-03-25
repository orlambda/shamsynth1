/*
  ==============================================================================

    WaveOscillator.h
    Created: 10 Oct 2025 12:10:08am
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Envelope/Envelope.h"
#include "../Modulation/ModulatableFloat.h"
#include "../Parameters.h"
#include "../Wavefolder/Wavefolder.h"

#include <JuceHeader.h>

// Sums all Waveforms for a Voice
class WaveOscillator
{
public:
    void startNote(float f);
    void endNote();
    // Abruptly ends all sound
    void silence();
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels, Envelope& envelope);
    void resetAngle() {currentAngle = 0.0f;}
    void trigger(float f);
    void reset();
    void setFrequency(float f);
    void setSampleRate(float sr);
    void reserveSpace(int samplesPerBlock);
    void clearModulationSignalBlocks();
    void updateAngleDelta();
    void updateLevel(float level) {currentLevel = level;}
    void updateSineLevel(float level) {currentSineLevel = level;}
    void updateTriangleLevel(float level) {currentTriangleLevel = level;}
    void updateSquareLevel(float level) {currentSquareLevel = level;}
    void updateTune(float tune) {currentTune->setValue(tune); updateAngleDelta();}
    void updateWavefolderThreshold(float threshold) {wavefolder.setThreshold(threshold);}
    void updateWavefolderScaling(float scaling) {wavefolder.setScaling(scaling);}
    
    std::vector<std::shared_ptr<ModulationSignalBlock>> tuneModifiers;
    std::shared_ptr<ModulatableFloat> currentTune = std::make_shared<ModulatableFloat>(osc1TuneMin, osc1TuneMax, osc1TuneDefault, RangeLimits::bound,
                                                                                       [](float value, float modulation){return value + (modulation * osc1TuneModMultiplicationFactor);});
    
    // Temporary
    float sampleRate = 0.0f;
private:
    // TODO: initialise in constructor
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
    
    float frequency = 0.0f;
    
    float currentLevel = 1.0f;
    float currentSineLevel = 1.0f;
    float currentTriangleLevel = 1.0f;
    float currentSquareLevel = 1.0f;
    float currentTuneAdjustment = 0.0f;
    
    bool isActive = false;
    
    Wavefolder wavefolder;
};
