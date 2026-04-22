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
#include "../Modulation/ModulationReactionFunctions.h"
#include "../Parameters.h"
#include "../Wavefolder/Wavefolder.h"

#include <JuceHeader.h>

using namespace ModulationReactionFunctions;
using namespace ParameterValues;

// Sums all Waveforms for a Voice
class WaveOscillator
{
public:
    void startNote(float f);
    void endNote();
    // Abruptly end all sound
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
    void updateLevel(float level) {currentLevel->setValue(level);}
    void updateSineLevel(float level) {currentSineLevel = level;}
    void updateTriangleLevel(float level) {currentTriangleLevel = level;}
    void updateSquareLevel(float level) {currentSquareLevel = level;}
    void updateTune(float tune) {currentTune->setValue(tune); updateAngleDelta();}
    void updateWavefolderThreshold(float threshold) {wavefolder.setThreshold(threshold);}
    void updateWavefolderAmount(float amount) {wavefolder.SetAmount(amount);}
    
    std::vector<std::shared_ptr<ModulationSignalBlock>> tuneModifiers;
    
// TODO: should this lambda `return value * (modulation * osc1LevelMaximumModFactor + 1);`? - this is also reused in noise and for other levels - make a named function somewhere
    std::shared_ptr<ModulatableFloat> currentLevel = std::make_shared<ModulatableFloat>(osc1LevelValues.minValue, osc1LevelValues.maxValue, osc1LevelValues.defaultValue, RangeLimits::lowerBound,
                                                                                    modulateLevel);
    std::shared_ptr<ModulatableFloat> currentTune = std::make_shared<ModulatableFloat>(osc1TuneValues.minValue, osc1TuneValues.maxValue, osc1TuneValues.defaultValue, RangeLimits::bound,
                                                                                    modulateTune);
    
    float sampleRate = 0.0f;
private:
    // TODO: initialise in constructor
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
    
    float frequency = 0.0f;
    
    float currentSineLevel = osc1SineLevelValues.defaultValue;
    float currentTriangleLevel = osc1TriangleLevelValues.defaultValue;
    float currentSquareLevel = osc1SquareLevelValues.defaultValue;
    float currentAdjustedTune = osc1TuneValues.defaultValue;
    
    bool isActive = false;
    
    Wavefolder wavefolder;
};
