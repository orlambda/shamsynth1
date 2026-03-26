/*
  ==============================================================================

    Voice.h
    Created: 6 Oct 2025 11:37:50pm
    Author:  Orlando Shamlou

  ==============================================================================
*/

#pragma once

#include "../Modulation/ModulationInputManager.h"
#include "../Modulation/ModulationOutputManager.h"
#include "../Noise/NoiseGenerator.h"
#include "../Oscillators/WaveOscillator.h"
#include "../Oscillators/LowFreqOsc.h"
#include "../Effects/Bitcrusher.h"
#include "../Envelope/Envelope.h"

#include <JuceHeader.h>

class Voice
{
public:
    Voice();
    Envelope envelope;
    // Check state
    bool isActive() {return envelope.isActive();}
    int getMidiNoteNumber(){return midiNoteNumber;}
    float getFundamental(){return juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);}
    
    // Change state
    void trigger(int p_midiNoteNumber);
    void release();
    void queueNote(int p_midiNoteNumber);
    void reset();
    
    // Check input/output channels, are they combined, etc.
        // Could see if I can change both manually, and print number of channels in buffer, etc.
    void processBlock(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels);
    
    // TODO: make static - sampleRate the same for every Voice
    void setSampleRate(float rate);
    void clearModulationBlocks();
    void reserveSpace(int samplesPerBlock, int totalNumChannels);
    void updateOsc1Level(float level) {waveOsc.updateLevel(level);}
    void updateOsc1SineLevel(float level) {waveOsc.updateSineLevel(level);}
    void updateOsc1TriangleLevel(float level) {waveOsc.updateTriangleLevel(level);}
    void updateOsc1SquareLevel(float level) {waveOsc.updateSquareLevel(level);}
    void updateOsc1Tune(float tune) {waveOsc.updateTune(tune);}
    void updateADSRSettings(float a, float d, float s, float r);
    void updateNoiseLevel(float level) {whiteNoise.currentLevel = level;}
    void updateBitcrusherBitDepth(float depth) {bitcrusher.bitDepth = depth;}
    void updateWavefolderThreshold(float threshold) {waveOsc.updateWavefolderThreshold(threshold);}
    void updateWavefolderAmount(float amount) {waveOsc.updateWavefolderAmount(amount);}
    
    // However a modulation matrix will probably change implementation, wait till then before refactoring
    // Rename modifiers: modulation, lfos, signals..
    void addNoiseLevelModifier(std::shared_ptr<LowFreqOsc> modifier);
    void addOscTuneModifier(std::shared_ptr<ModulationSignalBlock> modifier);
    // Temporarily public to access modifiers in processor
    // osc1
    WaveOscillator waveOsc;
    
    std::shared_ptr<ModulationOutput> getEnvelopeOutput();
    std::shared_ptr<ModulatableFloat> getTuneInput();

private:
    // State
    float sampleRate;
    // TODO: how to initialise?
    int midiNoteNumber = 0;
    
    juce::AudioBuffer<float> voiceBuffer;
    
    // White Noise Generator
    NoiseGenerator whiteNoise;
    
    // effects
    Bitcrusher bitcrusher;
};
